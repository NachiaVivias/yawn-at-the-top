
const fs = require('fs');
const toml = require('toml');
const html_escape = require('escape-html');
const prism = require('prismjs');
const loadLanguages = require('prismjs/components/');
loadLanguages("c");
loadLanguages("cpp");
loadLanguages("python");
loadLanguages("sh");
const cp = require('child_process');
const marked = require('marked');

const data = toml.parse(fs.readFileSync("build/build_setting.toml").toString());
const title = data.title;  // タイトル (先頭に表示)
const teamname = data.teamname;   // チーム名 + 大学名 (各ページ左上に表示)
const fontsize = data.fontsize;       // フォントサイズ
const orientation = data.orientation;     // portrait (縦長) / landscape (横長)
const num_columns = data.num_columns;          // 何段組みか
const break_after_toc = data.break_after_toc; // toc の後に : page (改ページする) / column (改段する) / auto (強制しない)
const sections = data.sections;   // ./* のフォルダを読み出す順序
const extra_list = data.extra_list;
const src_folder = data.src_folder;
const src_doc_folder = data.src_doc_folder;
const enable_extra = data.enable_extra;
const do_delete_clang_format_instruction = data.do_delete_clang_format_instruction;
const do_delete_triple_slash_comment = data.do_delete_triple_slash_comment;
const enable_line_hash = data.enable_line_hash;


let codeContent = "";
let ToCContent = "";

let extra_file_list = extra_list.map(x => x.file);

function getCatCommand(is_cpp, filepath) {
    if(is_cpp){
        let result = `clang-format ${filepath}`;
        if(do_delete_clang_format_instruction) result += ` | grep -v '// clang-format'`;
        if(do_delete_triple_slash_comment)     result += ` | grep -v '/// '`;
        return result;
    }
    else {
        return `cat ${filepath}`;
    }
}

// ファイルを開いて中身を取り出し、拡張子によって prism.js でパース & HTML エンコードを行う
function addCode(folder, doc_folder, filename, file_display_name, addTitle, isDoc) {
    // 隠しファイルは無視
    if(filename.startsWith('.')) return;

    const is_cpp = filename.endsWith(".cpp") || filename.endsWith(".hpp");
    const command_to_cat_file = getCatCommand(is_cpp, `${folder}/${filename}`);
    const file_text = cp.execSync(command_to_cat_file).toString();

    const text = file_text.trimEnd();

    // タイトル行
    if(addTitle) {
        ToCContent += `
        <li><a href="#${file_display_name}">${file_display_name}</a></li>`;
        codeContent += `
        <div class="filename">
            <h2 id="${file_display_name}">${file_display_name}</h2>`;

        // C++ ならハッシュ値を計算
        if (is_cpp) {
            var text_hash = cp.execSync(`${command_to_cat_file} | sh build/hash.sh`);
            codeContent += `
            md5: ${text_hash}`;
        }

        codeContent += `
        </div>`;
    }
    
    if(!isDoc && is_cpp) {
        // doc/に同じ構成のmdがあればそれを追加
        try {
            const doc_filename = filename.substring(0, filename.length - 4) + ".md";
            fs.statSync(doc_folder + "/" + doc_filename);
            addCode(doc_folder, "", doc_filename, "", false, true);
        } catch(err) {
        }
    }

    const highlight_text = (function () {
        // .md ファイルは marked で HTML にコンパイル
        if (filename.endsWith(".md")) {
            return marked.marked(text, { gfm: true });
        }
        // prism.js でパース & HTML エンコード
        if (is_cpp) {
            if(enable_line_hash) {
                raw = text.split('\n');
                highlighted = prism.highlight(text, prism.languages.cpp, "cpp").split('\n');
                // 行ごとのハッシュを計算
                const hashed = cp.execSync(`${command_to_cat_file} | sh build/hash_line.sh`).toString().split('\n')
                var ret = "";
                var j = 0;
                var block_comment = false;
                for(var i = 0; i < highlighted.length; i++) {
                    const line = raw[i];
                    var with_hash = false;
                    var idx = 0;
                    while(true) {
                        // この辺のコメント判定はガバガバです。許してね
                        if(block_comment) {
                            const nidx = line.indexOf('*/', idx);
                            if(nidx == -1) break;
                            idx = nidx + 2;
                            block_comment = false;
                        } else {
                            const nidx1 = line.indexOf('//', idx);
                            if(nidx1 != -1) {
                                if(/\S/.test(line.substring(idx, nidx1))) with_hash = true;
                                break;
                            }
                            const nidx2 = line.indexOf('/*', idx);
                            if(nidx2 != -1) {
                                if(/\S/.test(line.substring(idx, nidx2))) with_hash = true;
                                idx = nidx2 + 2;
                                block_comment = true;
                                continue;
                            }
                            if(/\S/.test(line.substring(idx))) with_hash = true;
                            break;
                        }
                    }
                    if(!with_hash) {
                        ret += '    ' + highlighted[i] + '\n';
                    } else {
                        ret += hashed[j++] + '  ' + highlighted[i] + '\n';
                    }
                }
                return ret;
            } else {
                return prism.highlight(text, prism.languages.cpp, "cpp");
            }
        }
        if (filename.endsWith(".py")) {
            return prism.highlight(text, prism.languages.python, "python");
        }
        if (filename.endsWith(".sh")) {
            return prism.highlight(text, prism.languages.sh, "sh");
        }
        return html_escape(text);
    })();

    codeContent += `
    <div class="${isDoc ? "content-doc" : "content"} content-${filename.split('.').pop()}">`;
    if (filename.endsWith(".md")) {
        codeContent += highlight_text;
    } else {
        codeContent += `
    <pre><code>${highlight_text}</code></pre>
`;
    }

    codeContent += '</div>\n';
}

for (const section of sections) {
    section_name = section.name;
    section_mode = section.mode ?? "manual";
    section_include = section.include ?? [];
    section_exclude = section.exclude ?? [];

    ToCContent += `
    <li><a class="section" href="#${section_name}">${section_name}</a></li>
    <ol>`;
    codeContent += `
    <h2 class="section" id="${section_name}">${section_name}</h2>
    `;

    const src_section_folder = src_folder + "/" + section_name;
    const src_doc_section_folder = src_doc_folder + "/" + section_name;

    if (fs.existsSync(src_section_folder)) {
        
        if (section_mode == "auto") {
            // フォルダ内のファイルを読み込む
            for (const file of fs.readdirSync(src_section_folder)) {
                if (!( section_include.map((f) => f.name).includes(file) )) {
                    section_include.push({ name:file });
                }
            }
        }

        for (const file of section_include) {
            if (file.name === null) continue;
            if (section_exclude.includes(file.name)) continue;
            if (extra_file_list.includes(section_name + "/" + file.name)) continue;
            if (!(fs.statSync(src_section_folder + "/" + file.name).isFile())) continue;

            file_display_name = file.display_name ?? file.name;

            addCode(src_section_folder, src_doc_section_folder, file.name, file_display_name, true, false);
        }

    } else {
        // フォルダが空だったら warning を出す
        console.warn(`Warning: ${src_section_folder} does not exist.`);
    }

    ToCContent += `
    </ol>`;
}

if (enable_extra && extra_list.length != 0) {
    
    ToCContent += `
    <li><a class="section" href="#extra">extra</a></li>
    <ol>`;
    codeContent += `
    <h2 class="section section-extra" id="extra">extra</h2>
    `;

    for (const extra_item of extra_list) {
        section_name = extra_item.file.split("/")[0];
        file_name = extra_item.file.split("/")[1];
        file_display_name = extra_item.display_name ?? file_name;

        const src_section_folder = src_folder + "/" + section_name;
        const src_doc_section_folder = src_doc_folder + "/" + section_name;

        if (fs.statSync(src_section_folder + "/" + file_name).isFile()) {
            addCode(src_section_folder, src_doc_section_folder, file_name, file_display_name, true, false);
        }
    }

    ToCContent += `
    </ol>`;
}


// build/notebook.html を出力
const htmlFileName = 'build/notebook.html';
fs.writeFileSync(htmlFileName, `<!DOCTYPE html>
<!-- generated by build/build.js -->
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>${title}</title>
    <!-- MathJax -->
    <script>
        var MathJax = {
            tex: {
                inlineMath: [['$', '$']]
            }
        };
    </script>
    <!--
    ここにあった polyfill.io のスクリプトリンクは削除しました。
    （そもそもブラウザが新しければ polyfill は不要 , 2024年に polyfill.io が切れて問題が起きているらしいし、このリンクは繋がらない）
    <script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
    -->
    <script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>
    <!-- css -->
    <link rel="stylesheet" type="text/css" href="notebook.css" />
</head>
<body>
    <h1 id="title">${title}</h1>
    <!-- 目次 -->
    <nav id="toc" role="doc-toc">
        <ol>
            ${ToCContent}
        </ol>
    </nav>

    ${codeContent}
</body>
</html>`);

// build/notebook.css を出力
fs.writeFileSync("build/notebook.css", `/* generated by build/build.js */
@import url("base.css");

html,
code {
    font-size: ${fontsize};
}

nav#toc {
    break-after: ${break_after_toc};
}

@media print {
    body {
        column-count: ${num_columns};
    }

    @page {
        size: A4 ${orientation};

        /* ヘッダー */
        @top-left {
            content: "${teamname}";
        }
    }
}`);

/*
// .verify-helper/docs/_config.yml を出力
fs.writeFileSync(".verify-helper/docs/_config.yml", `
# generated by build/build.js
title: '${title}'
exclude: ['node_modules', 'test/benchmark']
`);
*/

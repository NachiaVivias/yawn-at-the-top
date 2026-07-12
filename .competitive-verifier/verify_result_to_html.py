'''

Google Gemini に作らせました
以下プロンプト



competitive-verifier (https://github.com/competitive-verifier/competitive-verifier)_の出力 JSON を、なるべく情報を捨てることなく、見やすいように HTML に整形する pythonスクリプトを作成してください。

添付のファイルは、出力の例（一部省略）です。

HTML 側の設計としては、まずテスト用プログラムそれぞれの成功・失敗を示すページを作り、そこからリンクする形で各プログラムの詳細な結果を示すページを作ってください。





ありがとうございます。

tc_elapsed , tc_memory を出力する部分の fstring が間違っているので、修正してください。

それと、 index のページに表示する内容として、成功・失敗に加えて Slowest と Heaviest を表示するようにしてください。

'''


import json
import os
import html

def escape(text):
    """HTMLエスケープ処理"""
    return html.escape(str(text))

def get_status_class(status):
    """ステータスに応じたCSSクラスを返す"""
    status = str(status).lower()
    if status in ['success', 'ac']:
        return 'status-success'
    elif status in ['failure', 'wa', 'tle', 're', 'mle']:
        return 'status-failure'
    return 'status-other'

def generate_html(json_filepath, output_dir):
    # 出力先ディレクトリの作成
    os.makedirs(output_dir, exist_ok=True)

    # JSONの読み込み
    with open(json_filepath, 'r', encoding='utf-8') as f:
        data = json.load(f)

    total_seconds = data.get("total_seconds", 0)
    files = data.get("files", {})

    # 共通のCSS
    css = """
    <style>
        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; line-height: 1.6; color: #333; background-color: #f9f9f9; padding: 20px; }
        .container { max-width: 1000px; margin: 0 auto; background: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }
        h1, h2, h3 { color: #2c3e50; }
        a { color: #3498db; text-decoration: none; }
        a:hover { text-decoration: underline; }
        table { width: 100%; border-collapse: collapse; margin-top: 15px; margin-bottom: 30px; }
        th, td { border: 1px solid #ddd; padding: 10px; text-align: left; }
        th { background-color: #f2f2f2; font-weight: bold; }
        tr:nth-child(even) { background-color: #fafafa; }
        .status-success { color: #27ae60; font-weight: bold; }
        .status-failure { color: #e74c3c; font-weight: bold; }
        .status-other { color: #f39c12; font-weight: bold; }
        .back-link { display: inline-block; margin-bottom: 20px; font-size: 1.1em; }
        .summary-box { background-color: #e8f4f8; padding: 15px; border-left: 5px solid #3498db; margin-bottom: 20px; }
    </style>
    """

    # インデックスページ (index.html) の生成
    index_html_path = os.path.join(output_dir, "index.html")
    with open(index_html_path, 'w', encoding='utf-8') as idx_f:
        idx_f.write(f"<!DOCTYPE html>\n<html>\n<head>\n<meta charset='utf-8'>\n<title>Verification Results</title>\n{css}\n</head>\n<body>\n")
        idx_f.write("<div class='container'>\n")
        idx_f.write("<h1>Verification Results</h1>\n")
        idx_f.write(f"<div class='summary-box'><p><strong>Total Execution Time:</strong> {total_seconds:.3f} seconds</p></div>\n")
        
        idx_f.write("<table>\n<tr><th>File Path</th><th>Overall Status</th><th>Slowest (s)</th><th>Heaviest (MB)</th></tr>\n")

        # 各ファイルの詳細ページ生成とインデックスへの追加
        for filepath, file_data in files.items():
            detail_filename = filepath.replace('/', '_').replace('\\', '_') + ".html"
            detail_filepath = os.path.join(output_dir, detail_filename)
            
            verifications = file_data.get("verifications", [])
            
            # ファイル全体のステータスと、Slowest/Heaviestの最大値を算出
            overall_status = "success"
            max_slowest = -1.0
            max_heaviest = -1.0

            for ver in verifications:
                if ver.get("status") == "failure":
                    overall_status = "failure"
                if "slowest" in ver:
                    max_slowest = max(max_slowest, float(ver["slowest"]))
                if "heaviest" in ver:
                    max_heaviest = max(max_heaviest, float(ver["heaviest"]))
            
            status_class = get_status_class(overall_status)
            str_slowest = f"{max_slowest:.3f}" if max_slowest >= 0 else "N/A"
            str_heaviest = f"{max_heaviest:.3f}" if max_heaviest >= 0 else "N/A"
            
            # インデックスのテーブルに行を追加
            idx_f.write(f"<tr>\n")
            idx_f.write(f"<td><a href='{detail_filename}'>{escape(filepath)}</a></td>\n")
            idx_f.write(f"<td class='{status_class}'>{escape(overall_status.upper())}</td>\n")
            idx_f.write(f"<td>{str_slowest}</td>\n")
            idx_f.write(f"<td>{str_heaviest}</td>\n")
            idx_f.write(f"</tr>\n")

            # --- 詳細ページの生成 ---
            with open(detail_filepath, 'w', encoding='utf-8') as det_f:
                det_f.write(f"<!DOCTYPE html>\n<html>\n<head>\n<meta charset='utf-8'>\n<title>Details: {escape(filepath)}</title>\n{css}\n</head>\n<body>\n")
                det_f.write("<div class='container'>\n")
                det_f.write(f"<a class='back-link' href='index.html'>&larr; Back to Index</a>\n")
                det_f.write(f"<h2>File: {escape(filepath)}</h2>\n")
                
                for ver in verifications:
                    v_name = ver.get("verification_name", "N/A")
                    v_status = ver.get("status", "N/A")
                    v_class = get_status_class(v_status)
                    
                    det_f.write(f"<h3>Verification: {escape(v_name)}</h3>\n")
                    det_f.write("<div class='summary-box'>\n")
                    det_f.write("<ul>\n")
                    det_f.write(f"<li><strong>Status:</strong> <span class='{v_class}'>{escape(v_status.upper())}</span></li>\n")
                    
                    if "elapsed" in ver:
                        det_f.write(f"<li><strong>Elapsed:</strong> {ver['elapsed']:.3f} s</li>\n")
                    if "slowest" in ver:
                        det_f.write(f"<li><strong>Slowest:</strong> {ver['slowest']:.3f} s</li>\n")
                    if "heaviest" in ver:
                        det_f.write(f"<li><strong>Heaviest:</strong> {ver['heaviest']:.3f} MB</li>\n")
                    if "last_execution_time" in ver:
                        det_f.write(f"<li><strong>Last Execution:</strong> {escape(ver['last_execution_time'])}</li>\n")
                    det_f.write("</ul>\n")
                    det_f.write("</div>\n")
                    
                    testcases = ver.get("testcases", [])
                    if testcases:
                        det_f.write("<table>\n")
                        det_f.write("<tr><th>Testcase Name</th><th>Status</th><th>Elapsed (s)</th><th>Memory (MB)</th></tr>\n")
                        for tc in testcases:
                            tc_name = tc.get("name", "N/A")
                            tc_status = tc.get("status", "N/A")
                            tc_class = get_status_class(tc_status)
                            
                            # f-string のフォーマットエラーを修正
                            tc_elapsed = tc.get("elapsed", "N/A")
                            if isinstance(tc_elapsed, (float, int)):
                                fmt_elapsed = f"{tc_elapsed:.3f}"
                            else:
                                fmt_elapsed = escape(tc_elapsed)
                                
                            tc_memory = tc.get("memory", "N/A")
                            if isinstance(tc_memory, (float, int)):
                                fmt_memory = f"{tc_memory:.3f}"
                            else:
                                fmt_memory = escape(tc_memory)
                            
                            det_f.write("<tr>\n")
                            det_f.write(f"<td>{escape(tc_name)}</td>\n")
                            det_f.write(f"<td class='{tc_class}'>{escape(tc_status)}</td>\n")
                            det_f.write(f"<td>{fmt_elapsed}</td>\n")
                            det_f.write(f"<td>{fmt_memory}</td>\n")
                            det_f.write("</tr>\n")
                        det_f.write("</table>\n")
                    else:
                        det_f.write("<p><em>No testcase details available.</em></p>\n")
                        
                det_f.write("</div>\n</body>\n</html>\n")

        idx_f.write("</table>\n")
        idx_f.write("</div>\n</body>\n</html>\n")

    print(f"HTML generation complete! Please open '{os.path.join(output_dir, 'index.html')}' in your browser.")

if __name__ == "__main__":
    # ファイル名をご指定の「verify_result.json」に変更しています
    INPUT_JSON = ".competitive-verifier/verify_result.json" 
    OUTPUT_DIR = ".competitive-verifier/html_output"
    
    if os.path.exists(INPUT_JSON):
        generate_html(INPUT_JSON, OUTPUT_DIR)
    else:
        print(f"Error: Could not find '{INPUT_JSON}'. Please check the file path.")
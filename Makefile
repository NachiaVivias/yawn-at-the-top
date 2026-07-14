PHONY: build verify serve

build: notebook.pdf

verify: .competitive-verifier/verify_result.json $(wildcard src/*/* test/* test/*/*)
	mkdir -p .competitive-verifier/verify_result
	competitive-verifier oj-resolve --config ".competitive-verifier/config.toml" >.competitive-verifier/resolve.json
	seq 0 2 | xargs -L 1 -P 3 -I {} bash -c 'competitive-verifier verify --split 3 --split-index {} --verify-json .competitive-verifier/resolve.json >.competitive-verifier/verify_result/{}.json 2>.competitive-verifier/verify_result/err_{}.txt'
	competitive-verifier merge-result .competitive-verifier/verify_result/*.json >.competitive-verifier/verify_result.json
	python3 .competitive-verifier/verify_result_to_html.py

URL = "http://127.0.0.1:4000"

.competitive-verifier/_jekyll/Gemfile:
	cd .competitive-verifier/_jekyll && bundle config set --local path '.vendor/bundle'
	cd .competitive-verifier/_jekyll && bundle install

serve: .competitive-verifier/_jekyll/Gemfile
	competitive-verifier docs --verify-json .competitive-verifier/resolve.json .competitive-verifier/verify_result.json
	cd .competitive-verifier/_jekyll && echo "repository: NachiaVivias/yawn-at-the-top" >> _config.yml
	cd .competitive-verifier/_jekyll && bundle exec jekyll serve --incremental

notebook.pdf: build/base.css build/notebook.css build/notebook.html
	vivliostyle build build/notebook.html -o notebook.pdf

build/notebook.html: build/build.js build/build_setting.toml $(wildcard src/*/* src/*/*/*) .clang-format
	node build/build.js

build/notebook.css: build/build.js
	node build/build.js

.competitive-verifier/verify_result.json:
	mkdir -p .competitive-verifier
	[ ! -f .competitive-verifier/verify_result.json ] && echo "{}" > .competitive-verifier/verify_result.json


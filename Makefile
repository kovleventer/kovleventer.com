SCSS_COMPILER := sass --no-source-map
PYTHON_3 := python3
CHEERP := /opt/cheerp/bin/clang++

.PHONY: all, clean, html, run

CHEERP_FLAGS := -target cheerp -cheerp-mode=wasm -O2 -Isrc/lib

BLOG_ENTRIES := $(shell find src/blog -type f -name config.yaml)
BLOG_FOLDERS := $(patsubst %config.yaml, %, $(BLOG_ENTRIES))
BLOG_BUILD_FOLDERS := $(patsubst src%, build%, $(BLOG_FOLDERS))
BLOG_HTMLS := $(patsubst %, %index.html, $(BLOG_BUILD_FOLDERS))
BLOG_JS := $(patsubst %, %script.js, $(BLOG_BUILD_FOLDERS))
BLOG_WASM := $(patsubst %, %script.wasm, $(BLOG_BUILD_FOLDERS))
BLOG_MEDIA := $(patsubst %, %media, $(BLOG_BUILD_FOLDERS))

STYLES := $(shell find src -type f -name style_*.scss)
BUILD_STYLES := $(patsubst %.scss, %.css, $(patsubst src/style%, build%,$(STYLES)))


all: | html $(BUILD_STYLES) $(BLOG_HTMLS) $(BLOG_MEDIA) $(BLOG_JS) $(BLOG_WASM) 

build/%.css: src/style/%.scss src/style/style.scss
	$(SCSS_COMPILER) $< $@

TEMPLATE_COMPILER := src/site_gen.py
html:
	mkdir -p build
	$(PYTHON_3) $(TEMPLATE_COMPILER)
	cp src/utilities.js build/utilities.js
	cp src/favicon.ico build/favicon.ico

BLOG_TEMPLATE_COMPILER := src/blog/blog_gen.py
build/blog/%index.html: src/blog/%index.html src/blog/% $(BLOG_TEMPLATE_COMPILER)
	mkdir -p build/blog/$* # TODO fix this redundancy
	$(PYTHON_3) $(BLOG_TEMPLATE_COMPILER) src/blog/$*
	
LIB_FILES = $(shell find src/lib -type f -name *.hpp)
build/blog/%script.wasm: src/blog/%script.cpp $(LIB_FILES) #build/blog/%
	mkdir -p build/blog/$*
	$(CHEERP) $(CHEERP_FLAGS) -cheerp-wasm-loader=$(patsubst %.wasm,%.js,$@) -o $@ $<
	
build/blog/%script.js: build/blog/%script.wasm
	
build/blog/%media: src/blog/%media
	mkdir -p build/blog/$*
	cp -r $< $@

# Empty rules
build/blog/%script.js:;
build/blog/%script.wasm:;
build/blog/%media:;

#build/blog/%/:
	#mkdir -p $@

clean:
	rm -rf build

run:
	$(PYTHON_3) server.py


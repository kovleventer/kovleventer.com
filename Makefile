SCSS_COMPILER := sass --no-source-map
PYTHON_3 := python3
CHEERP := /opt/cheerp/bin/clang++
TSC := tsc

.PHONY: all, clean, html, run

CHEERP_LIB := src/lib/cheerp
CHEERP_BASE_NAME := chscript
TS_BASE_NAME := tscript

CHEERP_FLAGS := -target cheerp -cheerp-mode=wasm -O2 -I$(CHEERP_LIB)

BLOG_ENTRIES := $(shell find src/blog -type f -name config.yaml)
BLOG_FOLDERS := $(patsubst %config.yaml, %, $(BLOG_ENTRIES))
BLOG_BUILD_FOLDERS := $(patsubst src%, build%, $(BLOG_FOLDERS))
BLOG_HTMLS := $(patsubst %, %index.html, $(BLOG_BUILD_FOLDERS))
BLOG_CHJS := $(patsubst %, %$(CHEERP_BASE_NAME).js, $(BLOG_BUILD_FOLDERS))
BLOG_CHWASM := $(patsubst %, %$(CHEERP_BASE_NAME).wasm, $(BLOG_BUILD_FOLDERS))
BLOG_TS := $(patsubst %, %$(TS_BASE_NAME).js, $(BLOG_BUILD_FOLDERS))
BLOG_MEDIA := $(patsubst %, %media, $(BLOG_BUILD_FOLDERS))

STYLES := $(shell find src -type f -name style_*.scss)
BUILD_STYLES := $(patsubst %.scss, %.css, $(patsubst src/style%, build%,$(STYLES)))


all: | html $(BUILD_STYLES) $(BLOG_HTMLS) $(BLOG_MEDIA) $(BLOG_CHJS) $(BLOG_CHWASM) $(BLOG_TS)

build/%.css: src/style/%.scss src/style/style.scss
	$(SCSS_COMPILER) $< $@

TEMPLATE_COMPILER := src/site_gen.py
html:
	mkdir -p build
	$(PYTHON_3) $(TEMPLATE_COMPILER)
	cp src/utilities.js build/utilities.js
	cp src/favicon.ico build/favicon.ico
	cp -r src/res build/

BLOG_TEMPLATE_COMPILER := src/blog/blog_gen.py
build/blog/%index.html: src/blog/%index.html src/blog/% $(BLOG_TEMPLATE_COMPILER)
	mkdir -p build/blog/$* # TODO fix this redundancy
	$(PYTHON_3) $(BLOG_TEMPLATE_COMPILER) src/blog/$*
	
LIB_FILES = $(shell find $(CHEERP_LIB) -type f -name *.hpp)
build/blog/%$(CHEERP_BASE_NAME).wasm: src/blog/%$(CHEERP_BASE_NAME).cpp $(LIB_FILES) #build/blog/%
	mkdir -p build/blog/$*
	$(CHEERP) $(CHEERP_FLAGS) -cheerp-wasm-loader=$(patsubst %.wasm,%.js,$@) -o $@ $<
	
build/blog/%$(CHEERP_BASE_NAME).js: build/blog/%$(CHEERP_BASE_NAME).wasm

build/blog/%$(TS_BASE_NAME).js: src/blog/%$(TS_BASE_NAME).ts
	mkdir -p build/blog/$*
	$(TSC) --outFile $@ $<
	
build/blog/%media: src/blog/%media
	mkdir -p build/blog/$*
	cp -r $< build/blog/$*

# Empty rules
build/blog/%$(CHEERP_BASE_NAME).js:;
build/blog/%$(CHEERP_BASE_NAME).wasm:;
build/blog/%$(TS_BASE_NAME).js:;
build/blog/%media:;

#build/blog/%/:
	#mkdir -p $@

clean:
	rm -rf build

run:
	$(PYTHON_3) server.py


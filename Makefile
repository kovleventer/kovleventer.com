SCSS_COMPILER := sass --no-source-map
PYTHON_3 := python3

.PHONY: all, clean, html


all: style html

style:
	$(SCSS_COMPILER) src/style/style_blue.scss build/style_blue.css
	$(SCSS_COMPILER) src/style/style_green.scss build/style_green.css
	$(SCSS_COMPILER) src/style/style_red.scss build/style_red.css
	$(SCSS_COMPILER) src/style/style_yellow.scss build/style_yellow.css
	

TEMPLATE_COMPILER := src/jinjagen.py
html:
	$(PYTHON_3) $(TEMPLATE_COMPILER)
	cp src/utilities.js build/utilities.js



clean:
	rm -rf build
	

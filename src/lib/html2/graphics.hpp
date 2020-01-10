#pragma once

#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "canvas.hpp"

using CanvasPTR = int;

class [[cheerp::genericjs]] Graphics {
private:
	static Canvas* storage[128]; // Oh god this is terrible
	static CanvasPTR ID;
public:
	static CanvasPTR createCanvas(const char* name, int width, int height) {
		storage[ID] = new Canvas(name, width, height);
		ID++;
		return ID - 1;
	}
	
	// Delegate stuff
	
	static void fillRect(CanvasPTR id, int x, int y, int width, int height, int rgb) {
		storage[id]->fillRect(x, y, width, height, rgb);
	}
	
	static void drawRect(CanvasPTR id, int x, int y, int width, int height, int rgb) {
		storage[id]->drawRect(x, y, width, height, rgb);
	}
	
	static void drawText(CanvasPTR id, const char* str, int x, int y, int rgb, const char* textAlign="center", const char* textBaseline="middle", int fontSize=20) {
		storage[id]->drawText(str, x, y, rgb, textAlign, textBaseline, fontSize);
	}
	
	static void clear(CanvasPTR id) {
		storage[id]->clear();
	}
	
	static void addEventListener(CanvasPTR id, const char* event, client::EventListener* cb) {
		storage[id]->addEventListener(event, cb);
	}
};

CanvasPTR Graphics::ID = 0;

Canvas* Graphics::storage[128] = {0};

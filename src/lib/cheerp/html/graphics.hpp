#pragma once

#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "canvas.hpp"

using CanvasPTR = int;

#define _CANVAS_STORAGE_SIZE 128

class [[cheerp::genericjs]] Graphics {
private:
	static Canvas* storage[_CANVAS_STORAGE_SIZE]; // Oh god this is terrible
	static CanvasPTR ID;
	
	static void renderLoop() {
		for (CanvasPTR id = 0; id < ID; id++) {
			if (storage[id]->getRenderCallback() != nullptr) {
				//std::cout << storage[id]->getRenderCallback() << std::endl;
				storage[id]->getRenderCallback()();
				//std::cout << "esdf" << std::endl;
			}
		}
		client::requestAnimationFrame(cheerp::Callback(renderLoop));
	}
public:
	static CanvasPTR createCanvas(const char* name, int width, int height) {
		storage[ID] = new Canvas(name, width, height);
		if (ID == 0) {
			client::requestAnimationFrame(cheerp::Callback(renderLoop));
		}
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
	
	static void fillCircle(CanvasPTR id, int x, int y, int radius, float sAngle, float eAngle, int rgb) {
		storage[id]->fillCircle(x, y, radius, sAngle, eAngle, rgb);
	}
	
	static void drawCircle(CanvasPTR id, int x, int y, int radius, float sAngle, float eAngle, int rgb) {
		storage[id]->drawCircle(x, y, radius, sAngle, eAngle, rgb);
	}
	
	static void drawLine(CanvasPTR id, int x1, int y1, int x2, int y2, int rgb) {
		storage[id]->drawLine(x1, y1, x2, y2, rgb);
	}
	
	static void setLineWidth(CanvasPTR id, int w) {
		storage[id]->setLineWidth(w);
	}
	
	static void clear(CanvasPTR id) {
		storage[id]->clear();
	}
	
	static void addEventListener(CanvasPTR id, const char* event, client::EventListener* cb) {
		storage[id]->addEventListener(event, cb);
	}
	
	static void setRenderCallback(int id, void (*newRenderFunction)(void)) {
		storage[id]->setRenderCallback(newRenderFunction);
	}
};

CanvasPTR Graphics::ID = 0;

Canvas* Graphics::storage[_CANVAS_STORAGE_SIZE] = {0};

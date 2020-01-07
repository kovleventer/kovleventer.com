#pragma once

#include <cheerp/clientlib.h>
#include <cheerp/client.h>

class [[cheerp::genericjs]] Canvas {
private:
	client::HTMLCanvasElement* canvas;
	client::CanvasRenderingContext2D* canvasCtx;
	int width;
	int height;
public:
	Canvas() {}
	
	Canvas(const char* name, int width, int height) {
		this->width = width;
		this->height = height;
		canvas = (client::HTMLCanvasElement*)client::document.getElementById(name);
		canvas->set_width(width);
		canvas->set_height(height);
		canvasCtx = (client::CanvasRenderingContext2D*)canvas->getContext("2d");
	}
	
	void fillRect(int x, int y, int width, int height, int rgb) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_fillStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->fillRect(x, y, width, height);
	}
	
	void drawRect(int x, int y, int width, int height, int rgb) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_strokeStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->strokeRect(x, y, width, height);
	}
	
	void drawText(const char* str, int x, int y, int rgb) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_font("20px sans-serif");
		canvasCtx->set_fillStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->fillText(str, x, y);
	}
	
	void clear() {
		canvasCtx->clearRect(0, 0, width, height);
	}
	
	// Unsafe hack so delete this latert TODO
	client::HTMLCanvasElement* _getUnderlyingCanvas() {
		return canvas;
	}
};


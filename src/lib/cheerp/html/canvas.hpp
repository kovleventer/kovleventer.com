#pragma once

#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include <iostream>

class [[cheerp::genericjs]] Canvas {
private:
	client::HTMLCanvasElement* canvas;
	client::CanvasRenderingContext2D* canvasCtx;
	void (*renderFunction)(void);
	int width;
	int height;
public:
	Canvas() {}
	
	Canvas(const char* name, int width, int height) {
		this->width = width;
		this->height = height;
		renderFunction = nullptr;
		canvas = (client::HTMLCanvasElement*)client::document.getElementById(name);
		canvas->set_width(width);
		canvas->set_height(height);
		canvasCtx = (client::CanvasRenderingContext2D*)canvas->getContext("2d");
	}
	
	static Canvas createEmptyCanvas(int width, int height) {
		Canvas c;
		c.canvas = (client::HTMLCanvasElement*)client::document.createElement("canvas");
		c.canvas->set_width(width);
		c.canvas->set_height(height);
		c.width = width;
		c.height = height;
		c.canvasCtx = (client::CanvasRenderingContext2D*)(c.canvas->getContext("2d"));
		return c;
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
	
	void drawText(const char* str, int x, int y, int rgb, const char* textAlign="center", const char* textBaseline="middle", int fontSize=20) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_font((std::to_string(fontSize)+"px sans-serif").c_str());
		canvasCtx->set_textAlign(textAlign);
		canvasCtx->set_textBaseline(textBaseline);
		canvasCtx->set_fillStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->fillText(str, x, y);
	}
	
	void drawCircle(int x, int y, int radius, float sAngle, float eAngle, int rgb) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_strokeStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->beginPath();
		canvasCtx->arc(x, y, radius, sAngle, eAngle, true);
		canvasCtx->stroke();
	}
	
	void fillCircle(int x, int y, int radius, float sAngle, float eAngle, int rgb) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_fillStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->beginPath();
		canvasCtx->moveTo(x, y);
		canvasCtx->arc(x, y, radius, sAngle, eAngle, true);
		canvasCtx->lineTo(x, y);
		canvasCtx->fill(); 
	}
	
	void drawLine(int x1, int y1, int x2, int y2, int rgb) {
		int r = (rgb>>16)&0xff;
		int g = (rgb>>8)&0xff;
		int b = rgb&0xff;
		canvasCtx->set_strokeStyle(client::String("").concat("rgb(", r, ",", g, ",", b, ")"));
		canvasCtx->beginPath();
		canvasCtx->moveTo(x1, y1);
		canvasCtx->lineTo(x2, y2);
		canvasCtx->stroke(); 
	}
	
	void blitCanvas(Canvas& c) {
		canvasCtx->drawImage(c.canvas, 0, 0, c.width, c.height, 0, 0, width, height);
	}
	
	void setLineWidth(int w) {
		canvasCtx->set_lineWidth(w);
	}
	
	void clear() {
		canvasCtx->clearRect(0, 0, width, height);
	}
	
	void addEventListener(const char* event, client::EventListener* cb) {
		canvas->addEventListener(event, cb);
	}
	
	void (*getRenderCallback(void))(void) {
		return renderFunction;
	}
	
	void setRenderCallback(void (*newRenderFunction)(void)) {
		renderFunction = newRenderFunction;
	}
	
	// Unsafe hack so delete this later TODO
	client::HTMLCanvasElement* _getUnderlyingCanvas() {
		return canvas;
	}
};


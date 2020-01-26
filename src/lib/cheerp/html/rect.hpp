#pragma once

#include "shape.hpp"
#include "../color.hpp"

#include <string>
#include <iostream>

class Rect : public Shape {
public:
	int x, y, w, h;
	std::string text;
	int textSize;
public:
	Rect(int x, int y, int w, int h, int fillColor, int textSize=17, int strokeColor=Color::BLACK) : Shape(fillColor, strokeColor), x(x), y(y), w(w), h(h), text(""), textSize(textSize) {}
	
	void setText(std::string text) {
		this->text = text;
	}
	
	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}
	
	int getW() {
		return w;
	}
	
	int getH() {
		return h;
	}
	
	bool contains(int X, int Y) {
		return x <= X && x+w > X && y <= Y && y+h > Y;
	}
	
	void setTextSize(int newTextSize) {
		textSize = newTextSize;
	}
	
	void render(CanvasPTR id) {
		Graphics::fillRect(id, x, y, w, h, fillColor);
		Graphics::drawRect(id, x, y, w, h, strokeColor);
		Graphics::drawText(id, text.c_str(), x+w/2, y+h/2, strokeColor, "center", "middle", textSize);
	}
};

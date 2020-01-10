#pragma once

#include "shape.hpp"
#include "../color.hpp"

class Rect : public Shape {
private:
	int x, y, w, h;
public:
	Rect(int x, int y, int w, int h, int fillColor, int strokeColor=Color::BLACK) : Shape(fillColor, strokeColor), x(x), y(y), w(w), h(h) {}
	
	void render() {
		
	}
};

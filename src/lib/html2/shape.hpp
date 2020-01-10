#pragma once

#include "renderable.hpp"

class Shape : public Renderable {
protected:
	int fillColor, strokeColor;
	Shape(int fillColor, int strokeColor) : fillColor(fillColor), strokeColor(strokeColor) {}
public:
	
	int getFillColor() {
		return fillColor;
	}
	
	int getStrokeColor() {
		return strokeColor;
	}
	
	void setFillColor(int newFillColor) {
		fillColor = newFillColor;
	}
	
	void setStrokeColor(int newStrokeColor) {
		strokeColor = newStrokeColor;
	}
	
	virtual bool contains(int X, int Y) = 0;
	
	virtual void render(CanvasPTR id) = 0;
};

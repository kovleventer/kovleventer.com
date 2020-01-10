#pragma once

#include "renderable.hpp"

class Shape : public Renderable {
protected:
	int fillColor, strokeColor;
public:
	virtual void render() = 0;
};

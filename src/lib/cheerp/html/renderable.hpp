#pragma once

#include <cheerp/clientlib.h>

#include "graphics.hpp"

class Renderable {
public:
	virtual void render(CanvasPTR id) = 0;//= 0;
	
	virtual ~Renderable() {}
};

#pragma once

#include <cheerp/clientlib.h>

class Renderable {
public:
	virtual void render() = 0;//= 0;
	
	virtual ~Renderable() {}
};

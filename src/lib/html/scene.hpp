#pragma once

#include <vector>
#include <iostream>

#include "renderable.hpp"
#include "graphics.hpp"

class Scene {
private:
	std::vector<Renderable*> elements;
public:
	Scene() {}
	
	void addElement(Renderable* element) {
		elements.push_back(element);
	}
	
	void render(CanvasPTR id) {
		Graphics::clear(id);
		for (Renderable* element : elements) {
			element->render(id);
		}
	}
	
	
};

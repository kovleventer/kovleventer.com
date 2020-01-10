#pragma once

#include <vector>

#include "renderable.hpp"
#include "htmlcanvas.hpp"

class Scene {
private:
	std::vector<Renderable*> elements;
public:
	Scene();
	
	void addElement(Renderable* element) {
		elements.push_back(element);
	}
	
	std::vector<Renderable*> __getElements() {
		return elements;
	}
};

[[cheerp::genericjs]] void Scene_render(Scene& s, Canvas* canvas) {
	auto elements = s.__getElements();
	for (Renderable* element : elements) {
		element->render();
	}
}



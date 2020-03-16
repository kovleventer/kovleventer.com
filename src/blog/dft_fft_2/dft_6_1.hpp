#pragma once

#include "html/canvas.hpp"
#include "html/input.hpp"
#include "math/matrix.hpp"
#include "math/complex.hpp"
#include "color.hpp"
#include "html/graphics.hpp"
#include "html/scene.hpp"
#include "html/rect.hpp"

#include <cmath>
#include <iomanip>

namespace dft_6_1 {

Scene scene;
CanvasPTR canvasPTR;
std::vector<Rect*> elements;

void constructMatrices() {
	int padding = 30;
	int s = 50;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			Rect* r = new Rect(s * x, 6 * s + padding + y * s, s, s, x % 2 ? Color::MAT_PINK_50 : Color::MAT_RED_50, 15);
			scene.addElement(r);
			elements.push_back(r);
		}
	}
	for (int y = 0; y < 6; y++) {
		Rect* r = new Rect(6 * s + padding, y * s, s, s, y % 2 ? Color::MAT_LBLUE_50 : Color::MAT_CYAN_50, 15);
		r->setText(std::string("s")+std::to_string(y+1));
		elements.push_back(r);
		scene.addElement(r);
	}
	for (int y = 0; y < 6; y++) {
		Rect* r = new Rect(6 * s + padding, 6 * s + padding + y * s, s, s, Color::MAT_GREEN_50, 15);
		r->setText(std::string("C")+std::to_string(y+1));
		elements.push_back(r);
		scene.addElement(r);
	}
}

void mouseMoveImpl(int X, int Y) {
	bool wasSelected = false;
	for (int y = 0; y < 6; y++) {
		if (elements[42+y]->contains(X, Y)) {
			elements[42+y]->setFillColor(Color::MAT_GREEN_300);
			for (int x = 0; x < 6; x++) {
				elements[y*6+x]->setFillColor(x % 2 ? Color::MAT_PINK_300 : Color::MAT_RED_300);
			}
			wasSelected = true;
			
		} else {
			elements[42+y]->setFillColor(Color::MAT_GREEN_50);
			for (int x = 0; x < 6; x++) {
				elements[y*6+x]->setFillColor(x % 2 ? Color::MAT_PINK_50 : Color::MAT_RED_50);
			}
		}
	}
	
	for (int y = 0; y < 6; y++) {
		elements[36+y]->setFillColor(wasSelected ? (y % 2 ? Color::MAT_LBLUE_300 : Color::MAT_CYAN_300) : (y % 2 ? Color::MAT_LBLUE_50 : Color::MAT_CYAN_50));
	}
	scene.render(canvasPTR);
}

void mouseMove(client::MouseEvent* e) {
	mouseMoveImpl(e->get_offsetX(), e->get_offsetY());
}

void mouseExit(client::MouseEvent* e) {
	mouseMoveImpl(-100, -100);
}

void init() {
	scene = Scene();
	int w=400, h=650;
	canvasPTR = Graphics::createCanvas("dft_6_1", w, h);
	Graphics::addEventListener(canvasPTR, "mousemove", cheerp::Callback(mouseMove));
	Graphics::addEventListener(canvasPTR, "mouseout", cheerp::Callback(mouseExit));
	
	constructMatrices();

	scene.render(canvasPTR);
}
}


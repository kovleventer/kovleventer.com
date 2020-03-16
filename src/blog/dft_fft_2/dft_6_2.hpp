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

namespace dft_6_2 {

Scene scene;
CanvasPTR canvasPTR;
std::vector<Rect*> elements1, elements2, result;

void constructMatrices() {
	int padding = 30;
	int s = 50;
	int padParts = 3*s+padding*5;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 3; x++) {
			Rect* r = new Rect(s * x, 3 * s + padding + y * s, s, s, Color::MAT_RED_50, 15);
			scene.addElement(r);
			elements1.push_back(r);
		}
	}
	for (int y = 0; y < 3; y++) {
		Rect* r = new Rect(3 * s + padding, y * s, s, s, Color::MAT_CYAN_50, 15);
		r->setText(std::string("s")+std::to_string(y*2+1));
		elements1.push_back(r);
		scene.addElement(r);
	}
	for (int y = 0; y < 6; y++) {
		Rect* r = new Rect(3 * s + padding, 3 * s + padding + y * s, s, s, Color::MAT_YELLOW_50, 15);
		r->setText(std::string("A")+std::to_string(y+1));
		elements1.push_back(r);
		scene.addElement(r);
	}
	
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 3; x++) {
			Rect* r = new Rect(s * x + padParts, 3 * s + padding + y * s, s, s, Color::MAT_PINK_50, 15);
			scene.addElement(r);
			elements2.push_back(r);
		}
	}
	for (int y = 0; y < 3; y++) {
		Rect* r = new Rect(3 * s + padding + padParts, y * s, s, s, Color::MAT_LBLUE_50, 15);
		r->setText(std::string("s")+std::to_string(y*2+2));
		elements2.push_back(r);
		scene.addElement(r);
	}
	for (int y = 0; y < 6; y++) {
		Rect* r = new Rect(3 * s + padding + padParts, 3 * s + padding + y * s, s, s, Color::MAT_LIME_50, 15);
		r->setText(std::string("B")+std::to_string(y+1));
		elements2.push_back(r);
		scene.addElement(r);
	}
	
	for (int y = 0; y < 6; y++) {
		Rect* r = new Rect(3 * s + padding + padParts+s+padding*2, 3 * s + padding + y * s, s, s, Color::MAT_GREEN_50, 15);
		r->setText(std::string("C")+std::to_string(y+1));
		result.push_back(r);
		scene.addElement(r);
	}
}

void mouseMoveImpl(int X, int Y) {
	bool wasSelected = false;
	for (int y = 0; y < 6; y++) {
		if (result[y]->contains(X, Y)) {
			result[y]->setFillColor(Color::MAT_GREEN_300);
			elements1[21+y]->setFillColor(Color::MAT_YELLOW_300);
			elements2[21+y]->setFillColor(Color::MAT_LIME_300);
			for (int x = 0; x < 3; x++) {
				elements1[y*3+x]->setFillColor(Color::MAT_RED_300);
				elements2[y*3+x]->setFillColor(Color::MAT_PINK_300);
			}
			wasSelected = true;
			
		} else {
			result[y]->setFillColor(Color::MAT_GREEN_50);
			elements1[21+y]->setFillColor(Color::MAT_YELLOW_50);
			elements2[21+y]->setFillColor(Color::MAT_LIME_50);
			for (int x = 0; x < 3; x++) {
				elements1[y*3+x]->setFillColor(Color::MAT_RED_50);
				elements2[y*3+x]->setFillColor(Color::MAT_PINK_50);
			}
		}
	}
	
	for (int y = 0; y < 3; y++) {
		elements1[18+y]->setFillColor(wasSelected ? Color::MAT_CYAN_300 : Color::MAT_CYAN_50);
		elements2[18+y]->setFillColor(wasSelected ? Color::MAT_LBLUE_300 : Color::MAT_LBLUE_50);
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
	int w=650, h=500;
	canvasPTR = Graphics::createCanvas("dft_6_2", w, h);
	Graphics::addEventListener(canvasPTR, "mousemove", cheerp::Callback(mouseMove));
	Graphics::addEventListener(canvasPTR, "mouseout", cheerp::Callback(mouseExit));
	
	constructMatrices();

	scene.render(canvasPTR);
}
}


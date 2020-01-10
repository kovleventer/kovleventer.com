#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "html2/scene.hpp"
#include "html2/graphics.hpp"
#include "html2/rect.hpp"
#include "math/matrix.hpp"
#include "color.hpp"

#include <vector>
#include <iostream>
#include <locale>

extern "C" [[cheerp::genericjs]] [[cheerp::jsexport]]
void hi_freq() {
	client::HTMLImageElement* element = static_cast<client::HTMLImageElement*>(client::document.getElementById("signal"));
	element->set_src("media/signal_hifreq.png");
}

extern "C" [[cheerp::genericjs]] [[cheerp::jsexport]]
void lo_freq() {
	client::HTMLImageElement* element = static_cast<client::HTMLImageElement*>(client::document.getElementById("signal"));
	element->set_src("media/signal_lowfreq.png");
}

Scene synthesisMTX;
CanvasPTR synthesisMTXCanvas;
std::vector<Rect*> synthMTXelements;

void mouseMove(int X, int Y) {
	bool wasSelected = false;
	for (int y = 0; y < 3; y++) {
		if (synthMTXelements[12+y]->contains(X, Y)) {
			synthMTXelements[12+y]->setFillColor(Color::MAT_GREEN_300);
			for (int x = 0; x < 3; x++) {
				synthMTXelements[y*3+x]->setFillColor(Color::MAT_RED_300);
			}
			wasSelected = true;
			
		} else {
			synthMTXelements[12+y]->setFillColor(Color::MAT_GREEN_50);
			for (int x = 0; x < 3; x++) {
				synthMTXelements[y*3+x]->setFillColor(Color::MAT_RED_50);
			}
		}
	}
	
	for (int y = 0; y < 3; y++) {
		synthMTXelements[9+y]->setFillColor(wasSelected ? Color::MAT_CYAN_300 : Color::MAT_CYAN_50);
	}
	synthesisMTX.render(synthesisMTXCanvas);
}

[[cheerp::genericjs]]
void mouseMoveJS(client::MouseEvent* e) {
	mouseMove(e->get_offsetX(), e->get_offsetY());
}

[[cheerp::genericjs]]
void mouseExitJS(client::MouseEvent* e) {
	mouseMove(-100, -100);
}

void constructSynthMatrices() {
	int padding = 30;
	int s = 60;
	int sw = 140;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			Rect* r = new Rect(sw * x, 3 * s + padding + y * s, sw, s, Color::MAT_RED_50);
			r->setText(std::string("cos(2*pi*f")+std::to_string(x+1)+std::string("*x")+std::to_string(y+1)+std::string(")")); // TODO use π instead of pi
			synthesisMTX.addElement(r);
			synthMTXelements.push_back(r);
		}
	}
	for (int y = 0; y < 3; y++) {
		Rect* r = new Rect(3 * sw + padding, y * s, s, s, Color::MAT_CYAN_50);
		r->setText(std::string("A")+std::to_string(y+1));
		synthMTXelements.push_back(r);
		synthesisMTX.addElement(r);
	}
	for (int y = 0; y < 3; y++) {
		Rect* r = new Rect(3 * sw + padding, 3 * s + padding + y * s, s, s, Color::MAT_GREEN_50);
		r->setText(std::string("s(x")+std::to_string(y+1)+std::string(")"));
		synthMTXelements.push_back(r);
		synthesisMTX.addElement(r);
	}
}

[[cheerp::genericjs]]
void initSynth() {
	synthesisMTX = Scene();
	int w=520, h=400;
	synthesisMTXCanvas = Graphics::createCanvas("synthesis_matrix", w, h);
	Graphics::addEventListener(synthesisMTXCanvas, "mousemove", cheerp::Callback(mouseMoveJS));
	Graphics::addEventListener(synthesisMTXCanvas, "mouseout", cheerp::Callback(mouseExitJS));
	
	constructSynthMatrices();

	synthesisMTX.render(synthesisMTXCanvas);
}

[[cheerp::genericjs]] void webMain() {
	initSynth();
}
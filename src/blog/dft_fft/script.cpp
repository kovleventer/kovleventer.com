#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "html/scene.hpp"
#include "html/graphics.hpp"
#include "html/rect.hpp"
#include "math/matrix.hpp"
#include "color.hpp"

#include <vector>
#include <iostream>
#include <locale>
#include <cmath>

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

CanvasPTR expSinCosCanvas;
double t = 0;

void updateExp() {
	Graphics::clear(expSinCosCanvas);
	t -= 0.02;
	int r = 100;
	int w = 500;
	int h = 500;
	int rr = 10;
	Graphics::setLineWidth(expSinCosCanvas, 4);
	
	Graphics::fillCircle(expSinCosCanvas, r+rr, h-r-rr, 30, 0, std::fmod(t, 2 * M_PI), Color::MAT_YELLOW_300);
	Graphics::drawCircle(expSinCosCanvas, r+rr, h-r-rr, 30, 0, std::fmod(t, 2 * M_PI), Color::MAT_YELLOW_700);
	
	Graphics::setLineWidth(expSinCosCanvas, 2);
	
	Graphics::drawCircle(expSinCosCanvas, r+rr, h-r-rr, r, 0, 2 * M_PI, Color::GRAY);
	Graphics::drawLine(expSinCosCanvas, r+rr, 0, r+rr, h, Color::GRAY);
	Graphics::drawLine(expSinCosCanvas, 0, h-r-rr, w, h-r-rr, Color::GRAY);
	
	
	
	for (int i = 0; i < 400; i++) {
		double t_1 = t + i * 0.09;
		double t_2 = t + (i+1) * 0.09;
		
		Graphics::drawLine(expSinCosCanvas, r+rr + std::cos(t_1)*r, h-r-rr-r-(t_1 - t)*10, r+rr + std::cos(t_2)*r, h-r-rr-r-(t_2 - t)*10, Color::MAT_CYAN_700);
		Graphics::drawLine(expSinCosCanvas, rr+r+r+(t_1 - t)*10, h-r-rr + std::sin(t_1)*r, rr+r+r+(t_2 - t)*10, h-r-rr + std::sin(t_2)*r, Color::MAT_GREEN_700);
	}
	
	
	
	Graphics::drawLine(expSinCosCanvas, r+rr + std::cos(t)*r, h-r-rr + std::sin(t)*r, r+rr + std::cos(t)*r, h-r-rr-r, Color::MAT_CYAN_300);
	Graphics::drawLine(expSinCosCanvas, r+rr + std::cos(t)*r, h-r-rr + std::sin(t)*r, rr+r+r, h-r-rr + std::sin(t)*r, Color::MAT_GREEN_300);
	
	Graphics::drawLine(expSinCosCanvas, r+rr + std::cos(t)*r, h-r-rr + std::sin(t)*r, r + rr, h-r-rr, Color::GRAY);
	
	
	
	
	
	Graphics::fillCircle(expSinCosCanvas, r+rr + std::cos(t)*r, h-r-rr + std::sin(t)*r, rr, 0, 2 * M_PI, Color::MAT_RED_700);
	
	
}


[[cheerp::genericjs]]
void updateExpJS(void) {
	updateExp();
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

[[cheerp::genericjs]]
void initExp() {
	expSinCosCanvas = Graphics::createCanvas("expo_sin_cos", 500, 500);
	Graphics::setRenderCallback(synthesisMTXCanvas, updateExpJS);
}

[[cheerp::genericjs]]
void webMain() {
	initSynth();
	initExp();
}

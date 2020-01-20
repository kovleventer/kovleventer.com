#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "html/scene.hpp"
#include "html/graphics.hpp"
#include "html/rect.hpp"
#include "html/input.hpp"
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

void mouseMoveSynth(int X, int Y) {
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
	mouseMoveSynth(e->get_offsetX(), e->get_offsetY());
}

[[cheerp::genericjs]]
void mouseExitJS(client::MouseEvent* e) {
	mouseMoveSynth(-100, -100);
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
	double tt = t + 0.6;
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
		double t_1 = t + i * 0.11;
		double t_2 = t + (i+1) * 0.11; // squiggly but idk why
		
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

Scene synthesisSCMTX;
CanvasPTR synthesisSCMTXCanvas;
std::vector<Rect*> synthSCMTXelements;

void constructSynthSCMatrices() {
	int padding = 30;
	int s = 50;
	int sw = 120;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 3; x++) {
			Rect* r = new Rect(sw * x, 6 * s + padding + y * s, sw, s, Color::MAT_RED_50, 15);
			r->setText(std::string("cos(2*pi*f")+std::to_string(x+1)+std::string("*x")+std::to_string(y+1)+std::string(")")); // TODO use π instead of pi
			synthesisSCMTX.addElement(r);
			synthSCMTXelements.push_back(r);
		}
		for (int x = 0; x < 3; x++) {
			Rect* r = new Rect(sw * (x+3), 6 * s + padding + y * s, sw, s, Color::MAT_PINK_50, 15);
			r->setText(std::string("sin(2*pi*f")+std::to_string(x+1)+std::string("*x")+std::to_string(y+1)+std::string(")")); // TODO use π instead of pi
			synthesisSCMTX.addElement(r);
			synthSCMTXelements.push_back(r);
		}
	}
	for (int y = 0; y < 3; y++) {
		Rect* r = new Rect(6 * sw + padding, y * s, s, s, Color::MAT_CYAN_50, 15);
		r->setText(std::string("A")+std::to_string(y+1));
		synthSCMTXelements.push_back(r);
		synthesisSCMTX.addElement(r);
	}
	for (int y = 0; y < 3; y++) {
		Rect* r = new Rect(6 * sw + padding, (y+3) * s, s, s, Color::MAT_LBLUE_50, 15);
		r->setText(std::string("B")+std::to_string(y+1));
		synthSCMTXelements.push_back(r);
		synthesisSCMTX.addElement(r);
	}
	for (int y = 0; y < 6; y++) {
		Rect* r = new Rect(6 * sw + padding, 6 * s + padding + y * s, s, s, Color::MAT_GREEN_50, 15);
		r->setText(std::string("s(x")+std::to_string(y+1)+std::string(")"));
		synthSCMTXelements.push_back(r);
		synthesisSCMTX.addElement(r);
	}
}

void mouseMoveSynthSC(int X, int Y) {
	bool wasSelected = false;
	for (int y = 0; y < 6; y++) {
		if (synthSCMTXelements[42+y]->contains(X, Y)) {
			synthSCMTXelements[42+y]->setFillColor(Color::MAT_GREEN_300);
			for (int x = 0; x < 3; x++) {
				synthSCMTXelements[y*6+x]->setFillColor(Color::MAT_RED_300);
				synthSCMTXelements[y*6+x+3]->setFillColor(Color::MAT_PINK_300);
			}
			wasSelected = true;
			
		} else {
			synthSCMTXelements[42+y]->setFillColor(Color::MAT_GREEN_50);
			for (int x = 0; x < 3; x++) {
				synthSCMTXelements[y*6+x]->setFillColor(Color::MAT_RED_50);
				synthSCMTXelements[y*6+x+3]->setFillColor(Color::MAT_PINK_50);
			}
		}
	}
	
	for (int y = 0; y < 3; y++) {
		synthSCMTXelements[36+y]->setFillColor(wasSelected ? Color::MAT_CYAN_300 : Color::MAT_CYAN_50);
		synthSCMTXelements[36+y+3]->setFillColor(wasSelected ? Color::MAT_LBLUE_300 : Color::MAT_LBLUE_50);
	}
	synthesisSCMTX.render(synthesisSCMTXCanvas);
}

[[cheerp::genericjs]]
void mouseMoveSCJS(client::MouseEvent* e) {
	mouseMoveSynthSC(e->get_offsetX(), e->get_offsetY());
}

[[cheerp::genericjs]]
void mouseExitSCJS(client::MouseEvent* e) {
	mouseMoveSynthSC(-100, -100);
}

CanvasPTR dftWRotCanvas;
[[cheerp::genericjs]] client::HTMLInputElement *dftWRotRange;

void renderDFTWRot(int value) {
	Graphics::clear(dftWRotCanvas);
	
	int w = 400;
	int h = 400;
	int r = 100;
	Graphics::setLineWidth(dftWRotCanvas, 8);
	for (int i = 0; i < 5; i++) {
		Graphics::drawLine(dftWRotCanvas, w/2, h/2, w/2+std::cos(2*M_PI*i/5)*(r), h/2-std::sin(2*M_PI*i/5)*(r), Color::MAT_RED_50);
	}
	Graphics::setLineWidth(dftWRotCanvas, 2);
	Graphics::drawCircle(dftWRotCanvas, w/2, h/2, r, 0, 2*M_PI, Color::GRAY);
	Graphics::drawLine(dftWRotCanvas, w/2, 0, w/2, h, Color::GRAY);
	Graphics::drawLine(dftWRotCanvas, 0, h/2, w, h/2, Color::GRAY);
	Graphics::setLineWidth(dftWRotCanvas, 8);
	Graphics::drawLine(dftWRotCanvas, w/2, h/2, w/2+std::cos(2*M_PI*value/5)*(r+10), h/2-std::sin(2*M_PI*value/5)*(r+10), Color::MAT_RED_700);
	Graphics::drawText(dftWRotCanvas, (std::string("f*t*N=") + std::to_string(value)).c_str(), w*3/4, 40, Color::GRAY, "center", "middle", 30);
}

[[cheerp::genericjs]]
void renderDFTWRotJS() {
	int value = getNumericInput(dftWRotRange);
	renderDFTWRot(value);
}

Scene dftInverse;
CanvasPTR dftInverseCanvas;
std::vector<Rect*> dftInverseElements;

void constructDFTIMatrices() {
	int padding = 30;
	int s = 50;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			Rect* r = new Rect(s * x, 5 * s + padding + y * s, s, s, Color::MAT_RED_50, 15);
			r->setText(std::string("W^")+std::to_string((x*y)%5));
			dftInverse.addElement(r);
			dftInverseElements.push_back(r);
		}
	}
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			Rect* r = new Rect(s * x + 5 * s + padding, y * s, s, s, Color::MAT_CYAN_50, 15);
			r->setText(std::string("W^(-")+std::to_string((x*y)%5)+std::string(")"));
			dftInverse.addElement(r);
			dftInverseElements.push_back(r);
		}
	}
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			Rect* r = new Rect(s * x + 5 * s + padding, 5 * s + padding + y * s, s, s, Color::MAT_GREEN_50, 15);
			r->setText(x==y ? std::string("5") : std::string("0"));
			dftInverse.addElement(r);
			dftInverseElements.push_back(r);
		}
	}
}

void mouseExitDFTI(int X, int Y) {
	
	for (int i = 0; i < 25; i++) {
		dftInverseElements[i]->setFillColor(Color::MAT_RED_50);
		dftInverseElements[25+i]->setFillColor(Color::MAT_CYAN_50);
		dftInverseElements[50+i]->setFillColor(Color::MAT_GREEN_50);
	}
	
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (dftInverseElements[50+y*5+x]->contains(X, Y)) {
				dftInverseElements[50+y*5+x]->setFillColor(Color::MAT_GREEN_300);
				
				for (int z = 0; z < 5; z++) {
					dftInverseElements[y*5+z]->setFillColor(Color::MAT_RED_300);
					dftInverseElements[25+z*5+x]->setFillColor(Color::MAT_CYAN_300);
				}
			}
		}
	}
	
	dftInverse.render(dftInverseCanvas);
}

[[cheerp::genericjs]]
void mouseMoveDFTIJS(client::MouseEvent* e) {
	mouseExitDFTI(e->get_offsetX(), e->get_offsetY());
}

[[cheerp::genericjs]]
void mouseExitDFTIJS(client::MouseEvent* e) {
	mouseExitDFTI(-100, -100);
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
	Graphics::setRenderCallback(expSinCosCanvas, updateExpJS);
}

[[cheerp::genericjs]]
void initSynthSinCos() {
	synthesisSCMTX = Scene();
	int w=850, h=650;
	synthesisSCMTXCanvas = Graphics::createCanvas("synthesis_sin_cos", w, h);
	Graphics::addEventListener(synthesisSCMTXCanvas, "mousemove", cheerp::Callback(mouseMoveSCJS));
	Graphics::addEventListener(synthesisSCMTXCanvas, "mouseout", cheerp::Callback(mouseExitSCJS));
	
	constructSynthSCMatrices();

	synthesisSCMTX.render(synthesisSCMTXCanvas);
}

[[cheerp::genericjs]]
void initDFTWRot() {
	dftWRotCanvas = Graphics::createCanvas("dft_wrot", 400, 400);
	dftWRotRange = static_cast<client::HTMLInputElement*>(client::document.getElementById("dft_wrot_exp"));
	dftWRotRange->addEventListener("input", cheerp::Callback(renderDFTWRotJS));
	renderDFTWRotJS();
}

[[cheerp::genericjs]]
void initDFTInverse() {
	dftInverse = Scene();
	int w=550, h=550;
	dftInverseCanvas = Graphics::createCanvas("dft_inverse", w, h);
	Graphics::addEventListener(dftInverseCanvas, "mousemove", cheerp::Callback(mouseMoveDFTIJS));
	Graphics::addEventListener(dftInverseCanvas, "mouseout", cheerp::Callback(mouseExitDFTIJS));
	
	constructDFTIMatrices();

	dftInverse.render(dftInverseCanvas);
}

[[cheerp::genericjs]]
void webMain() {
	initSynth();
	initExp();
	initSynthSinCos();
	initDFTWRot();
	initDFTInverse();
}

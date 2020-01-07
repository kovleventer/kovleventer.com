#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "htmlcanvas.hpp"

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

[[cheerp::genericjs]] Canvas synthmatrix;

[[cheerp::genericjs]]
void render() {
	synthmatrix.clear();
	
}

void mouseMove() {
	
}

[[cheerp::genericjs]]
void jsInit() {
	synthmatrix = Canvas("dft_matrices", 400, 400);
	synthmatrix._getUnderlyingCanvas()->addEventListener("mouseover", cheerp::Callback(mouseMove));
}

void webMain() {
	jsInit();
	render();
}

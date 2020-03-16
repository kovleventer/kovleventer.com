#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "dft_matrix.hpp"
#include "coloring_demo.hpp"
#include "dft_6_1.hpp"
#include "dft_6_2.hpp"

extern "C" [[cheerp::jsexport]]
void show_even() {
	client::HTMLImageElement* element = static_cast<client::HTMLImageElement*>(client::document.getElementById("evenodd"));
	element->set_src("media/dft_cover_even.png");
}

extern "C" [[cheerp::jsexport]]
void show_even_tb() {
	client::HTMLImageElement* element = static_cast<client::HTMLImageElement*>(client::document.getElementById("evenodd"));
	element->set_src("media/dft_cover_even_tb.png");
}

extern "C" [[cheerp::jsexport]]
void show_odd() {
	client::HTMLImageElement* element = static_cast<client::HTMLImageElement*>(client::document.getElementById("evenodd"));
	element->set_src("media/dft_cover_odd.png");
}

extern "C" [[cheerp::jsexport]]
void show_odd_tb() {
	client::HTMLImageElement* element = static_cast<client::HTMLImageElement*>(client::document.getElementById("evenodd"));
	element->set_src("media/dft_cover_odd_tb.png");
}

void webMain() {
	dftMInit();
	coloring_demo::init();
	dft_6_1::init();
	dft_6_2::init();
}

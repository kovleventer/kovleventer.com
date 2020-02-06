#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "dft_matrix.hpp"
#include "coloring_demo.hpp"

void webMain() {
	dftMInit();
	coloring_demo::init();
}

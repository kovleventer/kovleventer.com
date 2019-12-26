#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "htmlcanvas.hpp"
#include "htmlinput.hpp"
#include "matrix.hpp"
#include "complex.hpp"
#include "color.hpp"

#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

#define MAX_MATRIX_SIZE 10
using CFMatrix = VMatrix<Complex<float>>;

std::vector<CFMatrix> dftMatrices;

[[cheerp::genericjs]] Canvas canvas1;
[[cheerp::genericjs]] client::HTMLInputElement *range, *checkb;

int padding = 20;
int size = 60;
int totalSize = padding * 2 + size * MAX_MATRIX_SIZE;
bool colored = false;

[[cheerp::genericjs]]
void render() {
	canvas1.clear();
	int value = getNumericInput(range);
	colored = checkb->get_checked();
	CFMatrix& matrix = dftMatrices[value-1];
	
	for (int y = 0; y < matrix.getY(); y++) {
		for (int x = 0; x < matrix.getX(); x++) {
			canvas1.drawRect(padding + x * size, padding + y * size, size, size, Color::BLACK);
			Complex<float> value = matrix.get(x, y);
			if (colored) {
				canvas1.fillRect(padding + x * size, padding + y * size, size, size, Color::angleToColor(value.getArg()));
			}
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << value.getArg();
			canvas1.drawText(stream.str().c_str(), padding + x * size + 5, padding + y * size + size / 2 + 10, Color::BLACK);
		}
	}
	
}

[[cheerp::genericjs]]
void jsInit() {
	canvas1 = Canvas("dft_matrices", totalSize, totalSize);
	checkb = static_cast<client::HTMLInputElement*>(client::document.getElementById("dft_colored"));
	range = static_cast<client::HTMLInputElement*>(client::document.getElementById("dft_size"));
	range->addEventListener("input", cheerp::Callback(render));
	checkb->addEventListener("change", cheerp::Callback(render));
}

void generateMatrices() {
	for (int i = 1; i <= MAX_MATRIX_SIZE; i++) {
		CFMatrix current = CFMatrix(i, i);
		for (int ts = 0; ts < i; ts++) {
			for (int fs = 0; fs < i; fs++) {
				current.set(ts, fs, Complex<float>::fromExp(1, 2.0f * M_PI / i * ts * fs));
			}
		}
		
		dftMatrices.push_back(current);
	}
}

void webMain() {
	jsInit();
	generateMatrices();
	render();
}

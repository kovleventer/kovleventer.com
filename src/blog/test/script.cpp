#include <cheerp/clientlib.h>
#include <cheerp/client.h>

#include "html2/canvas.hpp"
#include "html2/input.hpp"
#include "math/matrix.hpp"
#include "math/complex.hpp"
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

int size = 60;
int totalSize = size * MAX_MATRIX_SIZE;
bool colored = false;

[[cheerp::genericjs]]
void render() {
	canvas1.clear();
	int value = getNumericInput(range);
	colored = checkb->get_checked();
	CFMatrix& matrix = dftMatrices[value-1];
	
	for (int y = 0; y < matrix.getY(); y++) {
		for (int x = 0; x < matrix.getX(); x++) {
			canvas1.drawRect(x * size, y * size, size, size, Color::BLACK);
			Complex<float> value = matrix.get(x, y);
			if (colored) {
				canvas1.fillRect(x * size, y * size, size, size, Color::angleToColor(value.getArg()));
			}
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << value.getArg();
			canvas1.drawText(stream.str().c_str(), x * size + 5, y * size + size / 2 + 10, Color::BLACK, "start", "alphabetic");
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

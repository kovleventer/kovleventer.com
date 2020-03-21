#pragma once

#include "html/canvas.hpp"
#include "html/input.hpp"
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

Canvas dftCanvas;
client::HTMLInputElement *dftRange, *dftColored;

int size = 60;
int totalSize = size * MAX_MATRIX_SIZE;
bool dColored = false;

void renderDFT() {
	dftCanvas.clear();
	int value = getNumericInput(dftRange);
	dColored = dftColored->get_checked();
	CFMatrix& matrix = dftMatrices[value-1];
	
	for (int y = 0; y < matrix.getY(); y++) {
		for (int x = 0; x < matrix.getX(); x++) {
			dftCanvas.drawRect(x * size, y * size, size, size, Color::BLACK);
			Complex<float> value = matrix.get(x, y);
			if (dColored) {
				dftCanvas.fillRect(x * size, y * size, size, size, Color::angleToColor(value.getArg()));
			}
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << value.getArg();
			dftCanvas.drawText(stream.str().c_str(), x * size + 5, y * size + size / 2 + 10, Color::BLACK, "start", "alphabetic");
		}
	}
	
	
	
}

void generateDFTMatrices() {
	for (int i = 1; i <= MAX_MATRIX_SIZE; i++) {
		CFMatrix current = CFMatrix(i, i);
		for (int ts = 0; ts < i; ts++) {
			for (int fs = 0; fs < i; fs++) {
				current.set(ts, fs, Complex<float>::fromExp(1, 2.0f * M_PI / i * ts * fs));
			}
		}
		
		dftMatrices.push_back(current);
	}
	renderDFT();
}

void dftMInit() {
	dftCanvas = Canvas("dft_matrices", totalSize, totalSize);
	dftColored = static_cast<client::HTMLInputElement*>(client::document.getElementById("dft_colored"));
	dftRange = static_cast<client::HTMLInputElement*>(client::document.getElementById("dft_size"));
	dftRange->addEventListener("input", cheerp::Callback(renderDFT));
	dftColored->addEventListener("change", cheerp::Callback(renderDFT));
	generateDFTMatrices();
}

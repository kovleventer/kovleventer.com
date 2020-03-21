#pragma once

#include "html/canvas.hpp"
#include "html/input.hpp"
#include "color.hpp"

#include <cmath>
#include <iomanip>
#include <vector>
#include <complex>

namespace fft_padding {
#define FFT_PADDING_SIZE 7
using Complex = std::complex<double>;
Canvas foreground;
Canvas mtracking;
std::vector<int> values(FFT_PADDING_SIZE);
int w = 800;
int h = 400;

int zeroLevel = 300;

int activeIDX = -1;
int activeValue = 0;

const int POINTS_7 = 0;
const int POINTS_8_LEFT = 1;
const int POINTS_8_RIGHT = 2;
int state = POINTS_7;

void render() {
	mtracking.clear();
	mtracking.setLineWidth(8);
	if (activeIDX != -1) {
		int x = w / (FFT_PADDING_SIZE + 3) * (activeIDX + 2);
		mtracking.drawLine(x, zeroLevel, x, -activeValue+zeroLevel, Color::MAT_CYAN_300);
		mtracking.fillCircle(x, -activeValue+zeroLevel, 15, 0, 2 * M_PI, Color::MAT_CYAN_300);
	}
	
	mtracking.blitCanvas(foreground);
}

void mouseMove(client::MouseEvent* e) {
	int X = e->get_offsetX();
	int Y = e->get_offsetY();
	
	int blocksize = w / (FFT_PADDING_SIZE + 3);
	int offset = blocksize * 1.5;
	
	bool activeIDSet = false;
	for (int i = 0; i < FFT_PADDING_SIZE; i++) {
		
		if (X > blocksize * i + offset && X <= blocksize * (i+1) + offset) {
			activeIDX = i;
			activeValue = -Y+zeroLevel;
			activeIDSet = true;
			break;
		}
	}
	if (!activeIDSet) {
		activeIDX = -1;
	}
	
	render();
}

void renderForeground() {
	foreground.clear();
	foreground.setLineWidth(4);
	foreground.drawLine(0, zeroLevel, w, zeroLevel, Color::GRAY);
	
	std::vector<Complex> dft_coeffs;
	
	if (state == POINTS_8_LEFT) {
		for (int i = 0; i < FFT_PADDING_SIZE + 1; i++) {
			Complex coeff;
			for (int j = 0; j < FFT_PADDING_SIZE; j++) { 
				coeff += (double)values[j] * std::exp(-Complex(0, 1) * M_PI * 2. * (double)((double)i * (j+1) / (FFT_PADDING_SIZE+1)));
			}
			dft_coeffs.push_back(coeff);
		}
	} else if (state == POINTS_8_RIGHT) {;
		for (int i = 0; i < FFT_PADDING_SIZE + 1; i++) {
			Complex coeff;
			for (int j = 0; j < FFT_PADDING_SIZE; j++) { 
				coeff += (double)values[j] * std::exp(-Complex(0, 1) * M_PI * 2. * (double)((double)i * j / (FFT_PADDING_SIZE+1)));
			}
			dft_coeffs.push_back(coeff);
		}
	} else {
		for (int i = 0; i < FFT_PADDING_SIZE; i++) {
			Complex coeff;
			for (int j = 0; j < FFT_PADDING_SIZE; j++) { 
				coeff += (double)values[j] * std::exp(-Complex(0, 1) * M_PI * 2. * (double)((double)i * j / FFT_PADDING_SIZE));
			}
			dft_coeffs.push_back(coeff);
		}
	}
	
	for (int x = 0; x < w; x++) {
		double x_ = (double)x / w*10 - (state == POINTS_8_LEFT ? 1 : 2);
		double x_1 = (double)(x+2) / w*10 - (state == POINTS_8_LEFT ? 1 : 2);
		double y = 0, y_1 = 0;
		for (int i = 0; i < dft_coeffs.size(); i++) {
			y += dft_coeffs[i].real() * std::cos(2 * M_PI * i * x_ / dft_coeffs.size())
					- dft_coeffs[i].imag() * std::sin(2 * M_PI * i * x_ / dft_coeffs.size());
			y_1 += dft_coeffs[i].real() * std::cos(2 * M_PI * i * x_1 / dft_coeffs.size())
					- dft_coeffs[i].imag() * std::sin(2 * M_PI * i * x_1 / dft_coeffs.size());
		}
		
		foreground.drawLine(x, -(y / dft_coeffs.size())+zeroLevel, x+2, -(y_1 / dft_coeffs.size())+zeroLevel, Color::RED);
	}
	
	if (state == POINTS_8_LEFT) {
		foreground.fillCircle(w / (FFT_PADDING_SIZE + 3), zeroLevel, 10, 0, 2 * M_PI, Color::MAT_GREEN_700);
	}
	if (state == POINTS_8_RIGHT) {
		foreground.fillCircle(w - w / (FFT_PADDING_SIZE + 3), zeroLevel, 10, 0, 2 * M_PI, Color::MAT_GREEN_700);
	}
	
	for (int i = 0; i < FFT_PADDING_SIZE; i++) {
		int x = w / (FFT_PADDING_SIZE + 3) * (i + 2);
		foreground.drawLine(x, zeroLevel, x, -values[i]+zeroLevel, Color::MAT_CYAN_700);
		foreground.fillCircle(x, -values[i]+zeroLevel, 10, 0, 2 * M_PI, Color::MAT_CYAN_700);
	}
	
	
	
	render();
}

void onClick(client::MouseEvent* e) {
	int X = e->get_offsetX();
	int Y = e->get_offsetY();
	
	int blocksize = w / (FFT_PADDING_SIZE + 3);
	int offset = blocksize * 1.5;
	
	for (int i = 0; i < FFT_PADDING_SIZE; i++) {
		if (X > blocksize * i + offset && X <= blocksize * (i+1) + offset) {
			values[i] = -Y+zeroLevel;
			break;
		}
	}
	
	renderForeground();
}


void init() {
	mtracking = Canvas("fft_padding", w, h);
	foreground = Canvas::createEmptyCanvas(w, h);
	mtracking.addEventListener("mousemove", cheerp::Callback(mouseMove));
	mtracking.addEventListener("click", cheerp::Callback(onClick));
	values = {120, 270, -60, 40, 195, 144, -20};
	
	renderForeground();
}
}

extern "C" [[cheerp::jsexport]]
void add_left() {
	fft_padding::state = fft_padding::POINTS_8_LEFT;
	fft_padding::renderForeground();
}

extern "C" [[cheerp::jsexport]]
void add_right() {
	fft_padding::state = fft_padding::POINTS_8_RIGHT;
	fft_padding::renderForeground();
}

extern "C" [[cheerp::jsexport]]
void add_nothing() {
	fft_padding::state = fft_padding::POINTS_7;
	fft_padding::renderForeground();
}


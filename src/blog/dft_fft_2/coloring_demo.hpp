#pragma once

#include "html/canvas.hpp"
#include "html/input.hpp"
#include "math/matrix.hpp"
#include "math/complex.hpp"
#include "color.hpp"

#include <cmath>
#include <iomanip>

namespace coloring_demo {
Canvas canvas;
Canvas bgWheel;
double angle;
int w = 600;
int h = 400;

void render() {
	canvas.clear();
	canvas.blitCanvas(bgWheel);
	canvas.setLineWidth(6);
	canvas.drawLine(w/2, h/2, std::cos(angle) * h/2 + w/2, std::sin(angle) * h/2 + h/2, Color::BLACK);
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << Complex<float>::fromExp(1, angle).getArg();
	canvas.drawText(stream.str().c_str(), w/4*3+50, 50, Color::BLACK, "center", "middle", 40);
}

void mouseMove(client::MouseEvent* e) {
	int X = e->get_offsetX() - w/2;
	int Y = e->get_offsetY() - h/2;
	double newangle = std::atan2(Y, X);
	angle = newangle;
	render();
}


void init() {
	canvas = Canvas("coloring_demo", w, h);
	bgWheel = Canvas::createEmptyCanvas(w, h);
	canvas.addEventListener("mousemove", cheerp::Callback(mouseMove));
	
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int X = x-w/2;
			int Y = y-h/2;
			if (X*X+Y*Y < h*h/4) {
				bgWheel.fillRect(x, y, 1, 1, Color::angleToColor(Complex<float>(x-w/2, y-h/2).getArg()));
			}
		}
	}
	render();
}
}

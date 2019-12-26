#pragma once

#include <cmath>

namespace Color {
	const int BLACK = 0x000000;
	const int RED = 0xFF0000;
	const int GREEN = 0x00FF00;
	const int BLUE = 0x0000FF;
	const int CYAN = 0x00FFFF;
	const int MAGENTA = 0xFF00FF;
	const int YELLOW = 0xFFFF00;
	const int WHITE = 0xFFFFFF;
	
	int rgbToColor(int r, int g, int b) {
		return (r << 16) | (g << 8) | b;
	}
	
	int angleToColor(float angle) {
		int r = (angle / M_PI / 2 + 0.5) * 255;
		int g = (-angle / M_PI / 2 + 0.5) * 255;
		int b = 0;
		return rgbToColor(r, g, b);
	}
	
	
}

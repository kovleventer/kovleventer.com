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
	
	const int MAT_RED_50 = 0xffebee;
	const int MAT_CYAN_50 = 0xe0f7fa;
	const int MAT_GREEN_50 = 0xf1f8e9;
	
	const int MAT_RED_300 = 0xe57373;
	const int MAT_CYAN_300 = 0x4dd0e1;
	const int MAT_GREEN_300 = 0x81c784;
	
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

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
	
	const int GRAY = 0x808080;
	
	const int MAT_RED_50 = 0xffebee;
	const int MAT_CYAN_50 = 0xe0f7fa;
	const int MAT_GREEN_50 = 0xf1f8e9;
	const int MAT_PINK_50 = 0xfce4ec;
	const int MAT_LBLUE_50 = 0xe1f5fe;
	
	const int MAT_RED_300 = 0xe57373;
	const int MAT_CYAN_300 = 0x4dd0e1;
	const int MAT_GREEN_300 = 0x81c784;
	const int MAT_YELLOW_300 = 0xffee58;
	const int MAT_PINK_300 = 0xf06292;
	const int MAT_LBLUE_300 = 0x4fc3f7;
	
	const int MAT_RED_700 = 0xd32f2f;
	const int MAT_CYAN_700 = 0x0097a7;
	const int MAT_GREEN_700 = 0x388e3c;
	const int MAT_YELLOW_700 = 0xfbc02d;
	
	int rgbToColor(int r, int g, int b) {
		return (r << 16) | (g << 8) | b;
	}
	
	void HSVtoRGB(int H, double S, double V, int output[3]) {
		double C = S * V;
		double X = C * (1 - std::abs(std::fmod(H / 60.0, 2) - 1));
		double m = V - C;
		double Rs, Gs, Bs;

		if(H >= 0 && H < 60) {
			Rs = C;
			Gs = X;
			Bs = 0;	
		}
		else if(H >= 60 && H < 120) {	
			Rs = X;
			Gs = C;
			Bs = 0;	
		}
		else if(H >= 120 && H < 180) {
			Rs = 0;
			Gs = C;
			Bs = X;	
		}
		else if(H >= 180 && H < 240) {
			Rs = 0;
			Gs = X;
			Bs = C;	
		}
		else if(H >= 240 && H < 300) {
			Rs = X;
			Gs = 0;
			Bs = C;	
		}
		else {
			Rs = C;
			Gs = 0;
			Bs = X;	
		}

		output[0] = (Rs + m) * 255;
		output[1] = (Gs + m) * 255;
		output[2] = (Bs + m) * 255;
	}
	
	int angleToColor(float angle) {
		int H;
		double S, V = 1;
		if (angle >= 0 && angle < M_PI-.01) {
			H = (angle / M_PI) * 360;
			S = 0.75;
			V = 1;
		} else {
			H = (angle / M_PI + 1) * 360;
			S = 0.5;
			V = 1;
		}
		int rgb[3];
		HSVtoRGB(H, S, V, rgb);
		return rgbToColor(rgb[0], rgb[1], rgb[2]);
	}
	
	
}

#include <x86intrin.h>

int main() {
	float a1 = 1, b1 = 2, c1 = 3, d1 = 4;
	float a2 = 5, b2 = 6, c2 = 7, d2 = 8;
	
	__m128 abab = _mm_set_ps(b2, a2, b1, a1);
	__m128 cdcd = _mm_set_ps(d2, c2, d1, c1);
	
	// Selecting and duplicating c's
	__m128 cccc = _mm_moveldup_ps(cdcd);
	// Same for d's
	__m128 dddd = _mm_movehdup_ps(cdcd);
	
	cccc = _mm_mul_ps(abab, cccc);
	__m128 baba = _mm_shuffle_ps(abab, abab, 0xB1);
	dddd = _mm_mul_ps(baba, dddd);
	
	// add and sub in an alternating way
	__m128 res = _mm_addsub_ps(cccc, dddd);
}

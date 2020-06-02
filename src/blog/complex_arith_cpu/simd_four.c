#include <x86intrin.h>

int main() {
	__m128 a = _mm_set_ps(1, 2, 3, 4);
	__m128 b = _mm_set_ps(5, 6, 7, 8);
	__m128 c = _mm_set_ps(9, 10, 11, 12);
	__m128 d = _mm_set_ps(12, 14, 15, 16);
	
	__m128 m1 = _mm_mul_ps(a, c);
	__m128 m2 = _mm_mul_ps(b, d);
	__m128 m3 = _mm_mul_ps(a, d);
	__m128 m4 = _mm_mul_ps(b, c);
	
	__m128 res_real = _mm_sub_ps(m1, m2);
	__m128 res_imag = _mm_add_ps(m3, m4);
}

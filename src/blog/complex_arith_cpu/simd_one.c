#include <x86intrin.h>

int main() {
	float a = 1, b = 2, c = 3, d = 4;
	
	// Loading values into the 128 bit register
	// __mm_set_ps accepts the parameters in reverse order
	__m128 data = _mm_set_ps(d, c, b, a);
	
	// See https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_mm_shuffle_ps
	__m128 aabb = _mm_shuffle_ps(data, data, 0x50);
	__m128 cdcd = _mm_shuffle_ps(data, data, 0xEE);
	
	// Multiplication is done as a single operation
	__m128 mulres = _mm_mul_ps(aabb, cdcd);
	
	float result[4];
	// Retrieving the results
	_mm_storeu_ps(result, mulres);
	
	float re = result[0] - result[3];
	float im = result[1] + result[2];
}

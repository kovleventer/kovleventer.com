#include <iostream>
#include <x86intrin.h>

void escape(void *p) {
  __asm__ __volatile__ ("" : "+r" (p) :: "memory");
}

#define CNT 100000000
//#define CNT 10

__m128 asd;

void test1() {
	for (int i = 0; i < CNT; i++) {
		__m128 a_reals = _mm_set_ps(i, 2, 2*i, 4);
		__m128 a_imags = _mm_set_ps(5, i, 7, 2*i);
		__m128 b_reals = _mm_set_ps(2*i, 10, i, 12);
		__m128 b_imags = _mm_set_ps(2*i, 14, 15, i);
		
		__m128 m1 = _mm_mul_ps(a_reals, b_reals);
		__m128 m2 = _mm_mul_ps(a_imags, b_imags);
		__m128 m3 = _mm_mul_ps(a_reals, b_imags);
		__m128 m4 = _mm_mul_ps(a_imags, b_reals);
		
		__m128 res_real = _mm_sub_ps(m1, m2);
		__m128 res_imag = _mm_add_ps(m3, m4);
		
		escape(&res_real);
		escape(&res_imag);
		asd = res_imag;
	}
}

void test2() {
	for (int i = 0; i < CNT; i++) {
		__m128 a_reals = _mm_set_ps(i, 2, 2*i, 4);
		__m128 a_imags = _mm_set_ps(5, i, 7, 2*i);
		__m128 b_reals = _mm_set_ps(2*i, 10, i, 12);
		__m128 b_imags = _mm_set_ps(2*i, 14, 15, i);
		
		__m128 m2 = _mm_mul_ps(a_imags, b_imags);
		__m128 m4 = _mm_mul_ps(a_imags, b_reals);
		
		__m128 res_real = _mm_fmsub_ps(a_reals, b_reals, m2);
		__m128 res_imag = _mm_fmadd_ps(a_reals, b_imags, m4);
		
		escape(&res_real);
		escape(&res_imag);
	
	}
}

void test3() {
	for (int i = 0; i < CNT; i++) {
		__m128 a_reals = _mm_set_ps(i, 2, 2*i, 4);
		__m128 a_imags = _mm_set_ps(5, i, 7, 2*i);
		__m128 b_reals = _mm_set_ps(2*i, 10, i, 12);
		__m128 b_imags = _mm_set_ps(2*i, 14, 15, i);
		
		__m128 s1 = _mm_add_ps(a_reals, a_imags); // 14
		__m128 s2 = _mm_sub_ps(b_imags, b_reals);
		__m128 s3 = _mm_add_ps(b_reals, b_imags); // 27
		
		__m128 k1 = _mm_mul_ps(b_reals, s1); // 252
		__m128 k2 = _mm_mul_ps(a_reals, s2);
		__m128 k3 = _mm_mul_ps(a_imags, s3); // 135
		
		__m128 res_real = _mm_sub_ps(k1, k3);
		__m128 res_imag = _mm_add_ps(k1, k2);
		
		escape(&res_real);
		escape(&res_imag);
		//asd = res_imag;
	}
}

void test4_(int i) {
	__m128 a = _mm_set_ps(1, i, 2*i, 4);
	__m128 b = _mm_set_ps(i, 5, 7, 2*i);
	for (int j = 0; j < CNT; j++) {
		
		__m128 bi = _mm_moveldup_ps(b);
		__m128 br = _mm_movehdup_ps(b);
		
		bi = _mm_mul_ps(a, bi);
		a = _mm_shuffle_ps(a, a, 0xB1);
		br = _mm_mul_ps(a, br);
		
		
		__m128 res = _mm_addsub_ps(br, bi);
		
		escape(&res);
	}
}

void test4() {
	
	for (int i = 0; i < CNT *2; i++) {
		
		__m128 a = _mm_set_ps(1, i, 2*i, 4);
	__m128 b = _mm_set_ps(i, 5, 7, 2*i);
		
		__m128 bi = _mm_moveldup_ps(b);
		__m128 br = _mm_movehdup_ps(b);
		
		bi = _mm_mul_ps(a, bi);
		a = _mm_shuffle_ps(a, a, 0xB1);
		br = _mm_mul_ps(a, br);
		
		
		__m128 res = _mm_addsub_ps(br, bi);
		
		escape(&res);
	}
	
	/*float a1 = 1, b1 = 2, c1 = 3, d1 = 4;
	float a2 = 5, b2 = 6, c2 = 7, d2 = 8;
	
	__m128 abab = _mm_set_ps(b2, a2, b1, a1);
	__m128 cdcd = _mm_set_ps(d2, c2, d1, c1);
	
		
	__m128 cc = _mm_moveldup_ps(cdcd);
	__m128 dd = _mm_movehdup_ps(cdcd);
	
	
	
	cc = _mm_mul_ps(abab, cc);
	
	__m128 baba = _mm_shuffle_ps(abab, abab, 0xB1);
	
	dd = _mm_mul_ps(baba, dd);
	asd = cc;
	
	__m128 res = _mm_addsub_ps(cc, dd);
	asd = res;*/
}

void test6() {
	
	for (int i = 0; i < CNT * 4; i++) {
		
		__m128 data = _mm_set_ps(1, i, 3, 4); // 4 3 9 1
		
		//asd = data;
		
		__m128 aabb = _mm_shuffle_ps(data, data, 0x50);
		//asd = aabb;
		__m128 cdcd = _mm_shuffle_ps(data, data, 0xEE);
		//asd = cdcd;
		
		__m128 mulres = _mm_mul_ps(aabb, cdcd);
		
		float result[4];
		_mm_storeu_ps(result, mulres);
		
		float re = result[0] - result[3];
		float im = result[1] - result[2];
		
		escape(&re);
		escape(&im);
	}
}

void test1_(int i) {
	__m128 a_reals = _mm_set_ps(i, 2, 2*i, 4);
	__m128 a_imags = _mm_set_ps(5, i, 7, 2*i);
	__m128 b_reals = _mm_set_ps(2*i, 10, i, 12);
	__m128 b_imags = _mm_set_ps(2*i, 14, 15, i);
	for (int j = 0; j < CNT; j++) {
		
		
		__m128 m1 = _mm_mul_ps(a_reals, b_reals);
		__m128 m2 = _mm_mul_ps(a_imags, b_imags);
		__m128 m3 = _mm_mul_ps(a_reals, b_imags);
		__m128 m4 = _mm_mul_ps(a_imags, b_reals);
		
		__m128 res_real = _mm_sub_ps(m1, m2);
		__m128 res_imag = _mm_add_ps(m3, m4);
		
		escape(&res_real);
		escape(&res_imag);
	}
}

void test5_(int i) {
	__m256 a_reals = _mm256_set_ps(i, 2, 2*i, 4, 6, 3, i, 8);
	__m256 a_imags = _mm256_set_ps(5, i, 7, 2*i, 9, 7, 6, i);
	__m256 b_reals = _mm256_set_ps(2*i, 10, i, 12, 4, i, 5, 6);
	__m256 b_imags = _mm256_set_ps(2*i, 14, 15, i, i, 8, 8, 8);
	for (int j = 0; j < CNT; j++) {
		
		
		__m256 m1 = _mm256_mul_ps(a_reals, b_reals);
		__m256 m2 = _mm256_mul_ps(a_imags, b_imags);
		__m256 m3 = _mm256_mul_ps(a_reals, b_imags);
		__m256 m4 = _mm256_mul_ps(a_imags, b_reals);
		
		__m256 res_real = _mm256_sub_ps(m1, m2);
		__m256 res_imag = _mm256_add_ps(m3, m4);
		
		escape(&res_real);
		escape(&res_imag);
	}
}

void test5() {
	
	for (int i = 0; i < CNT / 2; i++) {
		__m256 a_reals = _mm256_set_ps(i, 2, 2*i, 4, 6, 3, i, 8);
	__m256 a_imags = _mm256_set_ps(5, i, 7, 2*i, 9, 7, 6, i);
	__m256 b_reals = _mm256_set_ps(2*i, 10, i, 12, 4, i, 5, 6);
	__m256 b_imags = _mm256_set_ps(2*i, 14, 15, i, i, 8, 8, 8);
		
		__m256 m1 = _mm256_mul_ps(a_reals, b_reals);
		__m256 m2 = _mm256_mul_ps(a_imags, b_imags);
		__m256 m3 = _mm256_mul_ps(a_reals, b_imags);
		__m256 m4 = _mm256_mul_ps(a_imags, b_reals);
		
		__m256 res_real = _mm256_sub_ps(m1, m2);
		__m256 res_imag = _mm256_add_ps(m3, m4);
		
		escape(&res_real);
		escape(&res_imag);
	}
}

int main() {
	int i;
	//std::cin >> i;
	
	test4();
	
	/*float* aaaa = (float*)&asd;
	
	for (int i = 0; i < 4; i++) {
		std::cout << aaaa[i] << " ";
	}
	std::cout << std::endl;*/
}

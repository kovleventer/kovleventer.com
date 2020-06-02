Complex c_mul_gauss(Complex c1, Complex c2) {
	float k1 = c2.real * (c1.real + c1.imag);
	float k2 = c1.real * (c2.imag - c2.real);
	float k3 = c1.imag * (c1.real + c2.imag);
	return { k1 - k3, k1 + k2 };
}

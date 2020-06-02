Complex c_div_fast(Complex c1, Complex c2) {
	float k1 = c1.real * (c2.real + c2.imag);
	float k2 = c2.real * (c1.real + c1.imag);
	float k3 = c2.imag * (c1.real - c1.imag);
	float dsqr = c2.real * c2.real + c2.imag * c2.imag;
	return { (k1 - k3) / dsqr,
			 (k2 - k1) / dsqr };
}

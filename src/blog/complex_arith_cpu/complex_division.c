Complex c_div(Complex c1, Complex c2) {
	float dsqr = c2.real * c2.real + c2.imag * c2.imag;
	return { (c1.real*c2.real + c1.imag*c2.imag) / dsqr,
			 (c1.imag*c2.real - c1.real*c2.imag) / dsqr };
}

Complex c_mul(Complex c1, Complex c2) {
	return { c1.real*c2.real - c1.imag*c2.imag,
			 c1.real*c2.imag + c2.real*c1.imag };
}

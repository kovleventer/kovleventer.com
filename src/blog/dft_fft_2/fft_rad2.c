void fft_req(double complex array[], int n) {
	if (n == 1) return;
	
	fft_req(array, n/2);
	fft_req(array + n/2, n/2); // n/2 offset
	
	for (int i = 0; i < n/2; i++) {
		double complex c1 = array[i];
		double complex c2 = array[i + n/2] * cexp(-I * PI * 2 * i / n);
		
		array[i] = c1 + c2;
		array[i + n/2] = c1 - c2;
	}
}

void fft(double complex array[], int n) { // n is the length of the array
	// Naive bit reversal permutation
	for(int i = 0; i < n; i++) {
		int rev_i = i; // i, but with its bits reversed
		
		int bits = 0; // log2(n)
		for (int n_ = n; n_ != 1; n_ >>= 1)
			bits++;
		int s = bits - 1;

		for(int v = i>>1; v != 0; v >>= 1) {
			rev_i <<= 1;
			rev_i |= v & 1;
			s--;
		}
		rev_i <<= s;
		rev_i &= n - 1;

		// Only swap when needed
		if(i < rev_i) {
			double complex temp = array[i];
			array[i] = array[rev_i];
			array[rev_i] = temp;
		}
	}
	
	fft_req(array, n);
}

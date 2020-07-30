public void b(int paramInt) {
	System.out.println("setMode !!!");
	if (paramInt == 1) {
		this.n[2] = (byte)1;
	} else if (paramInt == 2) {
		this.n[2] = (byte)2;
	} else if (paramInt == 3) {
		this.n[2] = (byte)3;
	}
	if (this.n[5] == 1)
		o(); 
}

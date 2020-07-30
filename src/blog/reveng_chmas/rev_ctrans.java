private void o() {
	if (this.m != null) {
		System.out.println("Send command + BackgroundControllActivity sendCommand()");
		this.m.controlTransfer(33, 9, 769, 256, this.n, this.n.length, 0);
		Log.d("Command Send", p());
		return;
	} 
	System.out.println("mUsbConnection null");
}

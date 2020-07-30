public void b() {
	if (this.c == null || this.d == null) {
		if (this.c == null)
			this.c = new Timer(); 
		if (this.d == null)
			this.d = new a(this); 
		this.c.schedule(this.d, 0L, 15000L);
		return;
	} 
	Log.d("MixModeController", "startTask : mTimer != null or mTimerTask != null ");
}

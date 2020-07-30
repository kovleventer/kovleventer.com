private String p() {
	String str = "";
	for (byte b1 = 0; b1 < this.n.length; b1++) {
		str = str + String.format("0x%02X", new Object[] { Byte.valueOf(this.n[b1]) }) + " ";
	} 
	return str;
}

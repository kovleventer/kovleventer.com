function isNumeric(num) {
	return !isNaN(num); // god damn it javascript
}

function b_compress() {
	const input = (<HTMLInputElement>document.getElementById("basic_compress_input")).value;
	let compressed : string = "";
	let currentChar : string = "";
	let currentRepCnt : number = 0;
	for (var i = 0; i < input.length; i++) {
		if (currentChar === input.charAt(i)) {
			currentRepCnt += 1;
		} else {
			if (currentRepCnt > 1) {
				compressed += currentChar + currentRepCnt.toString();
			} else if (currentRepCnt === 1) {
				compressed += currentChar;
			}
			currentChar = input.charAt(i);
			currentRepCnt = 1;
		}
	}
	if (currentRepCnt > 1) {
		compressed += currentChar + currentRepCnt.toString();
	} else if (currentRepCnt === 1) {
		compressed += currentChar;
	}
	
	const p_compressed = document.getElementById("basic_compress_compressed");
	p_compressed.innerText = compressed;
	
	// >using regex
	let decompressed : string = "";
	let lastChar = "";
	let lastCount = 0;
	for (var i = 0; i < compressed.length; i++) {
		if (isNumeric(compressed.charAt(i))) {
			lastCount = lastCount * 10 + parseInt(compressed.charAt(i));
		} else {
			if (lastCount > 1) {
				decompressed += lastChar.repeat(lastCount - 1);
			}
			decompressed += compressed.charAt(i);
			lastCount = 0;
			lastChar = compressed.charAt(i);
		}
	}
	if (lastCount > 1) {
		decompressed += lastChar.repeat(lastCount - 1);
	}
	
	const p_decompressed = document.getElementById("basic_compress_decompressed");
	p_decompressed.innerText = decompressed;
	
	if (decompressed === input) {
		document.getElementById("basic_compress_nomatch").style.display = "none";
	} else {
		document.getElementById("basic_compress_nomatch").style.display = "block";
	}
}

b_compress();

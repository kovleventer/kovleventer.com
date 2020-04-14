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


function repc_compress() {
	const input = (<HTMLInputElement>document.getElementById("repc_compress_input")).value;
	
	let compressed = [];
	let currentChar : string = "";
	let currentRepCnt : number = 0;
	for (var i = 0; i < input.length; i++) {
		if (currentChar === input.charAt(i) && currentRepCnt < 255) {
			currentRepCnt += 1;
		} else {
			if (currentRepCnt > 0) {
				compressed.push(currentChar);
				compressed.push(currentRepCnt);
			}
			currentChar = input.charAt(i);
			currentRepCnt = 1;
		}
	}
	if (currentRepCnt > 0) {
		compressed.push(currentChar);
		compressed.push(currentRepCnt);
	}
	
	let compressedStr : string = "";
	
	for (var i = 0; i < compressed.length / 2; i++) {
		compressedStr += compressed[i * 2];
		compressedStr += "<span class=\"plt_blue\">(" + compressed[i * 2 + 1].toString() + ")</span>";
	}
	
	const p_compressed = document.getElementById("repc_compress_compressed");
	p_compressed.innerHTML = compressedStr;
	
	let decompressed : string = "";
	for (var i = 0; i < compressed.length / 2; i++) {
		for (var j = 0; j < compressed[i * 2 + 1]; j++) {
			decompressed += compressed[i * 2];
		}
	}
	
	const p_decompressed = document.getElementById("repc_compress_decompressed");
	p_decompressed.innerText = decompressed;
	
	if (decompressed === input) {
		document.getElementById("repc_compress_nomatch").style.display = "none";
	} else {
		document.getElementById("repc_compress_nomatch").style.display = "block";
	}
}

repc_compress();


function mnp5_compress() {
	const input = (<HTMLInputElement>document.getElementById("mnp5_compress_input")).value;
	
	let compressed = [];
	let currentChar : string = "";
	let currentRepCnt : number = 0;
	
	for (var i = 0; i < input.length; i++) {
		if (currentChar === input.charAt(i) && currentRepCnt < 255) {
			currentRepCnt += 1;
		} else {
			if (currentRepCnt >= 3) {
				for (var j = 0; j < 3; j++) {
					compressed.push(currentChar);
				}
				compressed.push(currentRepCnt);
			} else {
				for (var j = 0; j < currentRepCnt; j++) {
					compressed.push(currentChar);
				}
			}
			currentChar = input.charAt(i);
			currentRepCnt = 1;
		}
	}
	if (currentRepCnt >= 3) {
		for (var j = 0; j < 3; j++) {
			compressed.push(currentChar);
		}
		compressed.push(currentRepCnt);
	} else {
		for (var j = 0; j < currentRepCnt; j++) {
			compressed.push(currentChar);
		}
	}
	
	let compressedStr : string = "";
	
	for (var i = 0; i < compressed.length; i++) {
		if (typeof compressed[i] === "string") {
			compressedStr += compressed[i];
		} else {
			compressedStr += "<span class=\"plt_blue\">(" + compressed[i].toString() + ")</span>";
		}
	}
	
	const p_compressed = document.getElementById("mnp5_compress_compressed");
	p_compressed.innerHTML = compressedStr;
	
	
	let decompressed : string = "";
	let lastChar = "";
	for (var i = 0; i < input.length; i++) {
		if (typeof compressed[i] === "string") {
			decompressed += compressed[i];
			lastChar = compressed[i];
		} else {
			for (var j = 0; j < compressed[i]-3; j++) {
				decompressed += lastChar;
			}
		}
	}
	const p_decompressed = document.getElementById("mnp5_compress_decompressed");
	p_decompressed.innerText = decompressed;
	
	if (decompressed === input) {
		document.getElementById("mnp5_compress_nomatch").style.display = "none";
	} else {
		document.getElementById("mnp5_compress_nomatch").style.display = "block";
	}
}

mnp5_compress();

let bin_grid = [
	[0, 1, 1, 1, 0, 0],
	[1, 0, 1, 0, 0, 0],
	[0, 0, 1, 1, 0, 1],
	[1, 1, 1, 0, 1, 1],
	[0, 0, 1, 1, 0, 1],
	[1, 0, 0, 1, 1, 1],
];

const canvas = <HTMLCanvasElement> document.getElementById("bin_rle"); 
const context = canvas.getContext("2d");

const padding = 10;
const size_tile = 50;
const size = 6;

canvas.width = padding * 2 + size_tile * size;
canvas.height = canvas.width;

function render_bingrid() {
	let compressed = [];
	let lastChar = 1;
	let count = 0;
	
	for (var y = 0; y < size; y++) {
		for (var x = 0; x < size; x++) {
			context.fillStyle = (bin_grid[y][x] == 0) ? "#007F9F" : "#FFFFFF";
			context.strokeStyle = "#007F9F";
			context.fillRect(padding + x * size_tile, padding + y * size_tile, size_tile, size_tile);
			context.strokeRect(padding + x * size_tile, padding + y * size_tile, size_tile, size_tile);
			
			
			if (bin_grid[y][x] == lastChar) {
				count++;
			} else {
				compressed.push(count);
				count = 1;
				lastChar = bin_grid[y][x];
			}
		}
	}
	compressed.push(count);
	
	let compressed_str = "";
	for (var i = 0; i < compressed.length; i++) {
		compressed_str += "(" + compressed[i].toString() + ") ";
	}
	const p_compressed = document.getElementById("bin_compressed");
	p_compressed.innerText = compressed_str;
}

canvas.addEventListener('click', function(e) { 
	let cRect = canvas.getBoundingClientRect();
	let x = Math.floor((e.clientX - cRect.left - padding) / size_tile);
	let y = Math.floor((e.clientY - cRect.top - padding) / size_tile);
	
	if (x >= 0 && x < size && y >= 0 && y < size) {
		bin_grid[y][x] = (bin_grid[y][x] == 0) ? 1 : 0;
		render_bingrid();
	}
	
}, false);

render_bingrid();

function packb_c() {
	(<HTMLImageElement>document.getElementById("packb")).src = "media/packb_compress.png"; 
}

function packb_noc() {
	(<HTMLImageElement>document.getElementById("packb")).src = "media/packb_nocompress.png"; 
}

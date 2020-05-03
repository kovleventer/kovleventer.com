const polar_canvas = <HTMLCanvasElement> document.getElementById("polar_complex"); 
const polar_context = polar_canvas.getContext("2d");

polar_canvas.width = 500;
polar_canvas.height = polar_canvas.width;

let r = 120;
let theta = -0.6;

function render_polar() {
	polar_context.clearRect(0, 0, polar_canvas.width, polar_canvas.height); 
	
	polar_context.beginPath();
	polar_context.fillStyle = "#FFEF90";
	polar_context.arc(250, 250, r, 0, theta, true);
	polar_context.lineTo(250, 250);
	polar_context.fill();
	
	polar_context.lineWidth = 7;
	polar_context.beginPath();
	polar_context.strokeStyle = "#BFAF10";
	polar_context.arc(250, 250, r, 0, theta, true);
	polar_context.stroke();
	
	polar_context.lineWidth = 5;
	polar_context.strokeStyle = "gray";
	polar_context.beginPath();
	polar_context.moveTo(0, 250);
	polar_context.lineTo(500, 250);
	polar_context.stroke();
	polar_context.beginPath();
	polar_context.moveTo(250, 0);
	polar_context.lineTo(250, 500);
	polar_context.stroke();
	
	polar_context.beginPath();
	polar_context.lineWidth = 7;
	polar_context.strokeStyle = "#10BFAF";
	polar_context.moveTo(250, 250);
	polar_context.lineTo((r+5)*Math.cos(theta)+250, (r+5)*Math.sin(theta)+250);
	polar_context.stroke();
	
	polar_context.font = "30px serif";
	polar_context.fillStyle = "#10BFAF";
	polar_context.fillText("r = " + r.toFixed(3), 20, 40);
	polar_context.fillStyle = "#BFAF10";
	polar_context.fillText("θ = " + (Math.atan2(Math.sin(theta), -Math.cos(theta))+3.1415926535).toFixed(3), 20, 70); 
}

polar_canvas.addEventListener('mousemove', function(e) { 
	let cRect = polar_canvas.getBoundingClientRect();
	let x = e.clientX - cRect.left;
	let y = e.clientY - cRect.top;
	
	r = Math.sqrt((x-250) * (x-250) + (y-250) * (y-250));
	theta = Math.atan2(y-250, x-250);
	
	render_polar();
	
}, false);

render_polar();

const neg_canvas = <HTMLCanvasElement> document.getElementById("negnum"); 
const neg_context = neg_canvas.getContext("2d");
const neg_display = <HTMLInputElement> document.getElementById("neg_display");
neg_canvas.width = 800;
neg_canvas.height = 50;

let neg_data: number[] = [
0, 1, 1, 0,
1, 0, 1, 0,
0, 0, 0, 0,
1, 1, 0, 1,
];

function render_neg() {
	neg_context.font = "30px serif";
	let n = 0;
	for (var i = 0; i < 16; i++) {
		neg_context.fillStyle = (neg_data[i] == 1) ? "#007F9F" : "#FFFFFF";
		neg_context.fillRect(i * 50, 0, 50, 50);
		neg_context.fillStyle = (neg_data[i] == 0) ? "#007F9F" : "#FFFFFF";
		neg_context.fillText(neg_data[i].toString(), i*50+18, 35);
		n += Math.pow(-2, 15-i) * neg_data[i];
	}
	neg_display.value = n.toString();
	
}

neg_canvas.addEventListener('click', function(e) { 
	let cRect = neg_canvas.getBoundingClientRect();
	let x = e.clientX - cRect.left;
	let y = e.clientY - cRect.top;
	
	neg_data[Math.floor(x/50)] = ((neg_data[Math.floor(x/50)] == 0) ? 1 : 0);
	
	render_neg();
	
}, false);

neg_display.addEventListener('input', function() {
	let n = parseInt(neg_display.value);
	for (var i = 15; i >= 0; i--) {
		neg_data[i] = Math.abs(n % -2);
		n = Math.floor(n / -2);
		if (neg_data[i] == 1) n++;
	}
	
	render_neg();
}, false);

render_neg();

const j2repr_canvas = <HTMLCanvasElement> document.getElementById("2jrepr"); 
const j2repr_context = j2repr_canvas.getContext("2d");
const j2r_display = <HTMLInputElement> document.getElementById("2jr_display");
const j2i_display = <HTMLInputElement> document.getElementById("2ji_display");
j2repr_canvas.width = 800;
j2repr_canvas.height = 50;

let j2repr_data: number[] = [
0, 0, 0, 0,
0, 0, 0, 0,
0, 3, 2, 0,
2, 1, 2, 1,
];

let fillColorR : string[] = ["#FFFFFF", "#FF9797", "#D70000", "#5A0000"];
let fontColorR : string[] = ["#5A0000", "#5A0000", "#FFFFFF", "#FFFFFF"];
let fillColorB : string[] = ["#FFFFFF", "#C2FAFF", "#25B4D6", "#007F9F"];
let fontColorB : string[] = ["#007F9F", "#007F9F", "#FFFFFF", "#FFFFFF"];

function render_2jrepr() {
	j2repr_context.font = "30px serif";
	let re = 0, im = 0;
	for (var i = 0; i < 16; i++) {
		j2repr_context.fillStyle = (i % 2 == 0) ? fillColorB[j2repr_data[i]] : fillColorR[j2repr_data[i]];
		j2repr_context.fillRect(i * 50, 0, 50, 50);
		j2repr_context.fillStyle = (i % 2 == 0) ? fontColorB[j2repr_data[i]] : fontColorR[j2repr_data[i]];
		j2repr_context.fillText(j2repr_data[i].toString(), i*50+18, 35);
		if (i % 2 == 0) re += Math.pow(-4, (14-i)/2) * j2repr_data[i];
		if (i % 2 == 1) im += Math.pow(-4, (13-i)/2)*2 * j2repr_data[i];
	}
	j2r_display.value = re.toString();
	j2i_display.value = im.toString();
	j2repr_context.fillStyle = "#000000";
	j2repr_context.fillRect(15*50-5, 0, 10, 50);
}

j2repr_canvas.addEventListener('click', function(e) { 
	let cRect = j2repr_canvas.getBoundingClientRect();
	let x = e.clientX - cRect.left;
	let y = e.clientY - cRect.top;
	
	let idx = Math.floor(x/50);
	
	j2repr_data[idx] = (j2repr_data[idx]+1) % 4;
	
	render_2jrepr();
	
}, false);

//TODO num2quaterim
/*neg_display.addEventListener('input', function() {
	let n = parseInt(neg_display.value);
	for (var i = 15; i >= 0; i--) {
		neg_data[i] = Math.abs(n % -2);
		n = Math.floor(n / -2);
		if (neg_data[i] == 1) n++;
	}
	
	render_2jrepr();
}, false);*/

render_2jrepr();

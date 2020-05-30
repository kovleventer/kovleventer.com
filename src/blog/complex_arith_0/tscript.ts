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

`timescale 1s/100ms
`include "../fadd.v"

module test();

reg a;
reg b;
reg c_in;

wire s;
wire c_out;

FullAdd fa(a, b, c_in, s, c_out);

initial
begin
	$monitor("a=%b, b=%b, c_in=%b, s=%b, c_out=%b", a, b, c_in, s, c_out);
	a = 0; b = 0; c_in=0; #10;
	a = 0; b = 0; c_in=1; #10;
	a = 0; b = 1; c_in=0; #10;
	a = 0; b = 1; c_in=1; #10;
	a = 1; b = 0; c_in=0; #10;
	a = 1; b = 0; c_in=1; #10;
	a = 1; b = 1; c_in=0; #10;
	a = 1; b = 1; c_in=1; #10;
	$finish;
end

endmodule

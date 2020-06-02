`timescale 1s/100ms
`include "../qimagfadd.v"

module test();

reg [1:0] a;
reg [1:0] b;
reg c_in_pos;
reg c_in_neg;

wire [1:0] s;
wire c_out_pos;
wire c_out_neg;

QImagFullAdd fa(a, b, c_in_neg, c_in_pos, s, c_out_neg, c_out_pos);

initial
begin
	$monitor("a=%d, b=%d, c_in_pos=%b, c_in_neg=%b, s=%d, c_out_pos=%b, c_out_neg=%b,", a, b, c_in_pos, c_in_neg, s, c_out_pos, c_out_neg);
	//$monitor("c_out=%b", c_out_neg);
	a = 0; b = 0; c_in_pos=0; c_in_neg=0; #10;
	a = 0; b = 0; c_in_pos=0; c_in_neg=1; #10;
	a = 0; b = 0; c_in_pos=1; c_in_neg=0; #10;
	a = 0; b = 1; c_in_pos=0; c_in_neg=0; #10;
	a = 0; b = 1; c_in_pos=0; c_in_neg=1; #10;
	a = 0; b = 1; c_in_pos=1; c_in_neg=0; #10;
	a = 0; b = 2; c_in_pos=0; c_in_neg=0; #10;
	a = 0; b = 2; c_in_pos=0; c_in_neg=1; #10;
	a = 0; b = 2; c_in_pos=1; c_in_neg=0; #10;
	a = 0; b = 3; c_in_pos=0; c_in_neg=0; #10;
	a = 0; b = 3; c_in_pos=0; c_in_neg=1; #10;
	a = 0; b = 3; c_in_pos=1; c_in_neg=0; #10;
	a = 1; b = 0; c_in_pos=0; c_in_neg=0; #10;
	a = 1; b = 0; c_in_pos=0; c_in_neg=1; #10;
	a = 1; b = 0; c_in_pos=1; c_in_neg=0; #10;
	a = 1; b = 1; c_in_pos=0; c_in_neg=0; #10;
	a = 1; b = 1; c_in_pos=0; c_in_neg=1; #10;
	a = 1; b = 1; c_in_pos=1; c_in_neg=0; #10;
	a = 1; b = 2; c_in_pos=0; c_in_neg=0; #10;
	a = 1; b = 2; c_in_pos=0; c_in_neg=1; #10;
	a = 1; b = 2; c_in_pos=1; c_in_neg=0; #10;
	a = 1; b = 3; c_in_pos=0; c_in_neg=0; #10;
	a = 1; b = 3; c_in_pos=0; c_in_neg=1; #10;
	a = 1; b = 3; c_in_pos=1; c_in_neg=0; #10;
	a = 2; b = 0; c_in_pos=0; c_in_neg=0; #10;
	a = 2; b = 0; c_in_pos=0; c_in_neg=1; #10;
	a = 2; b = 0; c_in_pos=1; c_in_neg=0; #10;
	a = 2; b = 1; c_in_pos=0; c_in_neg=0; #10;
	a = 2; b = 1; c_in_pos=0; c_in_neg=1; #10;
	a = 2; b = 1; c_in_pos=1; c_in_neg=0; #10;
	a = 2; b = 2; c_in_pos=0; c_in_neg=0; #10;
	a = 2; b = 2; c_in_pos=0; c_in_neg=1; #10;
	a = 2; b = 2; c_in_pos=1; c_in_neg=0; #10;
	a = 2; b = 3; c_in_pos=0; c_in_neg=0; #10;
	a = 2; b = 3; c_in_pos=0; c_in_neg=1; #10;
	a = 2; b = 3; c_in_pos=1; c_in_neg=0; #10;
	a = 3; b = 0; c_in_pos=0; c_in_neg=0; #10;
	a = 3; b = 0; c_in_pos=0; c_in_neg=1; #10;
	a = 3; b = 0; c_in_pos=1; c_in_neg=0; #10;
	a = 3; b = 1; c_in_pos=0; c_in_neg=0; #10;
	a = 3; b = 1; c_in_pos=0; c_in_neg=1; #10;
	a = 3; b = 1; c_in_pos=1; c_in_neg=0; #10;
	a = 3; b = 2; c_in_pos=0; c_in_neg=0; #10;
	a = 3; b = 2; c_in_pos=0; c_in_neg=1; #10;
	a = 3; b = 2; c_in_pos=1; c_in_neg=0; #10;
	a = 3; b = 3; c_in_pos=0; c_in_neg=0; #10;
	a = 3; b = 3; c_in_pos=0; c_in_neg=1; #10;
	a = 3; b = 3; c_in_pos=1; c_in_neg=0; #10;
	$finish;
end

endmodule

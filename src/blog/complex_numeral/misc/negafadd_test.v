`timescale 1s/100ms
`include "../negafadd.v"

module test();

reg a;
reg b;
reg c_in_pos;
reg c_in_neg;

wire s;
wire c_out_pos;
wire c_out_neg;

NegaFullAdd fa(a, b, c_in_neg, c_in_pos, s, c_out_neg, c_out_pos);

initial
begin
	$monitor("s=%b, c_out_pos=%b, c_out_neg=%b,", s, c_out_pos, c_out_neg);
	a = 0; b = 0; c_in_pos=0; c_in_neg=0; #10;
	a = 0; b = 0; c_in_pos=0; c_in_neg=1; #10;
	a = 0; b = 0; c_in_pos=1; c_in_neg=0; #10;
	a = 0; b = 1; c_in_pos=0; c_in_neg=0; #10;
	a = 0; b = 1; c_in_pos=0; c_in_neg=1; #10;
	a = 0; b = 1; c_in_pos=1; c_in_neg=0; #10;
	a = 1; b = 0; c_in_pos=0; c_in_neg=0; #10;
	a = 1; b = 0; c_in_pos=0; c_in_neg=1; #10;
	a = 1; b = 0; c_in_pos=1; c_in_neg=0; #10;
	a = 1; b = 1; c_in_pos=0; c_in_neg=0; #10;
	a = 1; b = 1; c_in_pos=0; c_in_neg=1; #10;
	a = 1; b = 1; c_in_pos=1; c_in_neg=0; #10;
	$finish;
end

endmodule


module FullAdd (
	input wire a,
	input wire b,
	input wire c_in,
	output wire s,
	output wire c_out
);

assign {c_out, s} = a + b + c_in;

endmodule


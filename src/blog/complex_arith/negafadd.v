module NegaFullAdd (
	input wire a,
	input wire b,
	input wire c_in_neg,
	input wire c_in_pos,
	output wire s,
	output wire c_out_neg,
	output wire c_out_pos
);

assign s = a + b + c_in_pos - c_in_neg;

// Only the negative carry bit is active
assign c_out_pos = ~a & ~b & ~c_in_pos & c_in_neg;

assign c_out_neg = (a + b + c_in_pos - c_in_neg > 1) & ~c_in_neg;

endmodule

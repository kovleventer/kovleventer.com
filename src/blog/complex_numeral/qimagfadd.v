module QImagFullAdd (
	input wire [1:0] a,
	input wire [1:0] b,
	input wire c_in_neg,
	input wire c_in_pos,
	output wire [1:0] s,
	output wire c_out_neg,
	output wire c_out_pos
);

assign s = a + b + c_in_pos - c_in_neg;

// Only the negative carry bit is active
assign c_out_pos = (a == 2'b00) & (b == 2'b00) & ~c_in_pos & c_in_neg;

assign c_out_neg = (a + b + c_in_pos - c_in_neg > 3) & ~c_out_pos;

endmodule

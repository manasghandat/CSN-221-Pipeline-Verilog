module mips_testbench ();

	reg clock;
	wire result;
	
	Pipeline test(clock);

	initial clock = 0;

	always #50 clock = ~clock;

endmodule
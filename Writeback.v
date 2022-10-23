module Writeback(
	output reg [31:0] read_data_1, read_data_2,
	input [31:0] write_data,
	input [4:0] read_reg_1, read_reg_2, write_reg, 
	input [5:0] opcode,
	input signal_regRead, signal_regWrite, signal_regDst, clk
);

	reg [31:0] registers [31:0];
	
	initial begin
		$readmemb("registers.mem", registers);
	end
	
	always @(write_data) begin
		// Write
		if(signal_regWrite) begin
			if(signal_regDst) begin
					registers[write_reg] = write_data;
			end
			else begin
					registers[read_reg_2] = write_data;
			end
			$writememb("registers.mem",registers);
		end
	end
	
	always @(read_reg_1, read_reg_2) begin
		// Read
		if(signal_regRead) begin
			read_data_1 = registers[read_reg_1];
			read_data_2 = registers[read_reg_2];
		end
	end
	
endmodule
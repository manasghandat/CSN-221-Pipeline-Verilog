
module ControlUnit(
	output reg RegRead,RegWrite,MemRead,MemWrite,RegDst,Branch,
	input [5:0] opcode, funct
);
	
	always @(opcode, funct) begin
	
		MemRead  = 1'b0;
		MemWrite = 1'b0;
		RegWrite = 1'b0;
		RegRead  = 1'b1;
		RegDst   = 1'b0;
		Branch   = 1'b0;
		
		if(opcode == 6'd0) begin
			RegDst = 1'b1;
			RegRead = 1'b1;
			RegWrite = 1'b1;
		end

		if(opcode != 6'd0 & opcode != 6'd3 & opcode != 6'd4 & opcode != 6'd2) begin
			RegWrite = 1'b1;
			RegDst   = 1'b0;
		end
		if(opcode == 6'd3 | opcode == 6'd4) begin
			Branch   = 1'b1;
		end

		if(opcode != 6'd0 & opcode == 6'd2 ) begin
			MemWrite = 1'b1;
			RegRead  = 1'b1;
		end

		if(opcode != 6'd0 & opcode == 6'd1)begin
			MemRead = 1'b1;
		end
	end
	
	
	
endmodule
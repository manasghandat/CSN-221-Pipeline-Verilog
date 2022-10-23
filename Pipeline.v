module Pipeline(clock);

	input clock;
	
	reg[31:0] PC = 32'b0;
	
	wire [31:0] instruction;
	
	wire [5:0] funct;
	wire [4:0] rs, rt, rd, shamt;
	wire [25:0] address;
	wire [15:0] immediate;
	wire [5:0] opcode;
	
	wire RegRead, RegWrite, RegDST;
	wire MemRead, MemWrite;
	wire BranchFlag;
	
	wire [31:0] DataWrite, rsValue, rtValue, MemData;
	
	FetchUnit IF (instruction, PC);

	Decode parse (opcode, rs, rt, rd, shamt, funct, immediate, address, instruction, PC);
	
	ControlUnit ControlSignals (RegRead, RegWrite,MemRead, MemWrite, RegDST, BranchFlag, opcode, funct);
								 
	ExecutionUnit ALU (DataWrite, BranchFlag, opcode, rsValue, rtValue, shamt, funct, immediate);
	
	Memory dataMemory (MemData, DataWrite, rtValue, opcode, MemRead, MemWrite);
	
	Writeback contents (rsValue, rtValue, DataWrite, rs, rt, rd, opcode, RegRead, RegWrite, RegDST, clock);
	
	always @(posedge clock) begin 
		if(opcode == 6'd6) begin
			PC = address;
		end
		else if(DataWrite == 0 & BranchFlag == 1) begin
			PC = PC + 1 + $signed(immediate); 
		end
		else begin
			PC = PC+1;
		end
	end 
	
endmodule
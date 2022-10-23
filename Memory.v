module Memory(
	output reg [31:0] ReadData,
	input  [31:0] address,DataWrite,
	input [5:0] opcode,
	input MemRead,MemWrite
);
	
	reg [31:0] MainMemory [255:0];
	integer i;
	initial begin
		for (i = 0; i< 256; i=i+1) begin
			MainMemory[i] = 32'b0;
		end
	end
	
	always @(address) begin
		if(MemWrite) begin
			MainMemory[address] = DataWrite;
		end
		if(MemRead) begin
			ReadData = MainMemory[address];
		end
	end

	
endmodule

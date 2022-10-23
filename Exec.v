
module ExecutionUnit(ALU_result, Branch, opcode, rsValue, rtValue, shamt, ALU_control, immediate);
	
	input [5:0] ALU_control, opcode;
	input [4:0] shamt;
	input [15:0] immediate;
	input [31:0] rsValue, rtValue;
	
	output reg Branch;
	output reg [31:0] ALU_result;
	
	reg [31:0] signExtend;

	always @ (ALU_control, rsValue, rtValue, shamt, immediate) begin
						
		if(opcode == 6'd0) begin
			case(ALU_control)
			
				6'd1 : 
					ALU_result = rsValue + rtValue;
				6'd2 : 
					ALU_result = rsValue - rtValue;
				6'd3 : 
					ALU_result = rsValue * rtValue;
				6'd4 : 
					ALU_result = rsValue & rtValue;
			endcase 
			
		end 
		
		else begin
			
			signExtend = {{16{immediate[15]}}, immediate};
			
			case(opcode)
		
				6'd1 :
					ALU_result = rsValue + signExtend;
				6'd2 :
					ALU_result = rsValue + signExtend;
				6'd8 : 
					ALU_result = rsValue + signExtend;
					
				6'd3 : 
					begin
						ALU_result = rsValue - rtValue;
						if(ALU_result == 0) begin
							Branch = 1'b1;
						end
						else begin
							Branch = 1'b0;
						end
					end
			endcase
		end
	end
endmodule
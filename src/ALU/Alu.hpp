#include <systemc.h>



SC_MODULE(Alu){
	 enum  OpC {zero_op = 0b0000,and_op = 0b0001,or_op = 0b0010,xor_op = 0b0011,not_op = 0b0100,slt_op = 0b0101,cmp_op = 0b0101,add_op = 0b0110,addi_op = 0b0111,sub_op = 0b1000,lw_op = 0b1001,sw_op = 0b1010,j_op = 0b1011,beq_op = 0b1100,bne_op = 0b1101};
    sc_out <bool> zero, notequal;
	sc_in <sc_uint<4>> opcode;
    sc_in <sc_int<32>> first_value,second_value;
    sc_out <sc_int<32>> output_value;

    sc_int<32> internDataA, internDataB, internResult;

    void aluOperation(){
        zero = false;
		notequal = false;
        internDataA = first_value.read();
        internDataB = second_value.read();
		
       		switch(opcode.read()){
				case and_op:
					internResult = internDataA & internDataB;
					output_value.write(internResult);
					break;
				case or_op:
					internResult = internDataA | internDataB;
					output_value.write(internResult);
					break;					
				case xor_op:
					internResult = internDataA ^ internDataB;
					output_value.write(internResult);
					break;
				case not_op:
					internResult = ~internDataA;
					output_value.write(internResult);
					break;
				case slt_op:
					internResult = internDataA - internDataB;
						if(internResult == 0){
							zero.write(true);
							notequal.write(false);
						}else{
							zero.write(false);
							if(internResult != 0){
								notequal = true;
							}else{
								notequal = false;
							}
						}
					output_value.write(internResult);
					break;
				case add_op:
				case addi_op:
					internResult = internDataA + internDataB;
					output_value.write(internResult);
					break;
				case sub_op:
					internResult = internDataA - internDataB;
					output_value.write(internResult);
					break;
				case beq_op:
				case bne_op:
					if(internDataA == internDataB){
						zero.write(true);
						notequal.write(false);
					}else{
						zero.write(false);
						notequal.write(true);
					}
					break;
			}
			
        
    }
		SC_CTOR(Alu){
			SC_METHOD(aluOperation);
				sensitive << opcode << first_value << second_value;
		}

};
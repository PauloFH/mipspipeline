#include <systemc.h>



SC_MODULE(alu){
    sc_in <sc_int<4>> opcode;
    sc_in <sc_int<32>> first_value,second_value;
    sc_out <sc_int<32>> output_value;
    sc_out <bool> zero, negative;
    sc_int<32> internDataA, internDataB, internResult;
    
    void aluOperation(){
        zero = false;
		negative = false;
        internDataA = first_value.read();
        internDataB = second_value.read();
		
       		switch(opcode.read()){
				case 1:
					internResult = internDataA & internDataB;
					output_value.write(internResult);
					break;
				case 2:
					internResult = internDataA | internDataB;
					output_value.write(internResult);
					break;					
				case 3:
					internResult = internDataA ^ internDataB;
					output_value.write(internResult);
					break;
				case 4:
					internResult = ~internDataA;
					output_value.write(internResult);
					break;
				case 5:
						if(internDataA == internDataB)
							zero = true;
						else
							zero = false;
						if (internDataA < internDataB)
							negative = true;
						else
							negative = false;
					break;
				case 6:
					internResult = internDataA + internDataB;
					output_value.write(internResult);
					break;
				case 7:
					internResult = internDataA - internDataB;
					output_value.write(internResult);
					break;
			}
			
        
    }
		SC_CTOR(alu){
			SC_METHOD(aluOperation);
				sensitive << opcode << first_value << second_value;
		}

};
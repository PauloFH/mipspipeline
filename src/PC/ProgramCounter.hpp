#include <systemc.h>

SC_MODULE(ProgramCounter) {
    sc_in<bool> clk; 
    sc_in<sc_uint<16>> pcInput;
    sc_in<bool> reset,  enable, load;
    sc_out<sc_uint<16>> pcOutput;
    sc_uint<16> currentInstruction;

    void counterIntruction() {
        if(reset.read()){
            currentInstruction = 0;
            pcOutput.write(currentInstruction);
        }else if(enable.read()){
            currentInstruction += 1;
            pcOutput.write(currentInstruction);
        }else if(load.read()){
            currentInstruction = pcInput.read();
            pcOutput.write(currentInstruction);
        }
    }
    
    SC_CTOR(ProgramCounter) {
       currentInstruction = 0; 
        SC_METHOD(counterIntruction);
        sensitive << clk.pos() << reset;
    }
};

#include <systemc.h>

SC_MODULE(ProgramCounter) {
    sc_in<bool> clock; 
    sc_in<int> pcInput;
    sc_in<bool> reset,  enable, load;
    sc_out<int> pcOutput;
    int currentInstruction;

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
        sensitive << clock.pos() << reset;
    }
};

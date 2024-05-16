#include <systemc.h>
#include <iostream>
using namespace std;
SC_MODULE(ProgramCounter) {
    sc_in<bool> clk; 
    sc_in<sc_uint<16>> pcInput;
    sc_in<bool> reset;
    sc_in<bool>enable;
    sc_in<bool>load;
    
    sc_out<sc_uint<16>> pcOutput;
    
    sc_uint<16> currentInstruction;

    void counterIntruction() {
        cout << "Program Counter" << endl;
        if(reset.read()){
            currentInstruction = 0;
            pcOutput.write(currentInstruction);
        }else
        if(load.read()){
            cout << "load" << endl;
            currentInstruction = pcInput.read();
            pcOutput.write(currentInstruction);

        } if(enable.read()){
            currentInstruction = pcInput.read();
            pcOutput.write(currentInstruction);
        }
    }
    
    SC_CTOR(ProgramCounter) {
       currentInstruction = 0; 
        SC_METHOD(counterIntruction);
        sensitive << clk.pos();
    }
};

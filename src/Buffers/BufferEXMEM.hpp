
#include <systemc.h>
SC_MODULE(BufferEXMEM) {
    sc_in<bool> clk;
    sc_in<sc_int<32>> ALU_result;


    SC_CTOR(BufferEXMEM) {
        
    }
};

#include <systemc.h>

SC_MODULE(BufferEXMEM) {
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_in<bool> zero;
    sc_in<bool> notequal;

    sc_in<sc_uint<6>> opdest;

    sc_in<sc_int<32>> ALU_result;
    
    sc_out<sc_uint<6>> opdestino;

    sc_uint<6> Intern_opdest;
    sc_uint<32> Intern_ALU_result;



    void bufferEXMEM() {
        if (reset.read() == true) {
            opdestino.write(0);
        } else {
            if (zero.read() == true && notequal.read() == false) {
                opdestino.write(0);
            } else {
                opdestino.write(opdest.read());
            }
        }
    }

    SC_CTOR(BufferEXMEM) {
        SC_METHOD(bufferEXMEM);
        sensitive << clk.pos();
        
    }
};
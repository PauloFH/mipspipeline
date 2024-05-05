#include <systemc.h>

SC_MODULE(Multiplexer) {
    sc_in<bool> aluSRC; 
    sc_in<sc_int<32>> in0; 
    sc_in<sc_int<32>> in1; 
    sc_out<sc_int<32>> out; 

    void process() {
        if (aluSRC.read() == 0) {
            out.write(in0.read()); 
        } else {
            out.write(in1.read());
        }
    }

    SC_CTOR(Multiplexer) {
        SC_METHOD(process);
        sensitive << aluSRC << in0 << in1;
    }
};

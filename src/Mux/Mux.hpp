#include <systemc.h>

SC_MODULE(Multiplexer) {
    sc_in<bool> pcSRC; 
    sc_in<sc_uint<9>> in0; 
    sc_in<sc_uint<9>> in1; 
    sc_out<sc_uint<9>> out; 

    void process() {
        if (pcSRC.read() == 0) {
            out.write(in0.read()); 
        } else {
            out.write(in1.read());
        }
    }

    SC_CTOR(Multiplexer) {
        SC_METHOD(process);
        sensitive << pcSRC << in0 << in1;
    }
};

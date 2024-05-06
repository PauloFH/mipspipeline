#include <systemc.h>

SC_MODULE(MuxDST) {
    sc_in<bool> RegDst; 
    sc_in<sc_int<32>> in0; 
    sc_in<sc_int<32>> in1; 
    sc_out<sc_int<32>> out; 

    void process() {
        if (RegDst.read() == 0) {
            out.write(in0.read()); 
        } else {
            out.write(in1.read());
        }
    }

    SC_CTOR(MuxDST) {
        SC_METHOD(process);
        sensitive << RegDst << in0 << in1;
    }
};

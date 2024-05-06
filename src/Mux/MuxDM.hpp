#include <systemc.h>

SC_MODULE(MuxDM) {
    sc_in<bool> memReg; 
    sc_in<sc_int<32>> in0; 
    sc_in<sc_int<32>> in1; 
    sc_out<sc_int<32>> out; 

    void process() {
        if (memReg.read() == 0) {
            out.write(in0.read()); 
        } else {
            out.write(in1.read());
        }
    }

    SC_CTOR(MuxDM) {
        SC_METHOD(process);
        sensitive << memReg << in0 << in1;
    }
};

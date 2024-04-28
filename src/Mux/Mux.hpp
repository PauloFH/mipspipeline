#include <systemc.h>

SC_MODULE(Multiplexer) {
    sc_in<bool> sel; 
    sc_in<int> in0; 
    sc_in<int> in1; 
    sc_out<int> out; 

    void process() {
        if (sel.read() == 0) {
            out.write(in0.read()); 
        } else {
            out.write(in1.read());
        }
    }

    SC_CTOR(Multiplexer) {
        SC_METHOD(process);
        sensitive << sel << in0 << in1;
    }
};

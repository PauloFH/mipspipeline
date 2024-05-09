#include <systemc.h>
#include "MuxDM.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> memReg;
    sc_signal<sc_int<32>> in0, in1, out;

    MuxDM mux("mux");
    mux.memReg(memReg);
    mux.in0(in0);
    mux.in1(in1);
    mux.out(out);

    memReg = false;
    in0 = 42;
    in1 = 24;

    sc_start(1, SC_NS);

    assert(out.read() == 42);

    memReg = true;

    sc_start(1, SC_NS);

    assert(out.read() == 24);

    cout << "Test passed!" << endl;

    return 0;
}
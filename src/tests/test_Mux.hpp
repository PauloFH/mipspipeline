#include <systemc.h>
#include "Mux.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> pcSRC;
    sc_signal<sc_uint<16>> in0, in1, out;

    Mux mux("mux");
    mux.pcSRC(pcSRC);
    mux.in0(in0);
    mux.in1(in1);
    mux.out(out);

    pcSRC = false;
    in0 = 0x1234;
    in1 = 0x5678;

    sc_start(1, SC_NS);

    assert(out.read() == 0x1234);

    pcSRC = true;

    sc_start(1, SC_NS);

    assert(out.read() == 0x5678);

    cout << "Test passed!" << endl;

    return 0;
}
#include <systemc.h>
#include <iostream>
#include "ProgramCounter.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<sc_uint<16>> pcInput;
    sc_signal<bool> reset, enable, load;
    sc_signal<sc_uint<16>> pcOutput;

    ProgramCounter pc("pc");
    pc.clk(clk);
    pc.pcInput(pcInput);
    pc.reset(reset);
    pc.enable(enable);
    pc.load(load);
    pc.pcOutput(pcOutput);

    // Test case 1: Reset
    reset = true;
    enable = false;
    load = false;
    pcInput = 0x1234;
    sc_start(1, SC_NS);
    assert(pcOutput.read() == 0);

    // Test case 2: Enable
    reset = false;
    enable = true;
    load = false;
    pcInput = 0x5678;
    sc_start(1, SC_NS);
    assert(pcOutput.read() == 0x5678);

    // Test case 3: Load
    reset = false;
    enable = false;
    load = true;
    pcInput = 0xABCD;
    sc_start(1, SC_NS);
    assert(pcOutput.read() == 0xABCD);

    cout << "All tests passed!" << endl;

    return 0;
}
#include <systemc.h>
#include "InstructionMemory.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> enable, write;
    sc_signal<sc_uint<16>> address;
    sc_signal<sc_uint<32>> instruction;

    InstructionMemory memory("memory");
    memory.clk(clk);
    memory.enable(enable);
    memory.write(write);
    memory.address(address);
    memory.instruction(instruction);

    enable = true;
    write = true;
    address = 0;
    instruction = 0x00000001; // Example instruction

    sc_start(1, SC_NS);

    assert(instruction.read() == 0x00000001);

    cout << "Test passed!" << endl;

    return 0;
}
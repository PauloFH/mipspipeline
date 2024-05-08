#include <systemc.h>
#include "BufferIFID.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> reset, enable, write;
    sc_signal<sc_uint<32>> instruction;
    sc_signal<sc_uint<16>> Address_Addr;
    sc_signal<sc_uint<16>> Address_Addr_Out;
    sc_signal<sc_uint<32>> instruction_out;
    sc_signal<sc_uint<6>> readRegister1;
    sc_signal<sc_uint<6>> readRegister2;
    sc_signal<sc_int<16>> immediate_out;
    sc_signal<sc_uint<4>> opcode_out;
    sc_signal<sc_uint<6>> DestReg_out;
    sc_signal<sc_uint<16>> label_j;

    BufferIFID buffer("buffer");
    buffer.clk(clk);
    buffer.reset(reset);
    buffer.enable(enable);
    buffer.write(write);
    buffer.instruction(instruction);
    buffer.Address_Addr(Address_Addr);
    buffer.Address_Addr_Out(Address_Addr_Out);
    buffer.instruction_out(instruction_out);
    buffer.readRegister1(readRegister1);
    buffer.readRegister2(readRegister2);
    buffer.immediate_out(immediate_out);
    buffer.opcode_out(opcode_out);
    buffer.DestReg_out(DestReg_out);
    buffer.label_j(label_j);

    reset = true;
    enable = false;
    write = false;
    instruction = 0;
    Address_Addr = 0;

    sc_start(1, SC_NS);

    reset = false;
    enable = true;
    write = true;
    instruction = 0x12345678;
    Address_Addr = 0x0000;

    sc_start(1, SC_NS);

    // Check output signals
    assert(Address_Addr_Out.read() == 0x0000);
    assert(instruction_out.read() == 0x12345678);
    assert(readRegister1.read() == 0x12);
    assert(readRegister2.read() == 0x5678);
    assert(immediate_out.read() == 0);
    assert(opcode_out.read() == 0b0001);
    assert(DestReg_out.read() == 0x12);
    assert(label_j.read() == 0);

    cout << "Test passed!" << endl;

    return 0;
}
#include <systemc.h>
#include "Registers.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> RegWrite, enable;
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_uint<6>> destReg, writeRegister, readRegister1, readRegister2;
    sc_signal<sc_int<32>> writeData, readData1, readData2, writeDataOut;
    sc_signal<sc_int<16>> immediate;

    Registers registers("registers");
    registers.clk(clk);
    registers.RegWrite(RegWrite);
    registers.enable(enable);
    registers.opcode(opcode);
    registers.destReg(destReg);
    registers.writeRegister(writeRegister);
    registers.readRegister1(readRegister1);
    registers.readRegister2(readRegister2);
    registers.writeData(writeData);
    registers.readData1(readData1);
    registers.readData2(readData2);
    registers.writeDataOut(writeDataOut);
    registers.immediate(immediate);

    enable = true;
    RegWrite = true;
    opcode = 0b0111;
    destReg = 0;
    writeRegister = 1;
    readRegister1 = 2;
    readRegister2 = 3;
    writeData = 0x12345678;
    immediate = 0x0001;

    sc_start(1, SC_NS);

    assert(readData1.read() == 0);
    assert(readData2.read() == 0x0001);

    opcode = 0b1001;
    readRegister1 = 4;
    immediate = 0x0002;

    sc_start(1, SC_NS);

    assert(readData1.read() == 4);
    assert(readData2.read() == 0x0002);

    opcode = 0b1010;
    readRegister1 = 5;
    destReg = 6;
    immediate = 0x0003;
    writeDataOut = 0x87654321;

    sc_start(1, SC_NS);

    assert(readData1.read() == 5);
    assert(readData2.read() == 0x0003);
    assert(writeDataOut.read() == 0x87654321);

    opcode = 0b1100;
    readRegister1 = 7;
    readRegister2 = 8;

    sc_start(1, SC_NS);

    assert(readData1.read() == 7);
    assert(readData2.read() == 8);

    cout << "All tests passed!" << endl;

    return 0;
}
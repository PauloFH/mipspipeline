#include <systemc.h>
#include "BufferMEMWB.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> RegWrite, memReg;
    sc_signal<sc_uint<6>> opDestino;
    sc_signal<sc_int<32>> dataAdress, readData;
    sc_signal<bool> regWriteOutput, memRegOut;
    sc_signal<sc_uint<6>> writeRegister;
    sc_signal<sc_int<32>> readDataOutput, dataAdressOutput;

    BufferMEMWB buffer("buffer");
    buffer.clk(clk);
    buffer.RegWrite(RegWrite);
    buffer.memReg(memReg);
    buffer.opDestino(opDestino);
    buffer.dataAdress(dataAdress);
    buffer.readData(readData);
    buffer.regWriteOutput(regWriteOutput);
    buffer.memRegOut(memRegOut);
    buffer.writeRegister(writeRegister);
    buffer.readDataOutput(readDataOutput);
    buffer.dataAdressOutput(dataAdressOutput);

    RegWrite = true;
    memReg = false;
    opDestino = 3;
    dataAdress = 100;
    readData = 50;

    sc_start(1, SC_NS);

    // Check output signals
    assert(regWriteOutput.read() == true);
    assert(memRegOut.read() == false);
    assert(writeRegister.read() == 3);
    assert(readDataOutput.read() == 50);
    assert(dataAdressOutput.read() == 100);

    cout << "Test passed!" << endl;

    return 0;
}
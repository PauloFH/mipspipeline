#include <systemc.h>
#include "BufferEXMEM.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> reset, enable, write, MemReg, regWrite, DMWrite, DMenable, Branch, zero, pcLoad;
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_uint<6>> opdest;
    sc_signal<sc_uint<16>> label_j;
    sc_signal<sc_int<32>> ALU_result, dataDM;
    sc_signal<sc_int<32>> ALU_result_Out, dataDMOut;
    sc_signal<sc_uint<16>> label_j_out;
    sc_signal<bool> DMWriteOUT, DMenableOUT, regWrite_Output, MemReg_Output, BranchOUT, pcLoadOut;
    sc_signal<sc_uint<6>> opdest_Out;

    BufferEXMEM buffer("buffer");
    buffer.clk(clk);
    buffer.reset(reset);
    buffer.enable(enable);
    buffer.write(write);
    buffer.MemReg(MemReg);
    buffer.regWrite(regWrite);
    buffer.opcode(opcode);
    buffer.DMWrite(DMWrite);
    buffer.DMenable(DMenable);
    buffer.Branch(Branch);
    buffer.opdest(opdest);
    buffer.zero(zero);
    buffer.pcLoad(pcLoad);
    buffer.ALU_result(ALU_result);
    buffer.dataDM(dataDM);
    buffer.ALU_result_Out(ALU_result_Out);
    buffer.label_j_out(label_j_out);
    buffer.DMWriteOUT(DMWriteOUT);
    buffer.DMenableOUT(DMenableOUT);
    buffer.regWrite_Output(regWrite_Output);
    buffer.MemReg_Output(MemReg_Output);
    buffer.BranchOUT(BranchOUT);
    buffer.pcLoadOut(pcLoadOut);
    buffer.opdest_Out(opdest_Out);
    buffer.dataDMOut(dataDMOut);

    reset = true;
    enable = false;
    write = false;
    MemReg = false;
    regWrite = false;
    opcode = 0;
    DMWrite = false;
    DMenable = false;
    Branch = false;
    opdest = 0;
    zero = false;
    pcLoad = false;
    ALU_result = 0;
    dataDM = 0;

    sc_start(1, SC_NS);

    reset = false;
    enable = true;
    write = true;
    MemReg = true;
    regWrite = true;
    opcode = 1;
    DMWrite = true;
    DMenable = true;
    Branch = true;
    opdest = 2;
    zero = true;
    pcLoad = true;
    ALU_result = 10;
    dataDM = 20;

    sc_start(1, SC_NS);

    // Check output signals
    assert(ALU_result_Out.read() == 10);
    assert(label_j_out.read() == 0);
    assert(DMWriteOUT.read() == true);
    assert(DMenableOUT.read() == true);
    assert(regWrite_Output.read() == true);
    assert(MemReg_Output.read() == true);
    assert(BranchOUT.read() == true);
    assert(pcLoadOut.read() == true);
    assert(opdest_Out.read() == 2);
    assert(dataDMOut.read() == 20);

    cout << "Test passed!" << endl;

    return 0;
}
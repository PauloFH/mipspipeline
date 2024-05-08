#include <systemc.h>
#include "BufferIDEX.hpp"

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS);
    sc_signal<bool> reset, enable, write, pcLoad, dmEnable, dmWrite, aluReset, Branch, memToReg;
    sc_signal<sc_uint<4>> opcode, aluOp;
    sc_signal<sc_uint<16>> pcJump, label_j;
    sc_signal<sc_uint<6>> destReg;
    sc_signal<sc_int<32>> registerData1, registerData2, dataDM;
    sc_signal<sc_int<32>> register1_Output, register2_Output, dataDMout;
    sc_signal<sc_uint<6>> destReg_Output;
    sc_signal<bool> regWrite_Output, Branch_Output, memToReg_Output;
    sc_signal<sc_uint<4>> opcode_Output, aluOp_out;
    sc_signal<sc_uint<16>> pc_out, label_j_out;
    sc_signal<bool> pcLoad_out, dmEnable_out, dmWrite_out, aluReset_out;

    BufferIDEX buffer("buffer");
    buffer.clk(clk);
    buffer.reset(reset);
    buffer.enable(enable);
    buffer.write(write);
    buffer.pcLoad(pcLoad);
    buffer.dmEnable(dmEnable);
    buffer.dmWrite(dmWrite);
    buffer.aluReset(aluReset);
    buffer.Branch(Branch);
    buffer.memToReg(memToReg);
    buffer.opcode(opcode);
    buffer.aluOp(aluOp);
    buffer.pcJump(pcJump);
    buffer.label_j(label_j);
    buffer.regWrite(regWrite_Output);
    buffer.registerData1(registerData1);
    buffer.registerData2(registerData2);
    buffer.destReg(destReg);
    buffer.dataDM(dataDM);
    buffer.register1_Output(register1_Output);
    buffer.register2_Output(register2_Output);
    buffer.dataDMout(dataDMout);
    buffer.destReg_Output(destReg_Output);
    buffer.opcode_Output(opcode_Output);
    buffer.pc_out(pc_out);
    buffer.label_j_out(label_j_out);
    buffer.pcLoad_out(pcLoad_out);
    buffer.dmEnable_out(dmEnable_out);
    buffer.dmWrite_out(dmWrite_out);
    buffer.aluReset_out(aluReset_out);
    buffer.aluOp_out(aluOp_out);
    buffer.Branch_Output(Branch_Output);
    buffer.memToReg_Output(memToReg_Output);

    reset = true;
    enable = false;
    write = false;
    pcLoad = false;
    dmEnable = false;
    dmWrite = false;
    aluReset = false;
    Branch = false;
    memToReg = false;
    opcode = 0;
    aluOp = 0;
    pcJump = 0;
    label_j = 0;
    registerData1 = 0;
    registerData2 = 0;
    destReg = 0;
    dataDM = 0;

    sc_start(1, SC_NS);

    reset = false;
    enable = true;
    write = true;
    pcLoad = true;
    dmEnable = true;
    dmWrite = true;
    aluReset = true;
    Branch = true;
    memToReg = true;
    opcode = 1;
    aluOp = 2;
    pcJump = 10;
    label_j = 20;
    registerData1 = 30;
    registerData2 = 40;
    destReg = 3;
    dataDM = 50;

    sc_start(1, SC_NS);

    // Check output signals
    assert(register1_Output.read() == 30);
    assert(register2_Output.read() == 40);
    assert(destReg_Output.read() == 3);
    assert(opcode_Output.read() == 1);
    assert(pc_out.read() == 10);
    assert(label_j_out.read() == 20);
    assert(Branch_Output.read() == true);
    assert(memToReg_Output.read() == true);
    assert(pcLoad_out.read() == true);
    assert(dmEnable_out.read() == true);
    assert(dmWrite_out.read() == true);
    assert(aluReset_out.read() == true);
    assert(aluOp_out.read() == 2);
    assert(dataDMout.read() == 50);

    cout << "Test passed!" << endl;

    return 0;
}
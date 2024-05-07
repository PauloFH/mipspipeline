#include <systemc.h>

SC_MODULE(BufferIDEX) {

    sc_in<bool>        clk;
    sc_in<bool>        enable;
    sc_in<bool>        write;
    // vem do Controller
    sc_in<bool>        pcLoad;
    sc_in <bool>       dmEnable;
    sc_in <bool>       dmWrite;
    sc_in<bool>        regWrite;
    sc_in<bool>        aluReset;
    sc_in<sc_uint<4>>  aluOp;
    sc_in<bool>        Branch;
    sc_in<bool>        memToReg;
     sc_in<sc_uint<4>>  opcode;
    sc_in<sc_uint<16>> pcJump;
    // vem do Registers
    sc_in<sc_int<32>>  registerData1;
    sc_in<sc_int<32>>  registerData2;
    // vem do MuxDST
    sc_in<sc_uint<6>>  destReg;
    sc_out<sc_int<32>> register1_Output;
    sc_out<sc_int<32>> register2_Output;
    
    sc_out<sc_uint<6>> destReg_Output;

    sc_out<sc_uint<4>> opcode_Output;
    sc_out<sc_uint<16>> pc_out;
    SC_CTOR(BufferIDEX) {
        SC_METHOD(update);
        sensitive << clk.pos();
    }

    void update() {
         if (enable.read()) {
            if (write.read()) {
                register1_Output.write(registerData1.read());
                register2_Output.write(registerData2.read());
                destReg_Output.write(destReg.read());
                opcode_Output.write(opcode.read());
                pc_out.write(pcJump.read());
            }
        }
    }
};

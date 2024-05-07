#include <systemc.h>

SC_MODULE(BufferIDEX) {

    sc_in<bool>        clk;
    sc_in<bool>        enable;
    sc_in<bool>        write;
    sc_in<bool>        reset;
    // vem do Controller
    sc_in<bool>        pcLoad;
    sc_in <bool>       dmEnable;
    sc_in <bool>       dmWrite;
    sc_in<bool>        aluReset;
    sc_in<sc_uint<4>>  aluOp;
    sc_in<bool>        Branch;
    sc_in<bool>        memToReg;
     sc_in<sc_uint<4>>  opcode;
    sc_in<sc_uint<16>> pcJump;
    sc_in<sc_uint<16>> label_j;

    // vem do Registers
    sc_in<sc_int<32>>  registerData1;
    sc_in<sc_int<32>>  registerData2;
    // vem do MuxDST
    sc_in<sc_uint<6>>  destReg;

    sc_out<sc_int<32>> register1_Output;
    sc_out<sc_int<32>> register2_Output;
    
    sc_out<sc_uint<6>> destReg_Output;

    sc_out<bool> Branch_Output;
    sc_out<bool> memToReg_Output;
    sc_out<sc_uint<4>> opcode_Output;
    sc_out<sc_uint<16>> pc_out;
    sc_out<sc_uint<16>> label_j_out;
    sc_out<bool> pcLoad_out;
    sc_out<bool> dmEnable_out;
    sc_out<bool> dmWrite_out;
    sc_out<bool> aluReset_out;
    sc_out<sc_uint<4>> aluOp_out;

    bool Intern_Branch;
    bool Intern_memToReg;
    sc_uint<4> Intern_opcode;
    sc_uint<16> Intern_pc;
    sc_uint<16> Intern_label_j;
    sc_uint<6> Intern_destReg;
    sc_int<32> Intern_register1;
    sc_int<32> Intern_register2;
    bool Intern_pcLoad;
    bool Intern_dmEnable;
    bool Intern_dmWrite;
    bool Intern_aluReset;
    sc_uint<4> Intern_aluOp;
    
    SC_CTOR(BufferIDEX) {
        SC_METHOD(update);
        sensitive << clk.pos();
    }

    void update() {
        if (reset.read()) {
                        Intern_dmWrite = 0;
            Intern_dmEnable = 0;
            Intern_pcLoad = 0;
            Intern_Branch = 0;
            Intern_memToReg = 0;
            Intern_aluReset = 0;
            Intern_aluOp = 0;
            Intern_register1 = 0;
            Intern_register2 = 0;
            Intern_destReg = 0;
            Intern_opcode = 0;
            Intern_pc = 0;
            Intern_label_j = 0;
            register1_Output.write(Intern_register1);
            register2_Output.write(Intern_register2);
            destReg_Output.write(Intern_destReg);
            opcode_Output.write(Intern_opcode);
            pc_out.write(Intern_pc);
            label_j_out.write(Intern_label_j);
            Branch_Output.write(Intern_Branch);
            memToReg_Output.write(Intern_memToReg);
            pcLoad_out.write(Intern_pcLoad);
            dmEnable_out.write(Intern_dmEnable);
            dmWrite_out.write(Intern_dmWrite);
            aluReset_out.write(Intern_aluReset);
            aluOp_out.write(Intern_aluOp);

        } else {
         if (enable.read()) {
            if (write.read()) {
                Intern_register1 = registerData1.read();
                Intern_register2 = registerData2.read();
                Intern_destReg = destReg.read();
                Intern_opcode = opcode.read();
                Intern_pc = pcJump.read();
                Intern_label_j = label_j.read();
                Intern_Branch = Branch.read();
                Intern_memToReg = memToReg.read();
                Intern_pcLoad = pcLoad.read();
                Intern_dmEnable = dmEnable.read();
                Intern_dmWrite = dmWrite.read();
                Intern_aluReset = aluReset.read();
                Intern_aluOp = aluOp.read();
            }  
            register1_Output.write(Intern_register1);
            register2_Output.write(Intern_register2);
            destReg_Output.write(Intern_destReg);
            opcode_Output.write(Intern_opcode);
            pc_out.write(Intern_pc);
            label_j_out.write(Intern_label_j);
            Branch_Output.write(Intern_Branch);
            memToReg_Output.write(Intern_memToReg);
            pcLoad_out.write(Intern_pcLoad);
            dmEnable_out.write(Intern_dmEnable);
            dmWrite_out.write(Intern_dmWrite);
            aluReset_out.write(Intern_aluReset);
            aluOp_out.write(Intern_aluOp);


            }else{
            register1_Output.write(Intern_register1);
            register2_Output.write(Intern_register2);
            destReg_Output.write(Intern_destReg);
            opcode_Output.write(Intern_opcode);
            pc_out.write(Intern_pc);
            label_j_out.write(Intern_label_j);
            Branch_Output.write(Intern_Branch);
            memToReg_Output.write(Intern_memToReg);
            pcLoad_out.write(Intern_pcLoad);
            dmEnable_out.write(Intern_dmEnable);
            dmWrite_out.write(Intern_dmWrite);
            aluReset_out.write(Intern_aluReset);
            aluOp_out.write(Intern_aluOp);
            }
        }
    }
};

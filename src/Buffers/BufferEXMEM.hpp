#include <systemc.h>

SC_MODULE(BufferEXMEM) {
        enum OpC
    {
        zero_op = 0b0000,
        and_op = 0b0001,
        or_op = 0b0010,
        xor_op = 0b0011,
        not_op = 0b0100,
        slt_op = 0b0101,
        cmp_op = 0b0101,
        add_op = 0b0110,
        addi_op = 0b0111,
        sub_op = 0b1000,
        lw_op = 0b1001,
        sw_op = 0b1010,
        j_op = 0b1011,
        beq_op = 0b1100,
        bne_op = 0b1101
    };

    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<bool> enable;
    sc_in<bool> write;
    sc_in<bool> MemReg;
    sc_in<bool>regWrite;
    sc_in<sc_uint<4>> opcode;
    sc_in<bool>DMWrite;
    sc_in<bool>DMenable;
    sc_in<bool>Branch;
    sc_in<sc_uint<6>> opdest;
    sc_in<bool> zero;
    sc_in<bool> pcLoad;
    sc_in<sc_int<32>> ALU_result;
    sc_in<sc_int<32>> dataDM;
    sc_in<sc_uint<16>> label_j;
    sc_out<sc_int<32>> ALU_result_Out;
    sc_out<sc_uint<16>> label_j_out;
    sc_out<bool>DMWriteOUT;
    sc_out<bool>DMenableOUT;
    sc_out<bool>regWrite_Output;
    sc_out<bool>MemReg_Output;
    sc_out<bool>BranchOUT;
    sc_out<bool> pcLoadOut;
    sc_out<sc_uint<6>> opdest_Out;
    sc_out<sc_int<32>> dataDMOut;
    sc_uint<6> Intern_opdest;
    sc_int<32> Intern_ALU_result;
    sc_uint<4> Intern_opcode;
    sc_uint<16> Intern_label_j;
    sc_int<32> Intern_dataDM;



    void bufferEXMEM() {
       
        if (reset.read() == true) {
            Intern_ALU_result = 0;
            Intern_label_j = 0;
            Intern_opdest = 0;
            Intern_opcode = 0;
            Intern_dataDM = 0;
            ALU_result_Out.write(Intern_ALU_result);
            label_j_out.write(Intern_label_j);
            opdest_Out.write(Intern_opdest);
            DMWriteOUT.write(0);
            DMenableOUT.write(0);
            regWrite_Output.write(0);
            MemReg_Output.write(0);
            BranchOUT.write(0);
            pcLoadOut.write(0);
            dataDMOut.write(Intern_dataDM);


        }else
         if (enable.read()) {
            Intern_opcode = opcode.read();
            if(Intern_opcode == j_op){
                BranchOUT.write(true);
                pcLoadOut.write(true);
            }else if(Intern_opcode == beq_op){
                if(zero.read()){
                    BranchOUT.write(true);
                    pcLoadOut.write(true);
            }else{
                BranchOUT.write(false);
            
            }}
            else if(Intern_opcode == bne_op){
                if(!zero.read()){
                    BranchOUT.write(true);
                    pcLoadOut.write(true);
                }else{
                    BranchOUT.write(false);
                }
            }else{
                 BranchOUT.write(false);
                pcLoadOut.write(false);
            }
            if(write.read()){
            Intern_dataDM = dataDM.read();
            Intern_ALU_result = ALU_result.read();
            Intern_label_j = label_j.read();
            Intern_opdest = opdest.read();
            ALU_result_Out.write(Intern_ALU_result);
            label_j_out.write(Intern_label_j);
            opdest_Out.write(Intern_opdest);
            DMWriteOUT.write(DMWrite.read());
            DMenableOUT.write(DMenable.read());
            regWrite_Output.write(regWrite.read());
            MemReg_Output.write(MemReg.read());
            }else{
            ALU_result_Out.write(Intern_ALU_result);
            label_j_out.write(Intern_label_j);
            opdest_Out.write(Intern_opdest);
            DMWriteOUT.write(DMWrite.read());
            DMenableOUT.write(DMenable.read());
            regWrite_Output.write(regWrite.read());
            MemReg_Output.write(MemReg.read());
            dataDMOut.write(Intern_dataDM);
            }
            }
        }
    SC_CTOR(BufferEXMEM) {
        SC_METHOD(bufferEXMEM);
        sensitive << clk.pos();
        
    }
};
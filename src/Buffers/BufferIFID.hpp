#include <systemc.h>

SC_MODULE(BufferIFID) {
    // Entradas
    sc_in<bool>         clk;
    sc_in<bool>         enable;
    sc_in<bool>         write;
    sc_in<bool>         reset;
    sc_in<sc_uint<32>>  instruction;
    sc_out<sc_uint<32>> instruction_out;
    sc_out<sc_uint<6>>  readRegister1;
    sc_out<sc_uint<6>>  readRegister2;
    sc_out<sc_int<16>>  immediate_out;
    sc_out<sc_uint<4>>  opcode_out;
    sc_out<sc_uint<6>>  DestReg_out;
    sc_out<sc_uint<16>> label_j;

    sc_uint<6>          Intern_DestReg_out;
    sc_uint<16>         Intern_label_j;
    sc_uint<32>         Intern_instruction;
    sc_uint<6>          Intern_readRegister1;
    sc_uint<6>          Intern_readRegister2;
    sc_uint<4>          Intern_opcode;
    sc_int<16>          Intern_immediate;
    enum  OpC {zero_op = 0b0000,and_op = 0b0001,or_op = 0b0010,xor_op = 0b0011,not_op = 0b0100,slt_op = 0b0101,cmp_op = 0b0101,add_op = 0b0110,addi_op = 0b0111,sub_op = 0b1000,lw_op = 0b1001,sw_op = 0b1010,j_op = 0b1011,beq_op = 0b1100,bne_op = 0b1101};
    void bufferProcess() {
        if(reset.read()){
            instruction_out.write(0);
            readRegister1.write(0);
            readRegister2.write(0);
            immediate_out.write(0);
            opcode_out.write(0);
            DestReg_out.write(0);
            label_j.write(0);
        }
        
        if(enable.read()){
            if(write.read()){
            Intern_instruction = instruction.read();
            Intern_opcode = Intern_instruction.range(31, 28);
    
            //beq/bne
            if(Intern_opcode == beq_op || Intern_opcode == bne_op){
                Intern_readRegister1 =  Intern_instruction.range(27, 22);
                Intern_readRegister2 =  Intern_instruction.range(21, 16);
                Intern_label_j = Intern_instruction.range(15, 0);
                Intern_DestReg_out = 0b000000;
                Intern_immediate = 0; 

            }else
             if(Intern_opcode == j_op){
                Intern_label_j = Intern_instruction.range(15, 0);
            }else

            if(Intern_opcode == addi_op|| Intern_opcode == lw_op || Intern_opcode == sw_op){
                Intern_readRegister2 =  0b000000;
                Intern_DestReg_out =  Intern_instruction.range(27, 22);
                Intern_readRegister1 =  Intern_instruction.range(21, 16);
                Intern_immediate = Intern_instruction.range(15, 0);
                
            }else{
                Intern_DestReg_out =  Intern_instruction.range(27, 22);
                Intern_readRegister1 =  Intern_instruction.range(21, 16);
                Intern_readRegister2 =  Intern_instruction.range(15, 0);
                Intern_immediate = 0;
            }
            }
            instruction_out.write(Intern_instruction);
            readRegister1.write(Intern_readRegister1);
            opcode_out.write(Intern_opcode);
            immediate_out.write(Intern_immediate);
            readRegister2.write(Intern_readRegister2);
            Intern_readRegister2 = Intern_instruction.range(20, 16);
            readRegister2.write(Intern_readRegister2);
            DestReg_out.write(Intern_DestReg_out);
            label_j.write(Intern_label_j);
        }
    }

     SC_CTOR(BufferIFID) {
        SC_METHOD(bufferProcess);
        sensitive << clk.pos();
    }
};
#include <systemc.h>

SC_MODULE(BufferIFID) {
    // Entradas
    sc_in<bool>         clk;
    sc_in<bool>         enable;
    sc_in<bool>         write;
    sc_in<sc_uint<32>>  instruction;
    sc_in<sc_uint<9>>   Address_Addr;

    sc_out<sc_uint<9>> Address_Addr_Out;

    sc_out<sc_uint<32>> instruction_out;
    sc_out<sc_uint<6>>  readRegister1;
    sc_out<sc_uint<6>>  readRegister2;
    sc_out<sc_int<16>>  immediate_out;
    sc_out<sc_uint<4>>  opcode_out;
    sc_out<sc_uint<6>>  DestReg_out;
    
    sc_uint<9>          Intern_Address_Addr;
    sc_uint<32>         Intern_instruction;
    sc_uint<6>          Intern_readRegister1;
    sc_uint<6>          Intern_readRegister2;
    sc_uint<4>          Intern_opcode;
    sc_int<16>          Intern_immediate;
   
   SC_HAS_PROCESS(BufferIFID);
    void bufferProcess() {
        if(enable.read()){
            if(write.read()){
            Intern_Address_Addr = Address_Addr.read();
            Intern_instruction = instruction.read();
            Intern_readRegister1 =  Intern_instruction.range(27, 21);
            Intern_opcode = Intern_instruction.range(31, 28);
            if(Intern_opcode == 0b0111){
                Intern_readRegister2 =  0b000000;
                
                Intern_immediate = Intern_instruction.range(15, 0);
            }else{
                Intern_readRegister2 =  Intern_instruction.range(20, 16);
                Intern_immediate = 0;
            }
            }
            instruction_out.write(Intern_instruction);
            Address_Addr_Out.write(Intern_Address_Addr);
            readRegister1.write(Intern_readRegister1);
            opcode_out.write(Intern_opcode);
            immediate_out.write(Intern_immediate);
            readRegister2.write(Intern_readRegister2);
            Intern_readRegister2 = Intern_instruction.range(20, 16);
            readRegister2.write(Intern_readRegister2);
        }
    }

     SC_CTOR(BufferIFID) {
        SC_METHOD(bufferProcess);
        sensitive << clk.pos();
    }
};
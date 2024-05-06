#include <systemc.h>

SC_MODULE(BufferIFID) {
    // Entradas
    sc_in<bool>         clk;
    sc_in<bool>         reset;

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
   
    void bufferProcess() {
        if (reset.read()) {
            instruction_out.write(0);
        } else {
            Intern_Address_Addr = Address_Addr.read();
            Intern_instruction = instruction.read();
            instruction_out.write(Intern_instruction);
            Address_Addr_Out.write(Intern_Address_Addr);
            Intern_readRegister1 =  Intern_instruction.range(27, 21);
            readRegister1.write(Intern_readRegister1);
            Intern_opcode = Intern_instruction.range(31, 28);
            opcode_out.write(Intern_opcode);
            if(Intern_opcode == 0b0111){
                Intern_readRegister2 =  0b000000;
                readRegister2.write(Intern_readRegister2);
                Intern_immediate = Intern_instruction.range(15, 0);
                immediate_out.write(Intern_immediate);
            }else{
            Intern_readRegister2 =  Intern_instruction.range(20, 16);
            readRegister2.write(Intern_readRegister2);
            }
        }
    }

     SC_CTOR(BufferIFID) {
        SC_METHOD(bufferProcess);
        sensitive << clk.pos();
        async_reset_signal_is(reset, true);
    }
};
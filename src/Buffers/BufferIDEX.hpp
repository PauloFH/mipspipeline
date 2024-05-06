#include <systemc.h>

SC_MODULE(BufferIDEX) {

    sc_in<bool> clk;
    sc_in<bool> reset;
    
    // vem do Controller
    sc_in<sc_uint<4>> opcode;

    
    // vem do Registers
    sc_in<sc_int<32>> registerData1;
    sc_in<sc_int<32>> registerData2;

    // vem do AddA
    sc_in<sc_uint<32>> addr_input;

    // vem do MuxDST
    sc_in<sc_uint<6>> destReg;

   

    sc_out<sc_int<32>> register1_Output;
    sc_out<sc_int<32>> register2_Output;
    sc_out<sc_uint<6>> destReg_Output;
    sc_out<sc_uint<4>> opcode_Output;
    sc_out<sc_uint<32>> pc_out;

    SC_CTOR(BufferIDEX) {
        SC_METHOD(update);
        sensitive << clk.pos();
        async_reset_signal_is(reset, true);
    }

    void update() {
      
    }
};

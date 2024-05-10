#include <systemc.h>
#include <Controller.hpp> // Inclua o arquivo do design do módulo Controller

int sc_main(int argc, char* argv[]) {

   	    sc_clock clk("clk", 1, SC_NS);
	    sc_signal<sc_uint<32>> instruction;
  		sc_signal<int> state;
        sc_signal<bool> s_zero;
        sc_signal<bool> s_reset;
        sc_signal<bool> s_pcReset;
        sc_signal<bool> s_pcEnable;
        sc_signal<bool> s_PcLoad;
        sc_signal<sc_uint<16>> s_pcjump;

        sc_signal<bool> s_regEnable;
        sc_signal<bool> s_regWrite;

        sc_signal<bool> s_imEnable;
        sc_signal<bool> s_imwrite;

    sc_signal<bool> s_dmEnable;
    sc_signal<bool> s_dmWrite;
  	sc_signal<bool> s_memToReg;
    sc_signal<bool> s_enable_BufferIFID;
    sc_signal<bool> s_write_BufferIFID;
    sc_signal<bool> s_reset_BufferIFID;
    sc_signal<bool> s_enable_BufferIDEX;
    sc_signal<bool> s_write_BufferIDEX;
    sc_signal<bool> s_reset_BufferIDEX;
    sc_signal<bool> s_branch;
    sc_signal<bool> s_enable_BufferEXMEM;
    sc_signal<bool> s_write_BufferEXMEM;
    sc_signal<bool> s_reset_BufferEXMEM;
    sc_signal<bool> s_enable_BufferMEMWB;
    sc_signal<bool> s_reset_BufferMEMWB;
    sc_signal<bool> s_write_BufferMEMWB;
    sc_signal<sc_uint<4>> s_aluOp;
    sc_signal<bool> s_aluReset;
    sc_signal<sc_uint<22>> s_addressOut;
  
    Controller controller_instance("controller");

    controller_instance.clk(clk);
    controller_instance.instruction(instruction);
    controller_instance.zero(s_zero);
    controller_instance.reset(s_reset);
    controller_instance.pcReset(s_pcReset);
    controller_instance.pcEnable(s_pcEnable);
    controller_instance.PcLoad(s_PcLoad);
    controller_instance.pcjump(s_pcjump);
    controller_instance.regEnable(s_regEnable);
    controller_instance.regWrite(s_regWrite);
    controller_instance.imEnable(s_imEnable);
    controller_instance.imwrite(s_imwrite);
    controller_instance.dmEnable(s_dmEnable);
    controller_instance.dmWrite(s_dmWrite);
    controller_instance.memToReg(s_memToReg);
    controller_instance.enable_BufferIFID(s_enable_BufferIFID);
    controller_instance.write_BufferIFID(s_write_BufferIFID);
    controller_instance.reset_BufferIFID(s_reset_BufferIFID);
    controller_instance.enable_BufferIDEX(s_enable_BufferIDEX);
    controller_instance.write_BufferIDEX(s_write_BufferIDEX);
    controller_instance.reset_BufferIDEX(s_reset_BufferIDEX);
    controller_instance.branch(s_branch);
    controller_instance.enable_BufferEXMEM(s_enable_BufferEXMEM);
    controller_instance.write_BufferEXMEM(s_write_BufferEXMEM);
    controller_instance.reset_BufferEXMEM(s_reset_BufferEXMEM);
    controller_instance.enable_BufferMEMWB(s_enable_BufferMEMWB);
    controller_instance.write_BufferMEMWB(s_write_BufferMEMWB);
   controller_instance.reset_BufferMEMWB(s_reset_BufferMEMWB);
    controller_instance.aluOp(s_aluOp);
    controller_instance.aluReset(s_aluReset);
    controller_instance.addressOut(s_addressOut);
	controller_instance.stateOut(state);
  

  			instruction  = 0b10010011000100010000000000000000;
  
    for (int i = 0; i < 10; ++i) {
        s_zero = false;
        s_reset = true;
        controller_instance.updateState();
        std::cout << "Pipeline State: " << state << std::endl;
        sc_start(1, SC_NS);
    }

    return 0;
}

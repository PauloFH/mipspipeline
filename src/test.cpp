
#include <systemc.h>
#include<InstructionMemory.hpp>
#include<ProgramCounter.hpp>
#include<Registers.hpp>
#include<Alu.hpp>
#include<DataMemory.hpp>
#include<Addr.hpp>
#include<Controller.hpp>
#include<Mux.hpp>
#include<MuxDM.hpp>
#include<BufferIFID.hpp>
#include<BufferIDEX.hpp>
#include<BufferEXMEM.hpp>
#include<BufferMEMWB.hpp>

int sc_main(int arg, char* argv[]) {

	ProgramCounter PC("PC");

/*
	InstructionMemory IM("IM");
	Registers RegistersData("RegistersData");

	Alu ALU("ALU");

	DataMemory DM("DM");

	Addr Addr("Addr");

	Mux Mux("Mux");

	MuxDM MuxDM("MuxDM");

	BufferIFID BufferIFID("BufferIFID");

	BufferIDEX BufferIDEX("BufferIDEX");

	BufferEXMEM BufferEXMEM("BufferEXMEM");

	BufferMEMWB BufferMEMWB("BufferMEMWB");
*/
//-----------------------------------------------------------------------------------------------
	sc_signal<bool> clk;
	sc_signal<bool> Controller_reset;
	sc_signal<bool> Controller_PC_enable;
	sc_signal<bool> Controller_PC_load;
	sc_signal<sc_uint<16>> Mux_PC_loadAddrs;
	sc_signal<sc_uint<16>> PC_IM_pcOutput;
	int i  - 0;

//-----------------------------------------------------------------------------------------------

	PC.clk(clk);
	PC.reset(Controller_reset);
	PC.enable(Controller_PC_enable);
	PC.load(Controller_PC_load);
	PC.pcInput(Mux_PC_loadAddrs);
	PC.pcOutput(PC_IM_pcOutput);

	Controller_reset = false;
	Controller_PC_enable = false;
	Controller_PC_load = false;
	Mux_PC_loadAddrs = 0;
	Controller_PC_enable = true;
	for (int i = 0; i < 10; i++)
	{
		clk = 0;
		sc_start(1, SC_NS);
		clk = 1;
		sc_start(1, SC_NS);
		clk = 0;
	}
	
	

	return 0;
}

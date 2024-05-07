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

//-----------------------------------------------------------------------------------------------


	


	sc_start(1, SC_NS);
	return 0;
}

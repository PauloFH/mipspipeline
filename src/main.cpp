
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

	Addr Addr("Addr");

	Mux Mux("Mux");

	BufferIFID BufferIFID("BufferIFID");
/*
	
	Registers RegistersData("RegistersData");

	Alu ALU("ALU");

	DataMemory DM("DM");

	

	

	MuxDM MuxDM("MuxDM");

	

	BufferIDEX BufferIDEX("BufferIDEX");

	BufferEXMEM BufferEXMEM("BufferEXMEM");

	BufferMEMWB BufferMEMWB("BufferMEMWB");
*/
//-----------------------------------------------------------------------------------------------
	sc_signal<bool> clk;
	sc_signal<bool> reset;
	//pc signals
	sc_signal<bool> Controller_PC_reset; //controller
	sc_signal<bool> Controller_PC_enable; // controller
	sc_signal<sc_uint<16>> Mux_PC_loadAddrs;	// Mux
	sc_signal<sc_uint<16>> PC_IM_pcOutput;// IM
	sc_signal<sc_uint<16>> PC_Addr_pcOutput; // Addr

	//IM signals
	sc_signal<bool> Controller_IM_enable; // controller
	sc_signal<bool> Controller_IM_Write;
	sc_signal<sc_uint<32>> IM_BufferIDEX_instruction; // BufferIDEX

	//Addr signals
	sc_signal<sc_uint<16>> Addr_MUX_op0; // Mux
	sc_signal<sc_uint<16>> Addr_BufferIFID_address; // BufferIFID

	//Mux signals
	sc_signal<bool> Brach_Mux_pcSRC; // BufferEXMEM
	sc_signal<sc_uint<16>> BufferEXMEM_MUX_op1; // BufferEXMEM

	//BufferIFID signals
	sc_signal<bool> Controller_BufferIFID_enable; // Controller
	sc_signal<bool> Controller_BufferIFID_write; // Controller
	sc_signal<bool> Controller_BufferIFID_reset; // Controller
	sc_signal<sc_uint<16>> BufferIFID_BufferIDEX_address; // BufferIDEX
	sc_signal<sc_uint<32>> BufferIFID_Controller_instruction; // Controller
	sc_signal<sc_uint<6>> BufferIFID_BufferIDEX_Opdest; // BufferIDEX
	sc_signal<sc_uint<6>> BufferIFID_Registers_readRegister1; // Registers
	sc_signal<sc_uint<6>> BufferIFID_Registers_readRegister2; // Registers
	sc_signal<sc_int<16>> BufferIFID_Registers_immediate; // Registers
	sc_signal<sc_uint<4>> BufferIFID_Registers_opcode; // Registers
    sc_signal<sc_uint<16>> BufferIFID_BufferIDEX_label_j; // BufferIDEX

//-----------------------------------------------------------------------------------------------

	PC.clk(clk);
	PC.reset(reset);
	PC.enable(Controller_PC_enable);
	PC.pcInput(Mux_PC_loadAddrs);
	PC.pcOutput(PC_IM_pcOutput);

	IM.clk(clk);
	IM.enable(Controller_IM_enable);
	IM.address(PC_IM_pcOutput);
	IM.write(Controller_IM_Write);
	IM.instruction(IM_BufferIDEX_instruction);

	Addr.first_value(Addr_MUX_op0);
	Addr.output_value(PC_Addr_pcOutput);
	Addr.output_value(Addr_BufferIFID_address);

	Mux.in0(Mux_PC_loadAddrs);
	Mux.in1(BufferEXMEM_MUX_op1);
	Mux.pcSRC(Brach_Mux_pcSRC);

	BufferIFID.clk(clk);
	BufferIFID.enable(Controller_BufferIFID_enable);
	BufferIFID.reset(Controller_BufferIFID_reset);
	BufferIFID.write(Controller_BufferIFID_write);
	BufferIFID.instruction(IM_BufferIDEX_instruction);
	BufferIFID.Address_Addr(Addr_BufferIFID_address);
	


	return 0;
}

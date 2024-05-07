
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

	Registers RegistersData("RegistersData");

	BufferIDEX BufferIDEX("BufferIDEX");

	Controller Controller("Controller");
/*
	
	

	Alu ALU("ALU");

	DataMemory DM("DM");

	MuxDM MuxDM("MuxDM");


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
	sc_signal<sc_uint<32>> IM_BufferIFID_instruction; // BufferIDEX

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
	sc_signal<sc_uint<32>> BufferIFID_Controller_instruction; // Controller
	sc_signal<sc_uint<16>> BufferIFID_BufferIDEX_address; // BufferIDEX
	sc_signal<sc_uint<6>> BufferIFID_BufferIDEX_Opdest; // BufferIDEX
	sc_signal<sc_uint<6>> BufferIFID_Registers_readRegister1; // Registers
	sc_signal<sc_uint<6>> BufferIFID_Registers_readRegister2; // Registers
	sc_signal<sc_int<16>> BufferIFID_Registers_immediate; // Registers
	sc_signal<sc_uint<4>> BufferIFID_Registers_opcode; // Registers
    sc_signal<sc_uint<16>> BufferIFID_BufferIDEX_label_j; // BufferIDEX

	//Registers signals
	sc_signal<bool> Controller_Registers_enable; // Controller
	sc_signal<bool> Controller_Registers_RegWrite; // Controller
	sc_signal<bool> Controller_Registers_reset; // Controller
	sc_signal<sc_uint<6>> BufferMEMWB_Registers_writeRegister; // BufferMEMWB
	sc_signal<sc_int<32>> MUXDM_Registers_writeData; //   MuxDM
	sc_signal<sc_int<32>> Registers_BufferIDEX_readData1; // BufferIDEX
	sc_signal<sc_int<32>> Registers_BufferIDEX_readData2; // BufferIDEX

	//BufferIDEX signals
	sc_signal<bool> Controller_BufferIDEX_enable; // Controller
	sc_signal<bool> Controller_BufferIDEX_reset; // Controller
	sc_signal<bool> Controller_BufferIDEX_write; // Controller
	sc_signal<bool> Controller_BufferIDEX_Reset; // Controller

	//Controller signals
	
	sc_signal<bool> Controller_reset; // Controller
	sc_signal<bool> ALU_Controller_zero; // ULA
	sc_signal<sc_uint<16>> Controller_BufferIDEX_pcJump; // BufferIDEX
	sc_signal<bool> Controller_BufferIDEX_pcLoad; // BufferIDEX
	sc_signal<bool>	Controller_BufferIDEX_EnableDM; //BufferIDEX
	sc_signal<bool>	Controller_BufferIDEX_WriteDM;//BufferIDEX
	sc_signal<bool>	Controller_BufferIDEX_MemtoReg; //BufferIDEX
	sc_signal<bool>	Controller_BufferIDEX_EnableBufferIDEX; //BufferIDEX
	sc_signal<bool>	Controller_BufferIDEX_WriteBufferIDEX; //BufferIDEX
	sc_signal<bool>	Controller_BufferIDEX_ResetBufferIDEX;
	sc_signal<bool>	Controller_BufferEXMEM_enableBufferEXMEM; //BufferEXMEM
	sc_signal<bool>	Controller_BufferEXMEM_WriteBufferEXMEM; //BufferEXMEM
	sc_signal<bool>	Controller_BufferEXMEM_ResetBufferEXMEM; //BufferEXMEM
	sc_signal<bool>	Controller_BufferMEMWB_enableBufferMEMWB; //BufferMEMWB
	sc_signal<bool>	Controller_BufferMEMWB_WriteBufferMEMWB; //BufferMEMWB
	sc_signal<bool>	Controller_BufferMEMWB_ResetBufferMEMWB; //BufferMEMWB
	sc_signal<sc_uint<4>> Controller_BufferIDEX_aluOp; //Controller
	sc_signal<bool> Controller_BufferIDEX_resetALU; //Controller







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
	IM.instruction(IM_BufferIFID_instruction);

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
	BufferIFID.instruction(IM_BufferIFID_instruction);
	BufferIFID.Address_Addr(Addr_BufferIFID_address);
	BufferIFID.Address_Addr_Out(BufferIFID_BufferIDEX_address);
	BufferIFID.instruction_out(BufferIFID_Controller_instruction);
	BufferIFID.readRegister1(BufferIFID_Registers_readRegister1);
	BufferIFID.readRegister2(BufferIFID_Registers_readRegister2);
	BufferIFID.immediate_out(BufferIFID_Registers_immediate);
	BufferIFID.opcode_out(BufferIFID_Registers_opcode);
	BufferIFID.DestReg_out(BufferIFID_BufferIDEX_Opdest);
	BufferIFID.label_j(BufferIFID_BufferIDEX_label_j);

	RegistersData.clk(clk);
	RegistersData.enable(Controller_Registers_enable);
	RegistersData.RegWrite(Controller_Registers_RegWrite);
	RegistersData.opcode(BufferIFID_Registers_opcode);
	RegistersData.writeRegister(BufferMEMWB_Registers_writeRegister);
	RegistersData.writeData(MUXDM_Registers_writeData);
	RegistersData.readRegister1(BufferIFID_Registers_readRegister1);
	RegistersData.readRegister2(BufferIFID_Registers_readRegister2);
	RegistersData.immediate(BufferIFID_Registers_immediate);
	RegistersData.readData1(Registers_BufferIDEX_readData1);
	RegistersData.readData2(Registers_BufferIDEX_readData2);


	BufferIDEX.clk(clk);
	BufferIDEX.enable(Controller_BufferIDEX_enable);
	BufferIDEX.reset(Controller_BufferIDEX_reset);
	BufferIDEX.write(Controller_BufferIDEX_write);
	BufferIDEX.opcode(BufferIFID_Registers_opcode);
	BufferIDEX.pcLoad(Controller_BufferIDEX_pcLoad);
	BufferIDEX.dmEnable(Controller_BufferIDEX_EnableDM);
	BufferIDEX.dmWrite(Controller_BufferIDEX_WriteDM);
	BufferIDEX.aluReset(Controller_BufferIDEX_resetALU);
	BufferIDEX.aluOp(Controller_BufferIDEX_aluOp);
	BufferIDEX.Branch()
	BufferIDEX.memToReg(Controller_BufferIDEX_MemtoReg);



	Controller.clk(clk);
	Controller.reset(Controller_reset);
	Controller.instruction(BufferIFID_Controller_instruction);
	Controller.pcEnable(Controller_PC_enable);
	Controller.PcLoad(Controller_BufferIDEX_pcLoad);
	Controller.pcReset(Controller_PC_reset);
	Controller.regEnable(Controller_Registers_enable);
	Controller.regWrite(Controller_Registers_RegWrite);
	Controller.imEnable(Controller_IM_enable);
	Controller.imwrite(Controller_IM_Write);
	Controller.dmEnable(Controller_BufferIDEX_EnableDM);
	Controller.dmWrite(Controller_BufferIDEX_WriteDM);
	Controller.memToReg(Controller_BufferIDEX_MemtoReg);
	Controller.pcjump(Controller_BufferIDEX_pcJump);
	Controller.enable_BufferIDEX(Controller_BufferIDEX_EnableBufferIDEX);
	Controller.write_BufferIDEX(Controller_BufferIDEX_WriteBufferIDEX);
	Controller.reset_BufferIDEX(Controller_BufferIDEX_ResetBufferIDEX);
	Controller.enable_BufferEXMEM(Controller_BufferEXMEM_enableBufferEXMEM);
	Controller.write_BufferEXMEM(Controller_BufferEXMEM_WriteBufferEXMEM);
	Controller.reset_BufferEXMEM(Controller_BufferEXMEM_ResetBufferEXMEM);
	Controller.enable_BufferMEMWB(Controller_BufferMEMWB_enableBufferMEMWB);
	Controller.write_BufferMEMWB(Controller_BufferMEMWB_WriteBufferMEMWB);
	Controller.reset_BufferMEMWB(Controller_BufferMEMWB_ResetBufferMEMWB);
	Controller.aluOp(Controller_BufferIDEX_aluOp);
	Controller.zero(ALU_Controller_zero);


	sc_signal<bool> Controller_Registers_reset; // Controller







	return 0;
}


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

int sc_main(int, char*[]) {
	Controller Controller("Controller");

	ProgramCounter PC("PC");

	InstructionMemory IM("IM");

	Addr Addr("Addr");

	Mux Mux("Mux");

	BufferIFID BufferIFID("BufferIFID");

	Registers RegistersData("RegistersData");

	BufferIDEX BufferIDEX("BufferIDEX");

	

	Alu ALU("ALU");

	BufferEXMEM BufferEXMEM("BufferEXMEM");

	DataMemory DM("DM");

	BufferMEMWB BufferMEMWB("BufferMEMWB");

	MuxDM MuxDM("MuxDM");

//-----------------------------------------------------------------------------------------------
	sc_signal<bool> clk;

	//pc signals
	sc_signal<bool> Controller_PC_reset; //controller OK
	sc_signal<bool> Controller_PC_enable; // controller OK
	sc_signal<bool> BufferEXMEM_PC_PCjump; // BufferEXMEM	OK
	sc_signal<bool> pcLoad;
	sc_signal<sc_uint<16>> Mux_PC_Addrs;	// Mux	OK
	sc_signal<sc_uint<16>> PC_Addr_IM_pcOutput;// IM OK
	//IM signals
	sc_signal<bool> Controller_IM_enable; // controller
	sc_signal<bool> Controller_IM_Write;
	sc_signal<sc_uint<32>> IM_BufferIFID_instruction; // BufferIDEX

	//Addr signals
	sc_signal<sc_uint<16>> Addr_MUX_op0; // Mux
	sc_signal<sc_uint<16>> Addr_MUX_BufferIFID_address; // BufferIFID

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
	sc_signal<bool> BufferMEMWB_Registers_RegWrite; // Controller
	sc_signal<bool> Controller_Registers_reset; // Controller
	sc_signal<sc_uint<6>> BufferMEMWB_Registers_writeRegister; // BufferMEMWB
	sc_signal<sc_int<32>> MUXDM_Registers_writeData; //   MuxDM
	sc_signal<sc_int<32>> Registers_BufferIDEX_readData1; // BufferIDEX
	sc_signal<sc_int<32>> Registers_BufferIDEX_readData2; // BufferIDEX
	sc_signal<sc_int<32>> Registers_BufferIDEX_writeDataOut; // Registers
	

	//BufferIDEX signals
	sc_signal<bool> Controller_BufferIDEX_enable; // Controller
	sc_signal<bool> Controller_BufferIDEX_reset; // Controller
	sc_signal<bool> Controller_BufferIDEX_write; // Controller
	sc_signal<bool> Controller_BufferIDEX_Reset; // Controller
	sc_signal<sc_int<32>> BufferIDEX_ALU_registerData1;
	sc_signal<sc_int<32>> BufferIDEX_ALU_registerData2;
	sc_signal<sc_uint<6>> BufferIDEX_BufferEXMEM_destReg;
	sc_signal<bool> BufferIDEX_BufferEXMEM_Branch_output;
	sc_signal<bool> BufferIDEX_BufferEXMEM_memToReg_output;
	sc_signal<sc_uint<4>> BufferIDEX_ALU_opcode_output;
	sc_signal<sc_uint<4>> BufferIDEX_BufferEXMEM_opcode_output;
	sc_signal<sc_uint<16>> BufferIDEX_BufferEXMEM_pc_output;
	sc_signal<sc_uint<16>> BufferIDEX_BufferEXMEM_label_j_output;
	sc_signal<bool> BufferIDEX_BufferEXMEM_pcLoad_output;
	sc_signal<bool> BufferIDEX_BufferEXMEM_dmEnable_output;
	sc_signal<bool> BufferIDEX_BufferEXMEM_dmWrite_output;
	sc_signal<bool> BufferIDEX_ALU_aluReset_output;
	sc_signal<bool> BufferIDEX_BufferEXMEM_RegWrite;
	sc_signal<sc_int<32>> BufferIDEX_BufferEXMEM_dataDM;

	//Controller signals
	
	sc_signal<bool> Controller_reset; // Controller
	sc_signal<sc_uint<16>> Controller_BufferIDEX_pcJump; // BufferIDEX
	sc_signal<bool> Controller_BufferIDEX_Branch; // BufferIDEX
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
	sc_signal<bool>Controller_BufferIDEX_RegWrite;
	sc_signal<int> Controller_stateOut;
	//ALU
	sc_signal<bool> ALU_BufferEXMEM_zero;
	sc_signal<sc_int<32>> ALU_Bufferexmem_result;

	//BufferEXMEM
	sc_signal<bool> BufferEXMEM_DataMemory_DMenable;
	sc_signal<bool> BufferEXMEM_DataMemory_DMWrite;
	sc_signal<bool> BufferEXMEM_BufferMEMWB_MemReg;
	sc_signal<bool> BufferEXMEM_BufferMEMWB_RegWrite;
	sc_signal<sc_int<32>>BufferEXMEM_DataMemory_WriteData;
	sc_signal<sc_uint<6>> BufferEXMEM_BufferMEMWB_Opdest;
	sc_signal<sc_int<32>> BufferEXMEM_BufferMEMWB_address;
	
	//DataMemory
	sc_signal<sc_int<32>> BufferEXMEM_DataMemory_Adress;
	sc_signal<sc_int<32>> DataMemory_BufferMEMWB_ReadData;
	sc_signal<bool> BufferMEMWB_MUXDM_memtoreg;
	sc_signal<sc_int<32>> BufferMEMWB_muxDM_readDataOutput;
	sc_signal<sc_int<32>> BufferMEMWB_muxDM_dataAdressOutput;




//-----------------------------------------------------------------------------------------------

	PC.clk(clk);
	PC.reset(Controller_PC_reset);
	PC.enable(Controller_PC_enable);
	PC.pcInput(Mux_PC_Addrs);
	PC.pcOutput(PC_Addr_IM_pcOutput);
	PC.load(BufferEXMEM_PC_PCjump);

	IM.clk(clk);
	IM.enable(Controller_IM_enable);
	IM.write(Controller_IM_Write);
	IM.address(PC_Addr_IM_pcOutput);
	IM.instruction(IM_BufferIFID_instruction);
	
	Addr.first_value(PC_Addr_IM_pcOutput);
	Addr.output_value(Addr_MUX_BufferIFID_address);

	Mux.in0(Addr_MUX_BufferIFID_address);
	Mux.in1(BufferEXMEM_MUX_op1);
	Mux.pcSRC(Brach_Mux_pcSRC);
	Mux.out(Mux_PC_Addrs);

	BufferIFID.clk(clk);
	BufferIFID.enable(Controller_BufferIFID_enable);
	BufferIFID.reset(Controller_BufferIFID_reset);
	BufferIFID.write(Controller_BufferIFID_write);
	BufferIFID.instruction(IM_BufferIFID_instruction);
	BufferIFID.instruction_out(BufferIFID_Controller_instruction);
	BufferIFID.readRegister1(BufferIFID_Registers_readRegister1);
	BufferIFID.readRegister2(BufferIFID_Registers_readRegister2);
	BufferIFID.immediate_out(BufferIFID_Registers_immediate);
	BufferIFID.opcode_out(BufferIFID_Registers_opcode);
	BufferIFID.DestReg_out(BufferIFID_BufferIDEX_Opdest);
	BufferIFID.label_j(BufferIFID_BufferIDEX_label_j);

	RegistersData.clk(clk);
	RegistersData.enable(Controller_Registers_enable);
	RegistersData.RegWrite(BufferMEMWB_Registers_RegWrite);
	RegistersData.opcode(BufferIFID_Registers_opcode);
	RegistersData.writeRegister(BufferMEMWB_Registers_writeRegister);
	RegistersData.writeData(MUXDM_Registers_writeData);
	RegistersData.readRegister1(BufferIFID_Registers_readRegister1);
	RegistersData.readRegister2(BufferIFID_Registers_readRegister2);
	RegistersData.immediate(BufferIFID_Registers_immediate);
	RegistersData.readData1(Registers_BufferIDEX_readData1);
	RegistersData.readData2(Registers_BufferIDEX_readData2);
	RegistersData.destReg(BufferIFID_BufferIDEX_Opdest);
	RegistersData.writeDataOut(Registers_BufferIDEX_writeDataOut);

	BufferIDEX.clk(clk);
	BufferIDEX.enable(Controller_BufferIDEX_enable);
	BufferIDEX.reset(Controller_BufferIDEX_reset);
	BufferIDEX.write(Controller_BufferIDEX_write);
	BufferIDEX.pcLoad_out(BufferIDEX_BufferEXMEM_pcLoad_output);
	BufferIDEX.opcode(BufferIFID_Registers_opcode);
	BufferIDEX.pcLoad(Controller_BufferIDEX_pcLoad);
	BufferIDEX.dmEnable(Controller_BufferIDEX_EnableDM);
	BufferIDEX.dmWrite(Controller_BufferIDEX_WriteDM);
	BufferIDEX.aluReset(Controller_BufferIDEX_resetALU);
	BufferIDEX.aluOp(Controller_BufferIDEX_aluOp);
	BufferIDEX.memToReg(Controller_BufferIDEX_MemtoReg);
	BufferIDEX.pcJump(Controller_BufferIDEX_pcJump);
	BufferIDEX.Branch(Controller_BufferIDEX_Branch);
	BufferIDEX.label_j(BufferIFID_BufferIDEX_label_j);
	BufferIDEX.registerData1(Registers_BufferIDEX_readData1);
	BufferIDEX.registerData2(Registers_BufferIDEX_readData2);
	BufferIDEX.register1_Output(BufferIDEX_ALU_registerData1);
	BufferIDEX.register2_Output(BufferIDEX_ALU_registerData2);
	BufferIDEX.destReg(BufferIFID_BufferIDEX_Opdest);
	BufferIDEX.Branch_Output(BufferIDEX_BufferEXMEM_Branch_output);
	BufferIDEX.memToReg_Output(BufferIDEX_BufferEXMEM_memToReg_output);
	BufferIDEX.aluOp_out(BufferIDEX_ALU_opcode_output);
	BufferIDEX.pc_out(BufferIDEX_BufferEXMEM_pc_output);
	BufferIDEX.label_j_out(BufferIDEX_BufferEXMEM_label_j_output);
	BufferIDEX.dmEnable_out(BufferIDEX_BufferEXMEM_dmEnable_output);
	BufferIDEX.dmWrite_out(BufferIDEX_BufferEXMEM_dmWrite_output);
	BufferIDEX.aluReset_out(BufferIDEX_ALU_aluReset_output);
	BufferIDEX.opcode_Output(BufferIDEX_BufferEXMEM_opcode_output);
	BufferIDEX.regWrite(Controller_BufferIDEX_RegWrite);
	BufferIDEX.regWrite_Output(BufferIDEX_BufferEXMEM_RegWrite);
	BufferIDEX.dataDM(Registers_BufferIDEX_writeDataOut);
	BufferIDEX.dataDMout(BufferIDEX_BufferEXMEM_dataDM);
	BufferIDEX.destReg_Output(BufferIDEX_BufferEXMEM_destReg);


	Controller.clk(clk);
	Controller.reset(Controller_reset);
	Controller.instruction(BufferIFID_Controller_instruction);
	Controller.pcEnable(Controller_PC_enable);
	Controller.PcLoad(Controller_BufferIDEX_pcLoad);
	Controller.pcReset(Controller_PC_reset);
	Controller.enable_BufferIFID(Controller_BufferIFID_enable);
	Controller.write_BufferIFID(Controller_BufferIFID_write);
	Controller.reset_BufferIFID(Controller_BufferIFID_reset);
	Controller.regEnable(Controller_Registers_enable);
	Controller.regWrite(Controller_BufferIDEX_RegWrite);
	Controller.imEnable(Controller_IM_enable);
	Controller.imwrite(Controller_IM_Write);
	Controller.dmEnable(Controller_BufferIDEX_EnableDM);
	Controller.dmWrite(Controller_BufferIDEX_WriteDM);
	Controller.memToReg(Controller_BufferIDEX_MemtoReg);
	Controller.pcjump(Controller_BufferIDEX_pcJump);
	Controller.branch(Controller_BufferIDEX_Branch);
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
	Controller.zero(ALU_BufferEXMEM_zero);
	Controller.stateOut(Controller_stateOut);
	Controller.aluReset(Controller_BufferIDEX_resetALU);

	ALU.clk(clk);
	ALU.reset(BufferIDEX_ALU_aluReset_output);
	ALU.opcode(BufferIDEX_ALU_opcode_output);
	ALU.first_value(BufferIDEX_ALU_registerData1);
	ALU.second_value(BufferIDEX_ALU_registerData2);
	ALU.output_value(ALU_Bufferexmem_result);
	ALU.zero(ALU_BufferEXMEM_zero);

	BufferEXMEM.clk(clk);
	BufferEXMEM.reset(Controller_BufferEXMEM_ResetBufferEXMEM);
	BufferEXMEM.enable(Controller_BufferEXMEM_enableBufferEXMEM);
	BufferEXMEM.write(Controller_BufferEXMEM_WriteBufferEXMEM);
	BufferEXMEM.pcLoadOut(BufferEXMEM_PC_PCjump);
	BufferEXMEM.MemReg(BufferIDEX_BufferEXMEM_memToReg_output);
	BufferEXMEM.regWrite(BufferIDEX_BufferEXMEM_RegWrite);
	BufferEXMEM.opcode(BufferIDEX_BufferEXMEM_opcode_output);
    BufferEXMEM.DMWrite(BufferIDEX_BufferEXMEM_dmWrite_output);
	BufferEXMEM.DMenable(BufferIDEX_BufferEXMEM_dmEnable_output);
	BufferEXMEM.Branch(BufferIDEX_BufferEXMEM_Branch_output);
	BufferEXMEM.opdest(BufferIDEX_BufferEXMEM_destReg);
	BufferEXMEM.zero(ALU_BufferEXMEM_zero);
	BufferEXMEM.ALU_result(ALU_Bufferexmem_result);
	BufferEXMEM.label_j_out(BufferEXMEM_MUX_op1);
	BufferEXMEM.regWrite_Output(BufferEXMEM_BufferMEMWB_RegWrite);
	BufferEXMEM.MemReg_Output(BufferEXMEM_BufferMEMWB_MemReg);
	BufferEXMEM.pcLoad(BufferIDEX_BufferEXMEM_pcLoad_output);
	BufferEXMEM.opdest_Out(BufferEXMEM_BufferMEMWB_Opdest);
	BufferEXMEM.dataDMOut(BufferEXMEM_DataMemory_WriteData);
	BufferEXMEM.label_j(BufferIDEX_BufferEXMEM_label_j_output);


	
	BufferEXMEM.BranchOUT(Brach_Mux_pcSRC);
	BufferEXMEM.DMenableOUT(BufferEXMEM_DataMemory_DMenable);
	BufferEXMEM.DMWriteOUT(BufferEXMEM_DataMemory_DMWrite);
	BufferEXMEM.ALU_result_Out(BufferEXMEM_DataMemory_Adress);
	BufferEXMEM.dataDM(BufferIDEX_BufferEXMEM_dataDM);

	DM.clk(clk);
	DM.memWrite(BufferEXMEM_DataMemory_DMWrite);
	DM.enable(BufferEXMEM_DataMemory_DMenable);
	DM.write_data(BufferEXMEM_DataMemory_WriteData);
	DM.address(BufferEXMEM_DataMemory_Adress);
	DM.readData(DataMemory_BufferMEMWB_ReadData);

	BufferMEMWB.clk(clk);
	BufferMEMWB.RegWrite(BufferEXMEM_BufferMEMWB_RegWrite);
	BufferMEMWB.memReg(BufferEXMEM_BufferMEMWB_MemReg);
	BufferMEMWB.opDestino(BufferEXMEM_BufferMEMWB_Opdest);
	BufferMEMWB.dataAdress(BufferEXMEM_BufferMEMWB_address);
	BufferMEMWB.readData(DataMemory_BufferMEMWB_ReadData);
	BufferMEMWB.regWriteOutput(BufferMEMWB_Registers_RegWrite);
	BufferMEMWB.writeRegister(BufferMEMWB_Registers_writeRegister);
	BufferMEMWB.memRegOut(BufferMEMWB_MUXDM_memtoreg);
	BufferMEMWB.readDataOutput(BufferMEMWB_muxDM_readDataOutput);
	BufferMEMWB.dataAdressOutput(BufferMEMWB_muxDM_dataAdressOutput);

	MuxDM.memReg(BufferMEMWB_MUXDM_memtoreg);
	MuxDM.in0(BufferMEMWB_muxDM_readDataOutput);
	MuxDM.in1(BufferMEMWB_muxDM_dataAdressOutput);
	MuxDM.out(MUXDM_Registers_writeData);

//-----------------------------------------------------------------------------------------------
for (int i = 0; i < 50; i++) {
		clk = 1;
		sc_start(10, SC_NS);
		clk = 0;
		sc_start(10, SC_NS);
	}
	

	return 0;
}

#include <systemc.h>
#include<InstructionMemory.hpp>
#include<ProgramCounter.hpp>
#include<Registers.hpp>
#include<Alu.hpp>
#include<DataMemory.hpp>
#include<AddA.hpp>
#include<Addr.hpp>
#include<Controller.hpp>
#include<MuxAlu.hpp>
#include<Mux.hpp>
#include<MuxDM.hpp>

int sc_main(int arg, char* argv[]) {

	ProgramCounter PC("PC");

	InstructionMemory IM("IM");

	Registers RegistersData("RegistersData");

	Alu ALU("ALU");

	DataMemory DM("DM");

	AddA AddA("AddA");

	Addr Addr("Addr");

	MuxAlu MuxAlu("MuxAlu");

	Mux Mux("Mux");

	MuxDM MuxDM("MuxDM");

//-----------------------------------------------------------------------------------------------

	sc_signal<bool>       clock; // Clock signal

	// Signals for ProgramCounter
    sc_signal<sc_uint<9>> PC_Input;
    sc_signal<bool>       PC_reset;
	sc_signal<bool>       PC_enable;
	sc_signal<bool>       PC_load;
    sc_signal<sc_uint<9>> PC_IM_address;

	// Signals for InstructionMemory
	sc_signal<bool>       IM_enable;
	sc_signal<bool>       IM_write;
	//sc_signal<sc_uint<9>> PC_IM_address;
	sc_signal<sc_uint<32>>IM_Buffer1_instructionIM;

	// Signals for Registers
	sc_signal<bool>       RegistersData_Controller_RegWrite;
	sc_signal<sc_uint<6>> RegistersData_MUX3_writeRegister;
	sc_signal<sc_int<32>> RegistersData_MUX4_writeData;
	sc_signal<sc_uint<6>> Buffer1_RegistersData_readRegister1;
	sc_signal<sc_uint<6>> Buffer1_RegistersData_readRegister2;
	sc_signal<sc_int<32>> RegistersData_Buffer2_readData1;
	sc_signal<sc_int<32>> RegistersData_Buffer2_readData2;

	// Signals for ALU
	sc_signal<bool>       Buffer3_ALU_zero;
	sc_signal<bool>       Buffer3_ALU_negative;
	sc_signal<sc_uint<4>> Controller_ALU_opcode;
	sc_signal<sc_int<32>> ALU_Buffer2_ALU_input1;
	sc_signal<sc_int<32>> ALU_Buffer1_ALU_input2;
	sc_signal<sc_int<32>> Buffer3_ALU_result;

	// Signals for DataMemory
	sc_signal<bool>       Buffer3_DM_enable;
	sc_signal<bool>       Buffer3_DM_memWrite;
	sc_signal<sc_int<32>> Buffer3_DM_write_data;
	sc_signal<sc_int<9>>  Buffer3_DM_address;
	sc_signal<sc_int<32>> DM_Buffer4_readData;

	// Signals for AddA
	sc_signal<sc_uint<9>> Buffer2_AddA_input1;
	sc_signal<sc_uint<9>> Buffer2_AddA_input2;
	sc_signal<sc_uint<9>> AddA_Buffer3_output;

	// Signals for Addr
	sc_signal<sc_uint<9>> PC_Addr_input;
	sc_signal<sc_uint<9>> Addr_Buffer1_output;


	// MuxAlu signals
	sc_signal<bool>       Buffer2_MuxAlu_aluSRC;
	sc_signal<sc_int<32>> Buffer2_MuxAlu_input0;
	sc_signal<sc_int<32>> Buffer2_MuxAlu_input1;
	sc_signal<sc_int<32>> MuxAlu_alu_output;

	// MuxPC signals
	sc_signal<bool>       Buffer3_Branch_MuxPC_pcSRC;
	sc_signal<sc_uint<9>> Addr_Mux_input0;
	sc_signal<sc_uint<9>> Buffer3_Mux_input1;
	sc_signal<sc_uint<9>> Mux_PC_output;

	// MuxDM signals
	sc_signal<bool>       Buffer4_MuxDM_dmSRC;
	sc_signal<sc_int<32>> Buffer4_MuxDM_input0;
	sc_signal<sc_int<32>> Buffer4_MuxDM_input1;
	sc_signal<sc_int<32>> MuxDM_Alu_output;

//-----------------------------------------------------------------------------------------------

	// Connecting the IM signals
	IM.clk(clock);
	IM.enable(IM_enable);
	IM.write(IM_write);
	IM.instruction(IM_Buffer1_instructionIM);
	IM.address(PC_IM_address);

	// Connecting the PC signals
	PC.clk(clock);
	PC.enable(PC_enable);
	PC.reset(PC_reset);
	PC.load(PC_load);
	PC.pcInput(PC_Input);
	PC.pcOutput(PC_IM_address);
	
	// Connecting the Registers signals
	RegistersData.clk(clock);
	RegistersData.RegWrite(RegistersData_Controller_RegWrite);
	RegistersData.writeRegister(RegistersData_MUX3_writeRegister);
	RegistersData.writeData(RegistersData_MUX4_writeData);
	RegistersData.readRegister1(Buffer1_RegistersData_readRegister1);
	RegistersData.readRegister2(Buffer1_RegistersData_readRegister2);
	RegistersData.readData1(RegistersData_Buffer2_readData1);
	RegistersData.readData2(RegistersData_Buffer2_readData2);
	
	// Connecting the ALU signals
	ALU.zero(Buffer3_ALU_zero);
	ALU.negative(Buffer3_ALU_negative);
	ALU.opcode(Controller_ALU_opcode);
	ALU.first_value(ALU_Buffer2_ALU_input1);
	ALU.second_value(ALU_Buffer1_ALU_input2);
	ALU.output_value(Buffer3_ALU_result);

	// Connecting the DM signals
	DM.clk(clock);
	DM.enable(Buffer3_DM_enable);
	DM.memWrite(Buffer3_DM_memWrite);
	DM.write_data(Buffer3_DM_write_data);
	DM.address(Buffer3_DM_address);
	DM.readData(DM_Buffer4_readData);

	// Connecting the AddA signals
	AddA.first_value(Buffer2_AddA_input1);
	AddA.second_value(Buffer2_AddA_input2);
	AddA.output_value(AddA_Buffer3_output);

	// Connecting the Addr signals
	Addr.first_value(PC_Addr_input);
	Addr.output_value(Addr_Buffer1_output);

	// Connecting the MuxAlu signals
	MuxAlu.aluSRC(Buffer2_MuxAlu_aluSRC);
	MuxAlu.in0(Buffer2_MuxAlu_input0);
	MuxAlu.in1(Buffer2_MuxAlu_input1);
	MuxAlu.out(MuxAlu_alu_output);

	// Connecting the MuxPC signals
	Mux.pcSRC(Buffer3_Branch_MuxPC_pcSRC);
	Mux.in0(Addr_Mux_input0);
	Mux.in1(Buffer3_Mux_input1);
	Mux.out(Mux_PC_output);

	// Connecting the MuxDM signals
	MuxDM.memReg(Buffer4_MuxDM_dmSRC);
	MuxDM.in0(Buffer4_MuxDM_input0);
	MuxDM.in1(Buffer4_MuxDM_input1);
	MuxDM.out(MuxDM_Alu_output);

	// Connecting the Controller signals

	sc_start(1, SC_NS);
	return 0;
}

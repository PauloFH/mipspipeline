#include <systemc.h>
#include<InstructionMemory.hpp>
#include<ProgramCounter.hpp>
#include<Registers.hpp>
#include<Alu.hpp>
#include<DataMemory.hpp>
#include<AddA.hpp>
#include<Addr.hpp>
#include<Controller.hpp>
#include<Mux.hpp>
#include<MuxDM.hpp>
#include<BufferIFID.hpp>

int sc_main(int arg, char* argv[]) {

	ProgramCounter PC("PC");

	InstructionMemory IM("IM");

	Registers RegistersData("RegistersData");

	Alu ALU("ALU");

	DataMemory DM("DM");

	AddA AddA("AddA");

	Addr Addr("Addr");


	Mux Mux("Mux");

	MuxDM MuxDM("MuxDM");

	BufferIFID BufferIFID("BufferIFID");
//-----------------------------------------------------------------------------------------------

	sc_signal<bool>       clock; // Clock signal

	// Signals for ProgramCounter
    sc_signal<sc_uint<16>> PC_Input;
    sc_signal<bool>       PC_reset;
	sc_signal<bool>       PC_enable;
	sc_signal<bool>       PC_load;
    sc_signal<sc_uint<16>> PC_IM_address;

	// Signals for InstructionMemory
	sc_signal<bool>       IM_enable;
	//sc_signal<sc_uint<9>> PC_IM_address;
	sc_signal<sc_uint<32>>IM_BufferIFIM_instructionIM;

	// Signals for Registers
	sc_signal<bool>       RegistersData_Controller_RegWrite;
	sc_signal<sc_uint<6>> RegistersData_MUX3_writeRegister;
	sc_signal<sc_int<32>> RegistersData_MUX4_writeData;
	sc_signal<sc_uint<6>> BufferIFIM_RegistersData_readRegister1;
	sc_signal<sc_uint<6>> BufferIFIM_RegistersData_readRegister2;
	sc_signal<sc_int<32>> RegistersData_Buffer2_readData1;
	sc_signal<sc_int<32>> RegistersData_Buffer2_readData2;
	sc_signal<sc_uint<4>> BufferIFID_RegistersData_opcode;
	sc_signal<sc_int<16>> BufferIFID_RegistersData_immediate;
	
	sc_signal<sc_uint<4>> BufferIFID_RegistersData_opcode;
	sc_signal<sc_int<16>> BufferIFID_RegistersData_immediate;

	// Signals for ALU
	sc_signal<bool>       ALU_Buffer3_zero;
	sc_signal<bool>       ALU_Buffer3_notequal;
	sc_signal<sc_uint<4>> Controller_ALU_opcode;
	sc_signal<sc_int<32>> Buffer2_ALU_input1;
	sc_signal<sc_int<32>> ALU_MuxDST_ALU_input2;
	sc_signal<sc_int<32>> ALU_Buffer3_result;

	// Signals for DataMemory
	sc_signal<bool>       Buffer3_DM_enable;
	sc_signal<bool>       Buffer3_DM_memWrite;
	sc_signal<sc_int<32>> Buffer3_DM_write_data;
	sc_signal<sc_int<32>>  Buffer3_DM_address;
	sc_signal<sc_int<32>> DM_Buffer4_readData;

	// Signals for AddA
	sc_signal<sc_uint<9>> Buffer2_AddA_input1;
	sc_signal<sc_uint<9>> Buffer2_AddA_input2;
	sc_signal<sc_uint<9>> AddA_Buffer3_output;

	// Signals for Addr
	sc_signal<sc_uint<9>> PC_Addr_input;
	sc_signal<sc_uint<9>> Addr_BufferIFIM_output; // BufferIFID


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

	//BufferIFID signals
	sc_signal<bool>        BufferIFID_reset;
	sc_signal<sc_uint<9>>  BufferIFID_BufferIDEX_address;
	sc_signal<sc_uint<6>> BufferIFID_BufferIDEX_DestReg;


	//Controller signals
	sc_signal<sc_uint<32>> BufferIFID_Controller_instruction;
//-----------------------------------------------------------------------------------------------

	// Connecting the IM signals
	IM.clk(clock);
	IM.enable(IM_enable);
	IM.instruction(IM_BufferIFIM_instructionIM);
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
	RegistersData.opcode(BufferIFID_RegistersData_opcode);
	RegistersData.writeRegister(RegistersData_MUX3_writeRegister);
	RegistersData.writeData(RegistersData_MUX4_writeData);
	RegistersData.readRegister1(BufferIFIM_RegistersData_readRegister1);
	RegistersData.readRegister2(BufferIFIM_RegistersData_readRegister2);
	RegistersData.immediate(BufferIFID_RegistersData_immediate);
	RegistersData.readData1(RegistersData_Buffer2_readData1);
	RegistersData.readData2(RegistersData_Buffer2_readData2);
	
	// Connecting the ALU signals
	ALU.zero(ALU_Buffer3_zero);
	ALU.notequal(ALU_Buffer3_notequal);
	ALU.opcode(Controller_ALU_opcode);
	ALU.first_value(Buffer2_ALU_input1);
	ALU.second_value(ALU_MuxDST_ALU_input2);
	ALU.output_value(ALU_Buffer3_result);

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
	Addr.output_value(Addr_BufferIFIM_output);

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

	// Connecting the BufferIFID signals
	BufferIFID.clk(clock);
	BufferIFID.reset(BufferIFID_reset);
	BufferIFID.instruction(IM_BufferIFIM_instructionIM);
	BufferIFID.Address_Addr(Addr_BufferIFIM_output);
	BufferIFID.Address_Addr_Out(BufferIFID_BufferIDEX_address);
	BufferIFID.instruction_out(BufferIFID_Controller_instruction);
	BufferIFID.readRegister1(BufferIFIM_RegistersData_readRegister1);
	BufferIFID.readRegister2(BufferIFIM_RegistersData_readRegister2);
	BufferIFID.opcode_out(BufferIFID_RegistersData_opcode);
	BufferIFID.DestReg_out(BufferIFID_BufferIDEX_DestReg);
	BufferIFID.immediate_out(BufferIFID_RegistersData_immediate);

	

	// Connecting the Controller signals

	sc_start(1, SC_NS);
	return 0;
}

#include <systemc.h>
#include<InstructionMemory.hpp>
int sc_main(int arg, char* argv[]) {
;
	InstructionMemory IM("IM");

	sc_signal<bool> clock;
	sc_signal<bool> enableIM;
	sc_signal<bool> writeIM;
	sc_signal<sc_uint<9>> addressIM;
	sc_signal<sc_uint<32>> instruction;
	IM.clk(clock);
	IM.enable(enableIM);
	IM.write(writeIM);
	IM.instruction(instruction);
	
	/*
	sc_trace_file *wf = sc_create_vcd_trace_file("PC");
	sc_trace(wf,clock,"clock");
	sc_trace(wf,enable,"enable");
	sc_trace(wf,reset,"reset");
	sc_trace(wf,load,"load");
	sc_trace(wf,cinp,"cinp");
	sc_trace(wf,coutp,"coutp");
	reset = 0;
	enable = 0;
	clock = 1;
	sc_close_vcd_trace_file(wf);
	*/
	sc_start(1, SC_NS);
	return 0;
}

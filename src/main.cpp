#include <systemc.h>
#include <Dcode.hpp>
#include <ProgramCounter.hpp>


int sc_main(int arg, char* argv[]) {
	Dcode decoder("Decoder");
	sc_signal<bool> clock;
	sc_signal<bool> enable;
	sc_signal<bool> reset;
	sc_signal<bool> load;
	sc_signal<int> cinp;
	sc_signal<int> coutp;
	ProgramCounter pc("PC");
	pc.clock(clock);
	pc.enable(enable);
	pc.reset(reset);
	pc.pcOutput(coutp);
	pc.load(load);
	pc.pcInput(cinp);
	
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

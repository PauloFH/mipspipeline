#include <systemc.h>

#define MEMORY_SIZE 512

SC_MODULE(InstructionMemory) {
    sc_in<bool> clk; 
    sc_in<bool> enable;
    sc_in<int> pc; 
    sc_out<int> instruction; 

    int memory[MEMORY_SIZE];

    void fetchInstruction() {
        int addr = pc.read();
        instruction.write(memory[addr]);
    }

        SC_CTOR(InstructionMemory) {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = rand() % 256;
        }

        SC_METHOD(fetchInstruction);
        sensitive << clk.pos();
    }
};

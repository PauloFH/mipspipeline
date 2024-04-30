#include <systemc.h>

#define MEMORY_SIZE 512

SC_MODULE(InstructionMemory) {
    sc_in<bool> clk; 
    sc_in<bool> enable;
    sc_in<bool> write;
    sc_in<int> pc; 
    sc_in<int> address;
    sc_out<int> instruction; 
    sc_in<std::vector<std::string>>dataInstructions;
    int memory[MEMORY_SIZE];
    int internInstruction;
    SC_HAS_PROCESS(InstructionMemory);

    void fetchInstruction() {
        while (true){
            wait();
            if (enable.read()){
                if (write.read())
                {
                    memory[address.read()] = pc.read();
                }else{
                   instruction.write(memory[address.read()]);
                }
            }
        }
    
    }
    void InstructionRegister(std::vector<int> instr){
            for(int i = 0; i < instr.size(); i++){
                memory[i] = instr[i];
            }
	}

        SC_CTOR(InstructionMemory) {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = 0;
        }
        SC_METHOD(fetchInstruction);
        sensitive << clk.pos();
        }
};

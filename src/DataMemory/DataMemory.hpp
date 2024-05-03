#include <systemc.h>

#define MEMORY_SIZE 4096

SC_MODULE(DataMemory) {
    sc_in<bool> clk; 
    sc_in<bool> memWrite; 
    sc_in<bool> enable; 
    sc_in<int> write_data; 
    sc_in<int> address; 
    sc_out<int> readData; 

    int memory[MEMORY_SIZE];
    
    void memoryOperation() {
        int localAddres = 0;
        if (enable.read() == true) {

             if(memWrite.read()== true){
                     localAddres = address.read();
                     readData.write(memory[localAddres]);
            } else {
                     localAddres = address.read();
                     memory[localAddres] = write_data.read();
            }
        }

    }
        SC_CTOR(DataMemory) {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = 0;
        }
        SC_METHOD(memoryOperation);
        sensitive << clk.pos();
    }

};

#include <systemc.h>

#define MEMORY_SIZE 4096

SC_MODULE(DataMemory) {
    sc_in<bool> clk; 
    sc_in<bool> memWrite; 
    sc_in<bool> enable; 
    sc_in<sc_int<32>> write_data; 
    sc_in<sc_int<32>> address; 
    sc_out<sc_int<32>> readData;

    sc_uint<16> internoAdress; 

    sc_int<32> memory[MEMORY_SIZE];
    
    void memoryOperation() {
        internoAdress = address.read();
        sc_uint<16> localAddres = 0;

        if (enable.read() == true) {

             if(memWrite.read()== true){
                     localAddres = internoAdress;
                     readData.write(memory[localAddres]);
            } else {
                     localAddres = internoAdress;
                     memory[localAddres] = write_data.read();
            }
        }

    }
        SC_CTOR(DataMemory) {
        for (int i = 0; i < MEMORY_SIZE; ++i) {
            memory[i] = 0;
        }
        SC_METHOD(memoryOperation);
        sensitive << clk.value_changed();
    }

};

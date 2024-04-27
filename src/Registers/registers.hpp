#include <systemc.h>

#define NUM_REGISTERS 32

SC_MODULE(Registers) {
    sc_in<bool> clk; 
    sc_in<bool> RegWrite; 
    sc_in<int> writeRegister;
    sc_in<int> writeData; 
    sc_in<int> readRegister1; 
    sc_in<int> readRegister2;
    sc_out<int> readData1;
    sc_out<int> readData2;

    int registers[NUM_REGISTERS];

    
    void writeRegistrator() {
        if (RegWrite.read() == true) {
            registers[RegWrite.read()] = writeData.read();
        }
    }

    
    void readRegistrator() {
       readData1.write(registers[readRegister1.read()]);
        readData2.write(registers[readRegister2.read()]);
    }

   
    SC_CTOR(Registers) {
    
        for (int i = 0; i < NUM_REGISTERS; ++i) {
            registers[i] = 0;
        }

       
        SC_METHOD(writeRegistrator);
        sensitive << clk.pos();

        
        SC_METHOD(readRegistrator);
        sensitive << readRegister1 << readRegister2;
    }
};
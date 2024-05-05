#include <systemc.h>

#define NUM_REGISTERS 32
#define RAND_MAX 255

SC_MODULE(Registers) {
    sc_in<bool> clk; 
    sc_in<bool> RegWrite; 
    sc_in<sc_uint<6>>  writeRegister;
    sc_in<sc_int<32>> writeData; 
    sc_in<sc_uint<6>>  readRegister1; 
    sc_in<sc_uint<6>>  readRegister2;
    sc_out<sc_int<32>> readData1;
    sc_out<sc_int<32>> readData2;

    sc_int<32> registers[NUM_REGISTERS];

    
    void writeRegistrator() {
        if (RegWrite.read() == true) {
            registers[writeRegister.read()] = writeData.read();
        }
    }

    
    void readRegistrator() {
       readData1.write(registers[readRegister1.read()]);
        readData2.write(registers[readRegister2.read()]);
    }

   
    SC_CTOR(Registers) {
    
        for (sc_uint<6> i = 0; i < NUM_REGISTERS; ++i) {
          
            registers[i] = rand();
        }

       
        SC_METHOD(writeRegistrator);
        sensitive << clk.value_changed();

        
        SC_METHOD(readRegistrator);
        sensitive << readRegister1 << readRegister2;
    }
};
#include <systemc.h>

#define NUM_REGISTERS 32

SC_MODULE(Registers)
{
    sc_in<bool> clk;
    sc_in<bool> RegWrite;
    sc_in<bool> enable;
    sc_in<sc_uint<4>> opcode;
    sc_in<sc_uint<6>> destReg;
    sc_in<sc_uint<6>> writeRegister;
    sc_in<sc_int<32>> writeData;
    sc_in<sc_uint<6>> readRegister1;
    sc_in<sc_uint<6>> readRegister2;
    sc_in<sc_int<16>> immediate;
    sc_out<sc_int<32>> readData1;
    sc_out<sc_int<32>> readData2;
    sc_out<sc_int<32>> writeDataOut;
    sc_int<32> Intern_immediate;
    sc_int<32> registers[NUM_REGISTERS];
    sc_int<32> readData1_intern, readData2_intern;
    
    void writeRegistrator()
    {   cout << "writeRegistrator" << endl;
        if (enable.read())
        {

            if (RegWrite.read() == true)
            {
                registers[writeRegister.read()] = writeData.read();
            }
        }
    }

    void readRegistrator()
    {   cout << "readRegistrator" << endl;
        if (enable.read())
        {
            if (opcode.read() == 0b0111)
            {
                readData1.write(registers[readRegister1.read()]);
                Intern_immediate = immediate.read();
                readData2.write(Intern_immediate);
            }
            else if(opcode.read() == 0b1001){
                
              readData1_intern = readRegister1.read();
                Intern_immediate = immediate.read();
                readData1.write(readData1_intern);
                readData2.write(Intern_immediate);
            }
            else if(opcode.read() == 0b1010){
                readData1_intern = readRegister1.read();
                Intern_immediate = immediate.read();
                readData1.write(readData1_intern);
                readData2.write(Intern_immediate);
                writeDataOut.write(registers[destReg.read()]);
                
            }
            else
            {
                readData1.write(registers[readRegister1.read()]);
                readData2.write(registers[readRegister2.read()]);
            }
        }
        cout << "-----------------------------------------------------------------------"<< endl;
        cout << "Registers" << endl;
        cout << "clk: " << clk.read() << endl;
        cout << "RegWrite: " << RegWrite.read() << endl;
        cout << "enable: " << enable.read() << endl;
        cout << "opcode: " << opcode.read() << endl;
        cout << "destReg: " << destReg.read() << endl;
        cout << "writeRegister: " << writeRegister.read() << endl;
        cout << "writeData: " << writeData.read() << endl;
        cout << "readRegister1: " << readRegister1.read() << endl;
        cout << "readRegister2: " << readRegister2.read() << endl;
        cout << "immediate: " << immediate.read() << endl;
        cout << "readData1: " << readData1.read() << endl;
        cout << "readData2: " << readData2.read() << endl;
        cout << "writeDataOut: " << writeDataOut.read() << endl;
                cout << "-----------------------------------------------------------------------"<< endl;
        for (sc_uint<6> i = 0; i < NUM_REGISTERS; ++i)
        {  
            cout << "registers[" << i << "]: " << registers[i] << endl;
        }
    }

    SC_CTOR(Registers)
    {
        for (sc_uint<6> i = 0; i < NUM_REGISTERS; ++i)
        {
            registers[i] = 0;
        }

        SC_METHOD(writeRegistrator);
        sensitive << clk.pos();
        
        SC_METHOD(readRegistrator);
        sensitive << readRegister1 << readRegister2 << writeRegister << writeData << RegWrite;
    }
};
#include <systemc.h>

SC_MODULE(BufferMEMWB) {

    sc_in<bool> RegWrite;
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_in<bool> memReg;
    sc_in<sc_uint<6>> opDestino;
    sc_in<sc_int<32>> dataAdress;
    sc_in<sc_int<32>> readData; 

    sc_out<bool> regWriteOutput;
    sc_out<sc_uint<6>> writeRegister;
    sc_out<bool> memRegOut;
    sc_out<sc_int<32>> readDataOutput;
    sc_out<sc_int<32>> dataAdressOutput;

    sc_uint<6> internoReadData;
    sc_int<32> internoDataAdress;
    sc_uint<32> internoOpDestino;

    SC_CTOR(BufferMEMWB) {

        SC_METHOD(readMemory);
        sensitive << clk.pos();
        async_reset_signal_is(reset, true);

    }

    void readMemory() {
        if (reset.read()) {
           writeRegister.write(0x00000000); 
        } else {
                internoDataAdress = dataAdress.read();
                internoOpDestino = opDestino.read();
                internoReadData = readData.read();
                writeRegister.write(internoOpDestino);
                regWriteOutput.write(RegWrite);
                memRegOut.write(memReg); 
                readDataOutput.write(readData);
                dataAdressOutput.write(dataAdress);
            }
        }
    };
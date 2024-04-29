#include <systemc.h>

SC_MODULE(BufferInIDEX) {
    sc_in<bool> clk;
    sc_in<int> ReadData1;
    sc_in<int> ReadData2;
    sc_in<bool> inM;
    sc_in<bool> inWB;
    sc_in<bool> inEX;
    sc_out<bool> outEX;
    sc_out<bool> outM;
    sc_out<bool> outWB;
    sc_out<int> outputData1;
     sc_out<int> outputData2; 
    int storedData1,storedData2;
    bool internalM, internalWB, internalEX;
        
    void bufferProcess() {
        while (true) {
            wait();
            internalM = inM.read();
            internalWB = inWB.read();
            internalEX = inEX.read();
            storedData1 = ReadData1.read();
            storedData2 = ReadData2.read();
            outputData1.write(storedData1);
            outputData2.write(storedData2);
        }
    }

    SC_CTOR(BufferInIDEX) {
       
        outputData1.initialize(0); 
        outputData2.initialize(0); 
        SC_THREAD(bufferProcess);
        sensitive << clk.pos()  << ReadData1 << ReadData2;
    }
};

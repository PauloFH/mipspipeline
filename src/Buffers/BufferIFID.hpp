#include <systemc.h>


SC_MODULE(BufferIFID) {
    sc_in<bool> clk;
    sc_in<int> inputData;
    sc_in<bool> enable;
    sc_out<int> outputData;
    int storedData;
    
    void bufferProcess() {
        while (true) {
            wait(); 
         if(enable.read()){
            storedData = inputData.read();
            outputData.write(storedData);
         }
        }
    }

    SC_CTOR(BufferIFID) {
        outputData.initialize(0);
        SC_THREAD(bufferProcess);
        sensitive << clk.pos();
    }
};

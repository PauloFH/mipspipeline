#include <systemc.h>

SC_MODULE(MuxDM) {
    sc_in<bool> clk;
    sc_in<bool> memReg; 
    sc_in<sc_int<32>> in0; 
    sc_in<sc_int<32>> in1; 
    sc_out<sc_int<32>> out; 

   sc_int<32> local_in1; 
    sc_int<32> local_in0;
    sc_int<32> local_out;
    // Add the missing sc_out port declaration for out

    void process() {
        
        if (memReg.read()) {
            cout << "in0" << endl;
            local_out = in0.read();
        } else {
            local_out = in1.read(); 
              cout << "in0" << endl;
        }
        out.write(local_out);
    cout << "MuxDM" << endl;
    cout << "memReg: " << memReg.read() << endl;
    cout << "in0: " << in0.read() << endl;
    cout << "in1: " << in1.read() << endl;
    cout << "out: " << local_out << endl;
    cout << "out: " << out.read() << endl;
    }

    SC_CTOR(MuxDM) {
        
        SC_METHOD(process);
        sensitive << clk.pos() << memReg << in0 << in1;
    }
};

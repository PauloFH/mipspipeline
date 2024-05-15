#include <systemc.h>

SC_MODULE(Mux) {
    sc_in<bool> pcSRC; 
    sc_in<sc_uint<16>> in0; 
    sc_in<sc_uint<16>> in1; 
    sc_out<sc_uint<16>> out; 

    void process() {
              
        if (pcSRC.read() == 0) {
            out.write(in0.read()); 
        } else {
            out.write(in1.read());
            
        }
         cout << "-----------------------------------------------------------------------" << endl;
           cout << "Mux" << endl;
           pcSRC.read() == 0 ? cout << "pcSRC: 0" << endl : cout << "pcSRC: 1" << endl;
          cout << "-----------------------------------------------------------------------" << endl;
    }

    SC_CTOR(Mux) {
        SC_METHOD(process);
        sensitive << pcSRC;
    }
};

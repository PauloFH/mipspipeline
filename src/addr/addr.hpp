#include <systemc.h>

SC_MODULE(addr){
    sc_in <int> first_value,second_value;
    sc_out <int> output_value;
    
    void add(){
        output_value.write(first_value.read() + second_value.read());
    }

    SC_CTOR(addr){
        SC_METHOD(add);
        sensitive << first_value << second_value;
    }

};

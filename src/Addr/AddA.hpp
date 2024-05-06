#include <systemc.h>


SC_MODULE(AddA){
    sc_in <sc_uint<9>> first_value,second_value;
    sc_out<sc_uint<9>> output_value;
    
    void adda(){
        output_value.write(first_value.read() + second_value.read());
    }

    SC_CTOR(AddA){
        SC_METHOD(adda);
        sensitive << first_value << second_value;
    }

};

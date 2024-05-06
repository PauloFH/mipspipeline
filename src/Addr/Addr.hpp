#include <systemc.h>


SC_MODULE(Addr){
    sc_in <sc_uint<9>> first_value;
    sc_out<sc_uint<9>> output_value;
    
    void addr(){
        output_value.write(first_value.read() + 4 );
    }

    SC_CTOR(Addr){
        SC_METHOD(addr);
        sensitive << first_value;
    }

};

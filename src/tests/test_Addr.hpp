#include <systemc.h>
#include "Addr.hpp"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<16>> first_value;
    sc_signal<sc_uint<16>> output_value;

    Addr addr("addr");
    addr.first_value(first_value);
    addr.output_value(output_value);

    sc_start(0, SC_NS);

    // Set input value
    first_value = 10;

    sc_start(1, SC_NS);

    // Check output value
    assert(output_value.read() == 11);

    cout << "Test passed!" << endl;

    return 0;
}
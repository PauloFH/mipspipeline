#include <systemc.h>
#include "Alu.hpp"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_int<32>> first_value;
    sc_signal<sc_int<32>> second_value;
    sc_signal<sc_int<32>> output_value;
    sc_signal<bool> zero;

    Alu alu("alu");
    alu.clk(clk);
    alu.reset(reset);
    alu.opcode(opcode);
    alu.first_value(first_value);
    alu.second_value(second_value);
    alu.output_value(output_value);
    alu.zero(zero);

    sc_start(0, SC_NS);

    // Test zero_op
    opcode = Alu::zero_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 0);
    assert(zero.read() == false);

    // Test and_op
    opcode = Alu::and_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 0);
    assert(zero.read() == false);

    // Test or_op
    opcode = Alu::or_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 15);
    assert(zero.read() == false);

    // Test xor_op
    opcode = Alu::xor_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 15);
    assert(zero.read() == false);

    // Test not_op
    opcode = Alu::not_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == -11);
    assert(zero.read() == false);

    // Test slt_op
    opcode = Alu::slt_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 5);
    assert(zero.read() == false);

    // Test cmp_op
    opcode = Alu::cmp_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 5);
    assert(zero.read() == false);

    // Test add_op
    opcode = Alu::add_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 15);
    assert(zero.read() == false);

    // Test addi_op
    opcode = Alu::addi_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 15);
    assert(zero.read() == false);

    // Test sub_op
    opcode = Alu::sub_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 5);
    assert(zero.read() == false);

    // Test lw_op
    opcode = Alu::lw_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 15);
    assert(zero.read() == false);

    // Test sw_op
    opcode = Alu::sw_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    assert(output_value.read() == 15);
    assert(zero.read() == false);

    // Test j_op
    opcode = Alu::j_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    // Add your assertions here

    // Test beq_op
    opcode = Alu::beq_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    // Add your assertions here

    // Test bne_op
    opcode = Alu::bne_op;
    first_value = 10;
    second_value = 5;
    reset = false;
    clk = true;
    sc_start(1, SC_NS);
    // Add your assertions here

    cout << "All tests passed!" << endl;

    return 0;
}
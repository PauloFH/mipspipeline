/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for SystemC course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 02 Nov. 2021
 * @brief Empty main program for SystemC
 *
 * @see https://github.com/fmuller-pns/systemc-vscode-project-template.git
 */

#include <systemc.h>
#include <alu.hpp>
int sc_main(int argc, char* argv[]) {
	sc_signal<sc_int<32>> first_value;
	sc_signal<sc_int<32>> second_value;
	sc_signal <sc_int<4>>opcode;
 	sc_signal <sc_int<32>>output_value;
    sc_signal <bool> zero, negative;
	alu alu("alu");
	alu.first_value(first_value);
	alu.second_value(second_value);
	alu.opcode(opcode);
	alu.output_value(output_value);
	alu.zero(zero);
	alu.negative(negative);

	first_value = 1;
	second_value = 2;
	opcode = 1;

	sc_start();


	cout << "resultado da operaction com opcode: " << opcode << " é: " << output_value << endl;
	cout << "status de zero: " << zero << endl;
	cout << "status de negative: " << negative << endl;
	return 0;
}



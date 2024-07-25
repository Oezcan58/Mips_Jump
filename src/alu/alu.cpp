/*
 * alu.cpp
 *
 *  Created on: 24.04.2024
 *      Author: isd
 */

#include "alu.h"

void alu::behaviour() {
	sc_int<32> tmp_in_1 = in_1.read().to_int();
	sc_int<32> tmp_in_2 = in_2.read().to_int();
	if(alu_control_fuct.read() == add) {
		alu_result.write(static_cast<sc_lv<32> >(tmp_in_1 + tmp_in_2));
	}
	else if(alu_control_fuct.read() == substract ||
			alu_control_fuct.read() == substract_not_equal) {
		alu_result.write(static_cast<sc_lv<32> >(tmp_in_1 - tmp_in_2));
	}
	else if(alu_control_fuct.read() == and_op) {
		alu_result.write(in_1.read() & in_2.read());
	}
	else if(alu_control_fuct.read() == or_op) {
		alu_result.write(in_1.read() | in_2.read());
	}
	else if(alu_control_fuct.read() == set_on_less_than) {
		if (tmp_in_1 < tmp_in_2) {
			alu_result.write("00000000000000000000000000000001");
		}
		else {
			alu_result.write("00000000000000000000000000000000");
		}
	}
	zero_behaviour();
}

void alu::zero_behaviour() {
	if(in_1.read() != in_2.read() && alu_control_fuct.read() == substract_not_equal) {
		zero.write(SC_LOGIC_1);
	}
	else if(in_1.read() == in_2.read() && alu_control_fuct.read() == substract_not_equal) {
		zero.write(SC_LOGIC_0);
	}
	else if(in_1.read() == in_2.read()) {
		zero.write(SC_LOGIC_1);
	}
	else {
		zero.write(SC_LOGIC_0);
	}
}

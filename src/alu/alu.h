/*
 * alu.h
 *
 *  Created on: 24.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef ALU_ALU_H_
#define ALU_ALU_H_

SC_MODULE(alu) {
	sc_in<sc_lv<32> > in_1;
	sc_in<sc_lv<32> > in_2;
	sc_in<sc_lv<4> > alu_control_fuct;
	sc_out<sc_logic> zero;
	sc_out<sc_lv<32> > alu_result;

	const sc_lv<4> and_op = "0000";
	const sc_lv<4> or_op = "0001";
	const sc_lv<4> add = "0010";
	const sc_lv<4> substract_not_equal = "0011";
	const sc_lv<4> substract = "0110";
	const sc_lv<4> set_on_less_than = "0111";

	void behaviour();
	void zero_behaviour();

	SC_CTOR(alu) {
		SC_METHOD(behaviour);
		sensitive << in_1 << in_2 << alu_control_fuct;
	}
};

#endif /* ALU_ALU_H_ */

/*
 * alu_control.h
 *
 *  Created on: 24.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef ALU_CONTROL_ALU_CONTROL_H_
#define ALU_CONTROL_ALU_CONTROL_H_

SC_MODULE(alu_control) {
	sc_in<sc_lv<6> > funct;
	sc_in<sc_lv<2> > alu_op;
	sc_out<sc_lv<4> > alu_control_fuct;

	const sc_lv<4> and_op = "0000";
	const sc_lv<4> or_op = "0001";
	const sc_lv<4> add = "0010";
	const sc_lv<4> substract_not_equal = "0011";
	const sc_lv<4> substract = "0110";
	const sc_lv<4> set_on_less_than = "0111";

	void behaviour() {
		if(alu_op.read() == "00" || (alu_op.read() == "10" && funct.read() == "100000")) {
			alu_control_fuct.write(add);
		}
		else if(alu_op.read() == "01" || (alu_op.read() == "10" && funct.read() == "100010")) {
			alu_control_fuct.write(substract);
		}
		else if(alu_op.read() == "11") {
			alu_control_fuct.write(substract_not_equal);
		}
		else if(alu_op.read() == "10" && funct.read() == "100100") {
			alu_control_fuct.write(and_op);
		}
		else if(alu_op.read() == "10" && funct.read() == "100101") {
			alu_control_fuct.write(or_op);
		}
		else if(alu_op.read() == "10" && funct.read() == "101010") {
			alu_control_fuct.write(set_on_less_than);
		}
		else {
			alu_control_fuct.write("0000");
		}
	}

	SC_CTOR(alu_control) {
		SC_METHOD(behaviour);
		sensitive << funct << alu_op;
	}
};

#endif /* ALU_CONTROL_ALU_CONTROL_H_ */

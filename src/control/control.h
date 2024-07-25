/*
 * control.h
 *
 *  Created on: 24.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

SC_MODULE(control) {
	sc_in<sc_lv<6> > opcode;
	sc_out<sc_logic> reg_dest;
	sc_out<sc_logic> jump;
	sc_out<sc_logic> branch;
	sc_out<sc_logic> mem_read;
	sc_out<sc_logic> mem_to_reg;
	sc_out<sc_logic> mem_write;
	sc_out<sc_logic> alu_src;
	sc_out<sc_logic> reg_write;
	sc_out<sc_lv<2> > alu_op;

	const sc_lv<6> rtypes = "000000";
	const sc_lv<6> addi = "001000";
	const sc_lv<6> beq = "000100";
	const sc_lv<6> bne = "000101";
	const sc_lv<6> jmp = "000010";
	const sc_lv<6> lw = "100011";
	const sc_lv<6> sw = "101011";

	const int c_rtypes = rtypes.to_int();
	const int c_addi = addi.to_int();
	const int c_beq = beq.to_int();
	const int c_bne = bne.to_int();
	const int c_jmp = jmp.to_int();
	const int c_lw = lw.to_int();
	const int c_sw = sw.to_int();

	void behaviour();

	SC_CTOR(control) {
		SC_METHOD(behaviour);
		sensitive << opcode;
	}
};

#endif /* CONTROL_CONTROL_H_ */

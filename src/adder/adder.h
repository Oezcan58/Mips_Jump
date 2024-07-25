/*
 * adder.h
 *
 *  Created on: 23.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef ADDER_ADDER_H_
#define ADDER_ADDER_H_

SC_MODULE(adder) {
	sc_in<sc_lv<32> > x;
	sc_in<sc_lv<32> > y;
	sc_out<sc_lv<32> > z;

	void behaviour() {
		sc_lv<32> tmp_z;
		sc_logic carry = SC_LOGIC_0;
		for(int i = 0; i < 32; ++i) {
			tmp_z[i] = (x.read()[i] ^ y.read()[i]) ^ carry;
			carry = (x.read()[i] & y.read()[i]) | (x.read()[i] & carry) | (y.read()[i] & carry);
		}
		z.write(tmp_z);
	}

	SC_CTOR(adder) {
		SC_METHOD(behaviour);
		sensitive << x << y;
	}
};

#endif /* ADDER_ADDER_H_ */

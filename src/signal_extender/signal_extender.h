/*
 * signal_extender.h
 *
 *  Created on: 23.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef SIGNAL_EXTENDER_SIGNAL_EXTENDER_H_
#define SIGNAL_EXTENDER_SIGNAL_EXTENDER_H_

SC_MODULE(signal_extender) {
	sc_in<sc_lv<16> > x;
	sc_out<sc_lv<32> > y;

	void behaviour() {
		sc_lv<32> tmp_out;
		for(int i = 16; i < 32; ++i) {
			tmp_out[i] = x.read()[15];
		}
		for(int i = 0; i < 16; ++i) {
			tmp_out[i] = x.read()[i];
		}
		y.write(tmp_out);
	}

	SC_CTOR(signal_extender) {
		SC_METHOD(behaviour);
		sensitive << x;
	}
};

#endif /* SIGNAL_EXTENDER_SIGNAL_EXTENDER_H_ */

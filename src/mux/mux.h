/*
 * mux.h
 *
 *  Created on: 18.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef MUX_H_
#define MUX_H_

template <int WIDTH>
SC_MODULE(mux) {
	sc_in<sc_lv<WIDTH> > in0;
	sc_in<sc_lv<WIDTH> > in1;
	sc_in<sc_logic> select;
	sc_out<sc_lv<WIDTH> > out;

	void behaviour() {
		if(select.read() == 1) {
			out.write(in1.read());
		}
		else {
			out.write(in0.read());
		}
	}

	SC_CTOR(mux) {
		SC_METHOD(behaviour);
		sensitive << in0 << in1 << select;
	}
};

#endif /* MUX_H_ */

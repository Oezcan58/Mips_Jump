/*
 * program_counter.h
 *
 *  Created on: 19.04.2024
 *      Author: isd
 */

#ifndef PROGRAM_COUNTER_PROGRAM_COUNTER_H_
#define PROGRAM_COUNTER_PROGRAM_COUNTER_H_

#include "systemc.h"

SC_MODULE(program_counter) {
	sc_in_clk clk;
	sc_in<sc_lv<32> > address_to_load;
	sc_out<sc_lv<32> > current_address;

	sc_lv<32> address = sc_lv<32>(SC_LOGIC_0);

	void behaviour_default() {
		current_address.write(address);
	}

	void behaviour_clked() {
		while(true) {
			wait();
			address = address_to_load.read();
		}
	}

	SC_CTOR(program_counter) {
		SC_METHOD(behaviour_default);
		sensitive << clk;
		SC_CTHREAD(behaviour_clked, clk.pos());
	}
};

#endif /* PROGRAM_COUNTER_PROGRAM_COUNTER_H_ */

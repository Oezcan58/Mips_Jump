/*
 * data_memory.h
 *
 *  Created on: 25.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef DATA_MEMORY_DATA_MEMORY_H_
#define DATA_MEMORY_DATA_MEMORY_H_

SC_MODULE(data_memory) {
	sc_in<sc_lv<32> > address;
	sc_in<sc_lv<32> > write_data;
	sc_in<sc_logic> mem_write;
	sc_in<sc_logic> mem_read;
	sc_in_clk clk;
	sc_out<sc_lv<32> > read_data;

	sc_lv<32> data_mem[32]= {
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",//mem 1
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",//mem 10
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",//mem 20
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",
				"00000000000000000000000000000000",//mem 30
				"00000000000000000000000000000000",
		};

	void behaviour_default() {
		if(mem_read.read() == SC_LOGIC_1) {
			int addr = ("0", address.read().range(6, 2)).to_int();
			read_data.write(data_mem[addr]);
		}
		else {
			sc_lv<32> zero (SC_LOGIC_0);
			read_data.write(zero);
		}
	}

	void behaviour_clked() {
		while(true) {
			wait();
			if(mem_write.read() == SC_LOGIC_1) {
				int addr = ("0", address.read().range(6, 2)).to_int();
				data_mem[addr] = write_data.read();
			}
		}
	}

	SC_CTOR(data_memory) {
		for(int i = 0; i < 32; ++i) {
			data_mem[i] = sc_lv<32>(SC_LOGIC_0);
		}
		SC_METHOD(behaviour_default);
		sensitive << address << write_data << clk << mem_write << mem_read;
		SC_CTHREAD(behaviour_clked, clk.pos());
	}
};

#endif /* DATA_MEMORY_DATA_MEMORY_H_ */

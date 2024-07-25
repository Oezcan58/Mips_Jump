/*
 * mips.h
 *
 *  Created on: 26.04.2024
 *      Author: isd
 */

#include "systemc.h"
#include "adder/adder.h"
#include "alu/alu.h"
#include "alu_control/alu_control.h"
#include "control/control.h"
#include "data_memory/data_memory.h"
#include "instruction_memory/instruction_memory.h"
#include "mux/mux.h"
#include "program_counter/program_counter.h"
#include "registers/registers.h"
#include "shifter/shifter.h"
#include "signal_extender/signal_extender.h"

#ifndef MIPS_H_
#define MIPS_H_

SC_MODULE(mips) {
	sc_in_clk clk;
	sc_signal<sc_lv<32> > instr_address;
	sc_signal<sc_lv<32> > next_address;
	sc_signal<sc_lv<32> > instruction;
	sc_signal<sc_lv<32> > read_data_1;
	sc_signal<sc_lv<32> > read_data_2;
	sc_signal<sc_lv<32> > write_data;
	sc_signal<sc_lv<32> > extended_immediate;
	sc_signal<sc_lv<32> > shifted_immediate;
	sc_signal<sc_lv<32> > alu_in_2;
	sc_signal<sc_lv<32> > alu_result;
	sc_signal<sc_lv<32> > last_instr_address;
	sc_signal<sc_lv<32> > incremented_address;
	sc_signal<sc_lv<32> > add2_result;
	sc_signal<sc_lv<32> > mux4_result;
	sc_signal<sc_lv<32> > concatenated_pc_and_jump_address;
	sc_signal<sc_lv<32> > mem_read_data;
	sc_signal<sc_lv<28> > shifted_jump_address;
	sc_signal<sc_lv<26> > jump_address;
	sc_signal<sc_lv<16> > immediate;
	sc_signal<sc_lv<6> > opcode;
	sc_signal<sc_lv<6> > funct;
	sc_signal<sc_lv<5> > rs;
	sc_signal<sc_lv<5> > rt;
	sc_signal<sc_lv<5> > rd;
	sc_signal<sc_lv<5> > shampt;
	sc_signal<sc_lv<5> > write_reg;
	sc_signal<sc_lv<4> > alu_control_fuct;
	sc_signal<sc_logic>  reg_dest;
	sc_signal<sc_logic>  jump;
	sc_signal<sc_logic>  branch;
	sc_signal<sc_logic>  mem_read;
	sc_signal<sc_logic>  mem_to_reg;
	sc_signal<sc_logic>  mem_write;
	sc_signal<sc_logic>  alu_src;
	sc_signal<sc_logic>  reg_write;
	sc_signal<sc_logic>  alu_zero;
	sc_signal<sc_logic>  branch_and_alu_zero;
	sc_signal<sc_lv<2> > alu_op;
	sc_signal<sc_lv<32> > add1_y_const_input;

	typedef enum state
	{
		loading = 0,
		running = 1,
		done = 2
	} state;
	sc_signal<state> s;

	//The clock for the other components; starts when the state is ready
	sc_signal<bool> en;

	program_counter* prog_count;
	instruction_memory* im;
	control* control1;
	mux<5>* mux1;
	registers* reg;
	alu_control* alu_cntrl;
	signal_extender* sgn_ext;
	mux<32>* mux2;
	alu* alu1;
	mux<32>* mux3;
	shifter<32, 32, 2>* shift1;
	adder* add1;
	mux<32>* mux4;
	adder* add2;
	shifter<26, 28, 2>* shift2;
	mux<32>* mux5;
	data_memory* mem;

	void behaviour() {
		opcode.write(instruction.read().range(31, 26));
		rs.write(instruction.read().range(25, 21));
		rt.write(instruction.read().range(20, 16));
		rd.write(instruction.read().range(15, 11));
		shampt.write(instruction.read().range(10, 6));
		funct.write(instruction.read().range(5, 0));
		immediate.write(instruction.read().range(15, 0));
		jump_address.write(instruction.read().range(25, 0));
		branch_and_alu_zero.write(branch.read() & alu_zero.read());
		concatenated_pc_and_jump_address.write((incremented_address.read().range(31, 28), shifted_jump_address.read()));
	}

	void behaviour_management() {
		while(true) {
			wait();
			if(s.read() == loading) {
				s.write(running);
			}
			else if(s.read() == running) {
				if(instr_address.read().to_int() > last_instr_address.read().to_int()) {
					s.write(done);
				}
			}
		}
	}

	void behaviour_gated_clock() {
		if(s.read() == running) {
			en = clk;
		}
		else {
			en = false;
		}
	}

	SC_CTOR(mips) {
		en = false;
		s = loading;
		add1_y_const_input = sc_lv<32>("00000000000000000000000000000100");
		read_data_1 = sc_lv<32>(SC_LOGIC_0);
		read_data_2 = sc_lv<32>(SC_LOGIC_0);
		write_data = sc_lv<32>(SC_LOGIC_0);
		extended_immediate = sc_lv<32>(SC_LOGIC_0);
		shifted_immediate = sc_lv<32>(SC_LOGIC_0);
		alu_in_2 = sc_lv<32>(SC_LOGIC_0);
		alu_result = sc_lv<32>(SC_LOGIC_0);
		last_instr_address = sc_lv<32>(SC_LOGIC_0);
		incremented_address = sc_lv<32>(SC_LOGIC_0);
		add2_result = sc_lv<32>(SC_LOGIC_0);
		mux4_result = sc_lv<32>(SC_LOGIC_0);
		concatenated_pc_and_jump_address = sc_lv<32>(SC_LOGIC_0);
		mem_read_data = sc_lv<32>(SC_LOGIC_0);
		reg_dest = SC_LOGIC_0;
		jump = SC_LOGIC_0;
		branch = SC_LOGIC_0;
		mem_read = SC_LOGIC_0;
		mem_to_reg = SC_LOGIC_0;
		mem_write = SC_LOGIC_0;
		alu_src = SC_LOGIC_0;
		reg_write = SC_LOGIC_0;
		alu_zero = SC_LOGIC_0;
		branch_and_alu_zero = SC_LOGIC_0;

		prog_count = new program_counter("PROG_COUNT");
		prog_count->clk(en);
		prog_count->address_to_load(next_address);
		prog_count->current_address(instr_address);

		im = new instruction_memory("IM");
		im->read_address(instr_address);
		im->instruction(instruction);
		im->last_instr_address(last_instr_address);

		control1 = new control("CONTROL1");
		control1->opcode(opcode);
		control1->reg_dest(reg_dest);
		control1->jump(jump);
		control1->branch(branch);
		control1->mem_read(mem_read);
		control1->mem_to_reg(mem_to_reg);
		control1->mem_write(mem_write);
		control1->alu_src(alu_src);
		control1->reg_write(reg_write);
		control1->alu_op(alu_op);

		mux1 = new mux<5>("MUX1");
		mux1->in0(rt);
		mux1->in1(rd);
		mux1->select(reg_dest);
		mux1->out(write_reg);

		reg = new registers("REG");
		reg->clk(en);
		reg->reg_write(reg_write);
		reg->read_reg_1(rs);
		reg->read_reg_2(rt);
		reg->write_reg(write_reg);
		reg->write_data(write_data);
		reg->read_data_1(read_data_1);
		reg->read_data_2(read_data_2);

		alu_cntrl = new alu_control("ALU_CNTRL");
		alu_cntrl->funct(funct);
		alu_cntrl->alu_op(alu_op);
		alu_cntrl->alu_control_fuct(alu_control_fuct);

		sgn_ext = new signal_extender("SGN_EXT");
		sgn_ext->x(immediate);
		sgn_ext->y(extended_immediate);

		mux2 = new mux<32>("MUX2");
		mux2->in0(read_data_2);
		mux2->in1(extended_immediate);
		mux2->select(alu_src);
		mux2->out(alu_in_2);

		alu1 = new alu("ALU1");
		alu1->in_1(read_data_1);
		alu1->in_2(alu_in_2);
		alu1->alu_control_fuct(alu_control_fuct);
		alu1->zero(alu_zero);
		alu1->alu_result(alu_result);

		mux3 = new mux<32>("MUX3");
		mux3->in0(alu_result);
		mux3->in1(mem_read_data);
		mux3->select(mem_to_reg);
		mux3->out(write_data);

		shift1 = new shifter<32, 32, 2>("SHIFT1");
		shift1->x(extended_immediate);
		shift1->y(shifted_immediate);

		add1 = new adder("ADD1");
		add1->x(instr_address);
		add1->y(add1_y_const_input);
		add1->z(incremented_address);

		mux4 = new mux<32>("MUX4");
		mux4->in0(incremented_address);
		mux4->in1(add2_result);
		mux4->select(branch_and_alu_zero);
		mux4->out(mux4_result);

		add2 = new adder("ADD2");
		add2->x(incremented_address);
		add2->y(shifted_immediate);
		add2->z(add2_result);

		shift2 = new shifter<26, 28, 2>("SHIFT2");
		shift2->x(jump_address);
		shift2->y(shifted_jump_address);

		mux5 = new mux<32>("MUX5");
		mux5->in0(mux4_result);
		mux5->in1(concatenated_pc_and_jump_address);
		mux5->select(jump);
		mux5->out(next_address);

		mem = new data_memory("MEM");
		mem->address(alu_result);
		mem->write_data(read_data_2);
		mem->mem_write(mem_write);
		mem->mem_read(mem_read);
		mem->clk(en);
		mem->read_data(mem_read_data);

		SC_METHOD(behaviour);
		sensitive << instruction << branch << alu_zero << incremented_address << shifted_jump_address;
		SC_METHOD(behaviour_gated_clock);
		sensitive << s << clk;
		SC_CTHREAD(behaviour_management, clk.pos());
	}

	~mips() {
		delete prog_count;
		delete im;
		delete control1;
		delete mux1;
		delete reg;
		delete alu_cntrl;
		delete sgn_ext;
		delete mux2;
		delete alu1;
		delete mux3;
		delete shift1;
		delete add1;
		delete mux4;
		delete add2;
		delete shift2;
		delete mux5;
		delete mem;
	}
};

#endif /* MIPS_H_ */

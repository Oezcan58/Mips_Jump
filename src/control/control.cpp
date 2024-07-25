/*
 * control.cpp
 *
 *  Created on: 24.04.2024
 *      Author: isd
 */

#include "control.h"

void control::behaviour() {
	int c_opcode = opcode.read().to_int();
	if(c_opcode == c_rtypes) {
		reg_dest.write(SC_LOGIC_1);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_0);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_0);
		reg_write.write(SC_LOGIC_1);
		alu_op.write("10");
	}
	else if(c_opcode == c_addi) {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_0);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_1);
		reg_write.write(SC_LOGIC_1);
		alu_op.write("00");
	}
	else if(c_opcode == c_beq) {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_1);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_0);
		reg_write.write(SC_LOGIC_0);
		alu_op.write("01");
	}
	else if(c_opcode == c_bne) {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_1);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_0);
		reg_write.write(SC_LOGIC_0);
		alu_op.write("11");
	}
	else if(c_opcode == c_jmp) {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_1);
		branch.write(SC_LOGIC_0);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_0);
		reg_write.write(SC_LOGIC_0);
		alu_op.write("00");
	}
	else if(c_opcode == c_lw) {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_0);
		mem_read.write(SC_LOGIC_1);
		mem_to_reg.write(SC_LOGIC_1);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_1);
		reg_write.write(SC_LOGIC_1);
		alu_op.write("00");
	}
	else if(c_opcode == c_sw) {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_0);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_1);
		alu_src.write(SC_LOGIC_1);
		reg_write.write(SC_LOGIC_0);
		alu_op.write("00");
	}
	else {
		reg_dest.write(SC_LOGIC_0);
		jump.write(SC_LOGIC_0);
		branch.write(SC_LOGIC_0);
		mem_read.write(SC_LOGIC_0);
		mem_to_reg.write(SC_LOGIC_0);
		mem_write.write(SC_LOGIC_0);
		alu_src.write(SC_LOGIC_0);
		reg_write.write(SC_LOGIC_0);
		alu_op.write("00");
	}
}

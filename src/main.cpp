#include <stdio.h>


#include "systemc.h"
#include "clkgen.h"
#include "mips.h"
#include "instruction_memory/instruction_memory.h"


int sc_main(int argc, char *argv[])
{
  printf("Testbench start\n");
  // setup trace file with resolution of 1 ns
  sc_trace_file *trace_file = sc_create_vcd_trace_file("trace");
  trace_file->set_time_unit(1, SC_NS);

  sc_signal <bool> clk;
  sc_signal<sc_lv<32> > read_address;
  sc_signal<sc_lv<32> > instruction;
  sc_signal<sc_lv<32> > last_instr_address;

  clkgen clkgen("CLOCK");
  clkgen.clk(clk);

  mips mips("MIPS");
  mips.clk(clk);

  instruction_memory imen("INSTRUCTION_MEMORY");
  imen.read_address(read_address);
  imen.instruction(instruction);
  imen.last_instr_address(last_instr_address);

  sc_trace(trace_file, clk, "CLK");
  sc_trace(trace_file, read_address, "READ_ADDRESS");
  sc_trace(trace_file, instruction, "INSTRUCTION");
  sc_trace(trace_file, last_instr_address, "LAST_INSTR_ADDRESS");
  //check simulation time! 50 ms is much time to simulate!
  sc_start(10, SC_MS);

  read_address.write(sc_lv<32>("0000100000000000000000000010001"));//adress 17
  sc_start(10, SC_MS);

  read_address.write(sc_lv<32>("0000100000000000000000000010001"));//adress 26
  sc_start(10, SC_MS);

  read_address.write(sc_lv<32>("0000100000000000000000000010001"));//address 18
  sc_start(10, SC_MS);

  cout << "Exiting from reset at " << sc_time_stamp() << "\n";

  cout << "Finished at " << sc_time_stamp() << "\n";
  sc_close_vcd_trace_file(trace_file);
  return 0;
}

/*
 * clkgen.h
 *
 *  Created on: 29.04.2024
 *      Author: isd
 */

#include "systemc.h"

#ifndef CLKGEN_H_
#define CLKGEN_H_

SC_MODULE(clkgen)
{
  sc_out <bool> clk;

  SC_CTOR(clkgen)
  {
    SC_THREAD(behaviour);
  }

  void behaviour()
  {
    clk = false;
    while (1)
      {
    	wait(50, SC_NS);
    	clk = !clk.read();
      }
  }
};

#endif /* CLKGEN_H_ */

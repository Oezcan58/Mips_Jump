/*
 * shifter.h
 *
 *  Created on: 22.04.2024
 *      Author: isd
 */

#ifndef SHIFTER_SHIFTER_H_
#define SHIFTER_SHIFTER_H_

#include "systemc.h"

template <int N1, int N2, int K>
SC_MODULE(shifter) {
	sc_in<sc_lv<N1> > x;
	sc_out<sc_lv<N2> > y;

	const int distance = K;

	void behaviour() {
		sc_lv<N1> x_shifted = sc_lv<N1>(SC_LOGIC_0);
		for(int i = (N1 - K + 1); i >= K; --i) {
			x_shifted[i] = x.read()[i - K];
		}
		sc_lv<N2> y_tmp = 0;
		if(N1 > N2) {
			for(int i = 0; i < N2; ++i) {
				y_tmp[i] = x_shifted[i];
			}
		}
		else if(N2 > N1) {
			for(int i = 0; i < N1; ++i) {
				y_tmp[i] = x_shifted[i];
			}
			for(int i = N1; i < N2; ++i) {
				y_tmp[i] = x_shifted[N1 - 1];
			}
		}
		else {
			for(int i = 0; i < N2; ++i) {
				y_tmp[i] = x_shifted[i];
			}
		}
		y.write(y_tmp);
	}

	SC_CTOR(shifter) {
		SC_METHOD(behaviour);
		sensitive << x;
	}
};

#endif /* SHIFTER_SHIFTER_H_ */

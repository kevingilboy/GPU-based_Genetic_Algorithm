/*
 * Kevin Gilboy
 * Simulator
 */

#include <math.h>
#define RANDRULE (rand() % (FULL_SIZE + 1))

int simulate(char *state) {
	double error = 0;

	for (int init_condition_num = 0; init_condition_num < NUM_INITIAL_CONDITIONS; init_condition_num++) {
		initialize_state(state, init_condition_num);

		for (int trial = 0; trial < TRIALS; trial++) {
			for (int step = 0; step < STEPS; step++) {
				//Generate rule
				int r;
				do {
					r = RANDRULE;
				} while (state[r] == -1);

				run_rule(state, r);
			}
			error += calculate_error(state);
		}
	}

	int ceil_error = ceil(error);
	return ceil_error;
}

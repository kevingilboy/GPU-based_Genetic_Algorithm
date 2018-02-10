/*
 * Kevin Gilboy
 * Simulator
 */

#include <math.h>
#define RANDRULE (rand() % (FULL_SIZE + 1))

int simulate(char *state) {
	double error = 0;
	double cumulative_state[FULL_SIZE];

	for (int init_condition_num = 0; init_condition_num < NUM_INITIAL_CONDITIONS; init_condition_num++) {
		for (int trial = 0; trial < TRIALS; trial++) {
			initialize_state(state, init_condition_num);

			//Run the trial
			for (int step = 0; step < STEPS; step++) {
				//Generate rule
				int r;
				do {
					r = RANDRULE;
				} while (state[r] == -1);

				run_rule(state, r);
			}
			//Trial finished, add to cumulative state for all trials
			for (int i = 0; i < FULL_SIZE; i++) {
				//Should I check if state is -1 here? Shouldnt matter...
				cumulative_state[i] += state[i];
			}
		}

		//Calculate average of each protein across all trials
		for (int i = 0; i < FULL_SIZE; i++) {
			cumulative_state[i] /= TRIALS;
		}

		//Calculate error
		error += calculate_error(cumulative_state, init_condition_num);
	}

	int ceil_error = ceil(error);
	return ceil_error;
}

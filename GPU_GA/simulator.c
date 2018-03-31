/*
 * Kevin Gilboy
 * Simulator
 */

#include <math.h>
#define RANDRULE (rand() % (FULL_SIZE + 1))

void simulate(Individual *individual) {
	char *state = individual->addr;
	int error = 0;

	for (int init_condition_num = 0; init_condition_num < NUM_INITIAL_CONDITIONS; init_condition_num++) {
		float cumulative_state[FULL_SIZE] = { 0 };

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
			cumulative_state[i] /= (float) TRIALS;
		}

		//Calculate error
		error += calculate_error(cumulative_state, init_condition_num);
	}

	individual->error = error;
}

#ifdef GPU
#include <curand.h>
#include <curand_kernel.h>

__global__
void test(char* c) {
	for (int i = 0; i < FULL_SIZE; i++) {
		char x = c[i];
		if (x == 0) {
			char y = c[i];
		}
		else if (x == 1) {
			char y = c[i];
		}
		continue;
	}
	return;
}

__global__
void simulate_parallel(char *gpu_individuals, int *gpu_error, int pitch, unsigned int seed) {
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	char *state = (char*)((char*)gpu_individuals + index * pitch);
	//printf("%d\n", index);
	int error = 0;
	curandState_t rand;
	curand_init(seed, // the seed controls the sequence of random values that are produced 
		0, // the sequence number is only important with multiple cores 
		0, // the offset is how much extra we advance in the sequence for each call, can be 0 
		&rand);
	
	for (int init_condition_num = 0; init_condition_num < NUM_INITIAL_CONDITIONS; init_condition_num++) {
		float cumulative_state[FULL_SIZE] = { 0 };

		for (int trial = 0; trial < TRIALS; trial++) {
			//initialize_state(state, init_condition_num);
			for (int i = 0; i < FULL_SIZE; i++) {
				if (state[i] != -1) {
					state[i] = PROTEIN[i].init_val[init_condition_num];
				}
			}

			//Run the trial
			for (int step = 0; step < STEPS; step++) {
				//Generate rule
				int r;
				do {
					r = curand(&rand) % (FULL_SIZE + 1);
				} while (state[r] == -1);

				run_rule(state, r);
			}
			//Trial finished, add to cumulative state for all trials
			for (int i = 0; i < FULL_SIZE; i++) {
				//Should I check if state is -1 here? Shouldnt matter...
				cumulative_state[i] += state[i];
			}
			printf("%d: %d: %d\n\n", index, init_condition_num, trial);
		}

		//Calculate average of each protein across all trials
		for (int i = 0; i < FULL_SIZE; i++) {
			cumulative_state[i] /= (float)TRIALS;
			printf("%f ", cumulative_state[i]);
		}
		printf("\n");

		//Calculate error
		error += calculate_error(cumulative_state, init_condition_num);
	}
	
	gpu_error[index] = error;
}
#endif

/*
 * Kevin Gilboy
 * GPU-ready main kernel
 */

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "params.h"
#include "simulator.c"
#include "tcell.c"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Random number on range [min,max] inclusive
#define RANDGEN(min,max) (rand() % (max + 1 - min)) + min

//Function declarations
void initialize_population();
void pause();

//Globals
bool population[INIT_POPULATION_SIZE][FULL_SIZE];
int error[INIT_POPULATION_SIZE];
int population_size = INIT_POPULATION_SIZE;

int main()
{
	srand(time(NULL));

	initialize_population();

	for (int i = 0; i < population_size; i++) {
		error[i] = simulate(population[i]);
	}

	pause();
    return 0;
}

void initialize_population() {
	//Cycle through each individual
	for (int i = 0; i < population_size; i++) {
		//Add the reduced rules in since those are
		//present in every individual
		for (int j = 0; j < REDUCED_SIZE; j++) {
			population[i][j] = PROTEINS[j].init_val;
		}
		for (int j = REDUCED_SIZE; j < FULL_SIZE; j++) {
			population[i][j] = NULL;
		}

		//Select TARGET_SIZE unique rules on the range
		//[REDUCED_SIZE,FULL_SIZE) and initialize them
		for (int j = 0; j < TARGET_SIZE; j++) {
			//Select a unique rule on range [REDUCED_SIZE,FULL_SIZE)
			int rule;
			do {
				rule = RANDGEN(REDUCED_SIZE,FULL_SIZE-1);
			} while (population[i][rule] != NULL);

			//Initialize the rule in the individual
			population[i][rule] = PROTEINS[rule].init_val;
		}
	}
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}

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

/*
* MACROS
*/
//Random number on range [min,max] inclusive
#define RANDGEN(min,max) (rand() % (max + 1 - min)) + min

/*
* FUNCTION PROTOTYPES
*/
void initialize_population();
bool check_stopping_criteria(int[], int);
void pause();

int main()
{
	//Stores the individuals of the population and their respective states
	//State is set to null if the protein is not used
	bool population[INIT_POPULATION_SIZE][FULL_SIZE];

	//Stores the errors of each individual resulting from simulation
	int error[INIT_POPULATION_SIZE];

	//The length of the population is stored separately so that the
	//population can be cropped without creating a new population array
	int population_size = INIT_POPULATION_SIZE;

	int evolution = 0;

	srand(time(NULL));

	initialize_population(population, population_size);

	do {
		for (int i = 0; i < population_size; i++) {
			error[i] = simulate(population[i]);

			//TODO sort population by increasing error

			//Trim to top 20 individuals
			population_size > 20 ? 20 : population_size;

			//TODO GA stuff here
		}

		//Increment evolution counter
		evolution++;
	} while (check_stopping_criteria(error, population_size));

	printf("Completed in %d evolutions\n", evolution);

	pause();
    return 0;
}

void initialize_population(bool population[INIT_POPULATION_SIZE][FULL_SIZE], int population_size) {
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

bool check_stopping_criteria(int error[], int population_size) {
	for (int i = 0; i < population_size; i++) {
		//Return false on any nonzero error
		if (error[i] != 0) {
			return false;
		}
	}
	return true;
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
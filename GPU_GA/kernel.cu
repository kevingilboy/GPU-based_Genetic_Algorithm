/*
 * Kevin Gilboy
 * GPU-ready main kernel
 */

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "params.h"
#include "simulator.c"
#include "ga.c"

/*
* FUNCTION PROTOTYPES
*/
void pause();

int main()
{
	//Stores the individuals of the population and their respective states
	//State is set to null if the protein is not used
	bool population[INIT_POPULATION_SIZE][FULL_SIZE];

	//Stores the errors of each individual resulting from simulation
	int error[INIT_POPULATION_SIZE];

	int evolution = 0;

	srand(time(NULL));

	initialize_population(population);

	//Cycle through each individual
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
		error[i] = simulate(population[i]);
	}

	//Trim to top 20 individuals
	//TODO sort population by increasing error
	for (int keep_indices = 0; keep_indices < SURVIVORS; keep_indices++) {

	}

	do {
		//TODO GA stuff here
		modify(population);

		//Cycle through each individual
		for (int i = 0; i < SURVIVORS; i++) {
			error[i] = simulate(population[i]);			
		}

		//Increment evolution counter
		evolution++;
	} while (check_stopping_criteria(error, SURVIVORS));

	printf("Completed in %d evolutions\n", evolution);

	pause();
    return 0;
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
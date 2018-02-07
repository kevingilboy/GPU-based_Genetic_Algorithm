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

	//Create the initial population of size INIT_POPULATION_SIZE
	initialize_population((bool **)population, INIT_POPULATION_SIZE, FULL_SIZE, REDUCED_RULES, TARGET_RULES);

	//Cycle through each individual
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
		error[i] = simulate(population[i]);
	}

	//Select the top SURVIVORS individuals
	natural_selection((bool **)population, error, INIT_POPULATION_SIZE, FULL_SIZE, SURVIVORS);

	do {	
		//Duplicate SURVIVORS individuals to size TARGET_POPULATION_SIZE
		proliferate((bool **)population, SURVIVORS, FULL_SIZE, TARGET_POPULATION_SIZE);

		//Simulate each TARGET_POPULATION_SIZE individual
		for (int i = 0; i < TARGET_POPULATION_SIZE; i++) {
			error[i] = simulate(population[i]);			
		}

		//Select the top SURVIVORS individuals
		natural_selection((bool **)population, error, TARGET_POPULATION_SIZE, FULL_SIZE, SURVIVORS);

		//Increment evolution counter
		evolution++;

		//Loop if any of the SURVIVORS individuals have nonzero error
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
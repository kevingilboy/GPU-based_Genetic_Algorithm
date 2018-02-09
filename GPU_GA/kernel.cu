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

	//Stores the addr and errors of each individual resulting from simulation
	struct Individual individuals[INIT_POPULATION_SIZE];

	//Evolution counter
	int evolution = 0;

	srand(time(NULL));

	//Create the initial population of size INIT_POPULATION_SIZE
	initialize_population((bool **)population, INIT_POPULATION_SIZE, FULL_SIZE, REDUCED_RULES, TARGET_RULES);

	//Cycle through each individual
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
		individuals[i].addr = population[i]; //Store the address
		individuals[i].error = simulate(population[i]); //Store the error
	}

	//Select the top SURVIVORS individuals
	natural_selection(individuals, INIT_POPULATION_SIZE, FULL_SIZE, SURVIVORS);

	//At somepoint, if population becomes an array of mallocs, I should free population[MU:end]
	//However memory is not a major issue considering we only have a population of 300

	do {	
		//Duplicate SURVIVORS individuals to size TARGET_POPULATION_SIZE
		proliferate(individuals, SURVIVORS, FULL_SIZE, TARGET_POPULATION_SIZE);

		//Simulate each TARGET_POPULATION_SIZE individual
		for (int i = 0; i < TARGET_POPULATION_SIZE; i++) {
			individuals[i].error = simulate(population[i]);
		}

		//Select the top SURVIVORS individuals
		natural_selection(individuals, TARGET_POPULATION_SIZE, FULL_SIZE, SURVIVORS);

		//Increment evolution counter
		evolution++;

		//Loop if any of the SURVIVORS individuals have nonzero error
	} while (check_stopping_criteria(individuals, SURVIVORS));

	printf("Completed in %d evolutions\n", evolution);

	pause();
    return 0;
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
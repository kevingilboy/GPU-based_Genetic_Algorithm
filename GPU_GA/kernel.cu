/*
 * Kevin Gilboy
 * GPU-ready main kernel
 */

//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

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
	char population[INIT_POPULATION_SIZE][FULL_SIZE];

	//Stores the addr and errors of each individual resulting from simulation
	struct Individual individuals[INIT_POPULATION_SIZE];

	//Evolution counter
	int evolution = 0;

	srand(time(NULL));

	//Create the initial population of size INIT_POPULATION_SIZE
	DEBUG_PRINT(("E_%d: Initialization\n", evolution));
	initialize_population(population, INIT_POPULATION_SIZE);

	//Cycle through each individual
	DEBUG_PRINT(("E_%d: Simulation\n", evolution));
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
		individuals[i].addr = population[i]; //Store the address
		individuals[i].error = simulate(population[i]); //Store the error
	}

	//Select the top SURVIVORS individuals
	DEBUG_PRINT(("E_%d: Natural Selection\n\n", evolution));
	natural_selection(individuals, INIT_POPULATION_SIZE);

	//At somepoint, if population becomes an array of mallocs, I should free population[MU:end]
	//However memory is not a major issue considering we only have a population of 300

	do {	
		//Increment evolution counter
		evolution++;

		//Duplicate SURVIVORS individuals to size TARGET_POPULATION_SIZE
		DEBUG_PRINT(("E_%d: Proliferation\n", evolution));
		proliferate(individuals);

		//Simulate each TARGET_POPULATION_SIZE individual
		DEBUG_PRINT(("E_%d: Simulation\n", evolution));
		for (int i = 0; i < TARGET_POPULATION_SIZE; i++) {
			individuals[i].error = simulate(individuals[i].addr);
		}

		//Select the top SURVIVORS individuals
		DEBUG_PRINT(("E_%d: Natural Selection\n", evolution));
		natural_selection(individuals, TARGET_POPULATION_SIZE);

		#ifdef DEBUG
				int error = 0;
				for (int i = 0; i < SURVIVORS; i++) {
					for (int j = REDUCED_RULES; j < FULL_SIZE; j++) {
						if (individuals[i].addr[j] != -1) {
							printf("%s,", PROTEIN[j].name);
						}
					}
					printf("\n");

					error += individuals[i].error;
				}
				printf("E_%d: Total error of %d\n\n", evolution, error);
		#endif

		//Loop if any of the SURVIVORS individuals have nonzero error
	} while (!check_stopping_criteria(individuals));

	printf("Completed in %d evolutions\n", evolution);

	pause();
    return 0;
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
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
	#ifdef CALC_PROGRAM_RUNTIME
		time_t start_time = time(NULL);
		clock_t timer;
	#endif

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
	START_TIMER
	initialize_population(population, INIT_POPULATION_SIZE);
	END_TIMER

	//Cycle through each individual
	DEBUG_PRINT(("E_%d: Simulation\n", evolution));
	START_TIMER
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
		individuals[i].addr = population[i]; //Store the address
		individuals[i].error = simulate(population[i]); //Store the error
	}
	END_TIMER

	//Select the top SURVIVORS individuals
	DEBUG_PRINT(("E_%d: Natural Selection\n\n", evolution));
	START_TIMER
	natural_selection(individuals, INIT_POPULATION_SIZE);
	END_TIMER

	//At somepoint, if population becomes an array of mallocs, I should free population[MU:end]
	//However memory is not a major issue considering we only have a population of 300

	do {	
		//Increment evolution counter
		DEBUG_PRINT(("\n"));
		evolution++;

		//Duplicate SURVIVORS individuals to size TARGET_POPULATION_SIZE
		DEBUG_PRINT(("E_%d: Proliferation\n", evolution));
		START_TIMER
		proliferate(individuals);
		END_TIMER

		//Simulate each TARGET_POPULATION_SIZE individual
		DEBUG_PRINT(("E_%d: Simulation\n", evolution));
		START_TIMER
		for (int i = 0; i < TARGET_POPULATION_SIZE; i++) {
			individuals[i].error = simulate(individuals[i].addr);
		}
		END_TIMER

		//Select the top SURVIVORS individuals
		DEBUG_PRINT(("E_%d: Natural Selection\n", evolution));
		START_TIMER
		natural_selection(individuals, TARGET_POPULATION_SIZE);
		END_TIMER

		//Loop if any of the SURVIVORS individuals have nonzero error
	} while (!check_stopping_criteria(individuals));

	printf("Completed in %d evolutions\n", evolution);

	#ifdef CALC_PROGRAM_RUNTIME
		time_t end_time = time(NULL);
		printf("Runtime: %d sec\n\n", end_time - start_time);
	#endif

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

	pause();
    return 0;
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
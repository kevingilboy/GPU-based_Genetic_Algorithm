
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
#include "tcell.c"
#include "simulator.c"
#include "ga.c"

/*
* MACROS
*/
//Random number on range [min,max] inclusive
#define RANDGEN(min,max) (rand() % (max + 1 - min)) + min

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

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
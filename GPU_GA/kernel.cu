/*
 * Kevin Gilboy
 * GPU-ready main kernel
 */

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "params.h"
#include "ga.c"
#include "simulator.c"

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
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
		individuals[i].addr = population[i]; //Store the address
	}
	END_TIMER

	//Cycle through each individual
	DEBUG_PRINT(("E_%d: Simulation\n", evolution));
	START_TIMER

#ifdef GPU
		cudaError_t cudaStatus;
		char *gpu_individuals;
		float *cum_state;
		size_t pitch, pitch2;

		// Choose which GPU to run on, change this on a multi-GPU system.
		cudaStatus = cudaSetDevice(0);
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
			pause();
			exit(-1);
		}

		cudaMallocPitch((void**) &gpu_individuals, &pitch, FULL_SIZE * sizeof(char), INIT_POPULATION_SIZE);
		cudaMallocPitch((void**)&cum_state, &pitch2, FULL_SIZE * sizeof(float), INIT_POPULATION_SIZE);
		cudaMemcpy2D(gpu_individuals, pitch, population, FULL_SIZE * sizeof(char), FULL_SIZE * sizeof(char), INIT_POPULATION_SIZE, cudaMemcpyHostToDevice);

		int *gpu_error;
		cudaMalloc((void**)&gpu_error, sizeof(int)*INIT_POPULATION_SIZE);

		int threads_per_block = 128;
		int blocks_per_grid = 300*200 / threads_per_block;
		simulate_parallel<<<blocks_per_grid, threads_per_block>>>(gpu_individuals, cum_state, pitch, pitch2, time(NULL)); //Store the error

		// Check for any errors launching the kernel
		cudaStatus = cudaGetLastError();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
			pause();
			exit(-1);
		}

		// cudaDeviceSynchronize waits for the kernel to finish, and returns
		// any errors encountered during the launch.
		//cudaStatus = cudaDeviceSynchronize();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching simulate_parallel!\n", cudaStatus);
			pause();
			exit(-1);
		}

		//for (int r = 0; r < INIT_POPULATION_SIZE; ++r) {
			//int *row = (int*)((float*)cum_state + r * pitch2);
			float hostPtr[300][FULL_SIZE];
			//cudaMemcpy(&e, row, sizeof(int) * INIT_POPULATION_SIZE, cudaMemcpyDeviceToHost);
			cudaMemcpy2D(hostPtr, FULL_SIZE * sizeof(float), cum_state, pitch, FULL_SIZE * sizeof(float), 300, cudaMemcpyDeviceToHost);
			//printf("%d\n", e);
		//}
		printf("Done");
		pause();
		exit(0);
	#else
		for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
			simulate(&individuals[i]); //Store the error
		}
	#endif
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
		#ifdef GPU
			char *gpu_population;
			cudaMalloc((void**)&gpu_population, sizeof(char) * 20 * FULL_SIZE);
			cudaMemcpy(&gpu_population, &population, sizeof(char) * 20 * FULL_SIZE, cudaMemcpyHostToDevice);

			Individual *gpu_individuals;
			cudaMalloc((void**)&gpu_individuals, sizeof(Individual) * 20);
			for (int i = 0; i < 20; i++) {
				*gpu_individuals[i].addr = gpu_population[i];
			}

			//simulate_parallel<<<1, 1 >>>(&gpu_individuals, time(NULL)); //Store the error
		#else
			for (int i = 0; i < TARGET_POPULATION_SIZE; i++) {
				simulate(&individuals[i]); //Store the error
			}
		#endif
		END_TIMER

		//Select the top SURVIVORS individuals
		DEBUG_PRINT(("E_%d: Natural Selection\n", evolution));
		START_TIMER
		natural_selection(individuals, TARGET_POPULATION_SIZE);
		END_TIMER
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
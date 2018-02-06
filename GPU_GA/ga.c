//Random number on range [min,max] inclusive
#define RANDGEN(min,max) (rand() % (max + 1 - min)) + min

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
				rule = RANDGEN(REDUCED_SIZE, FULL_SIZE - 1);
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
//Random number on range [min,max] inclusive
#define RANDINT(min,max) (rand() % (max + 1 - min)) + min

void initialize_population(bool population[INIT_POPULATION_SIZE][FULL_SIZE]) {
	//Cycle through each individual
	for (int i = 0; i < INIT_POPULATION_SIZE; i++) {
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
				rule = RANDINT(REDUCED_SIZE, FULL_SIZE - 1);
			} while (population[i][rule] != NULL);

			//Initialize the rule in the individual
			population[i][rule] = PROTEINS[rule].init_val;
		}
	}
}

void modify(bool population[SURVIVORS][FULL_SIZE]) {
	double r;

	//Cycle through each individual
	for (int i = 0; i < SURVIVORS; i++) {
		//Decide to mutate, mate, reproduce
		r = (double)rand() / RAND_MAX;
		if (0 < r && r < P_MUTATE) {
			//MUTATE!
		}
		else if (P_MUTATE < r && r < P_MATE + P_MUTATE) {
			//MATE!
		}
	}
}

void mutate(bool individual[FULL_SIZE]) {

}

void mate(bool individual_1[FULL_SIZE], bool individual_2[FULL_SIZE]) {

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
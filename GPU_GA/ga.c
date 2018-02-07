//Random number on range [min,max] inclusive
#define RANDINT(min,max) (rand() % (max + 1 - min)) + min

void initialize_population(bool** population, int population_size, int individual_length, int reduced_num_rules, int target_num_rules) {
	//Cycle through each individual
	for (int i = 0; i < population_size; i++) {
		//Add the reduced rules in since those are
		//present in every individual. Make the rest NULL
		for (int j = 0; j < reduced_num_rules; j++) {
			population[i][j] = PROTEINS[j].init_val;
		}
		for (int j = reduced_num_rules; j < individual_length; j++) {
			population[i][j] = NULL;
		}

		//Select TARGET_SIZE unique rules on the range
		//[REDUCED_SIZE,FULL_SIZE) and initialize them
		for (int j = 0; j < target_num_rules - reduced_num_rules; j++) {
			//Select a unique rule on range [REDUCED_SIZE,FULL_SIZE)
			int rule;
			do {
				rule = RANDINT(reduced_num_rules, individual_length - 1);
			} while (population[i][rule] != NULL);

			//Initialize the rule in the individual
			population[i][rule] = PROTEINS[rule].init_val;
		}
	}
}

void natural_selection(bool** population, int* error, int current_population_size, int individual_length, int target_population_size) {
	//TODO sort scores asc whilst sorting index
	//TODO select top SURVIVORS
	//TODO Sort index asc whilst sorting scores
	//TODO Move rows into population(0:9) by cycling through population(survivor_indices(0:9))
}

void proliferate(bool** population, int current_population_size, int individual_length, int target_population_size) {
	double r;

	//Cycle through each individual
	for (int i = 0; i < target_population_size - current_population_size; i++) {
		//Need MOD in case target_pop is not divisible by current_pop
		int parent_index = i % current_population_size;
		int child_index = current_population_size + i;
		
		//Decide to mutate, mate, reproduce
		r = (double)rand() / RAND_MAX;
		if (0 < r && r < P_MUTATE) {
			//MUTATE!
			mutate(population[parent_index], population[child_index], individual_length);
		}
		else if (P_MUTATE < r && r < P_MATE + P_MUTATE) {
			//MATE!

			//Select a second parent
			int parent_2_index;
			do {
				parent_2_index = RANDINT(0, current_population_size - 1);
			} while (parent_2_index == parent_index);

			mate(population[parent_index], population[parent_2_index], population[child_index], individual_length);
		}
		else {
			//REPRODUCE!
			reproduce(population[parent_index], population[child_index], individual_length);
		}
	}
}

void mutate(bool *parent, bool *child, int individual_length) {
	//TODO
}

void mate(bool *parent1, bool *parent2, bool *child, int individual_length) {
	//TODO
}

void reproduce(bool *parent, bool *child, int individual_length) {
	for (int i = 0; i < individual_length; i++) {
		child[i] = parent[i];
	}
}

bool check_stopping_criteria(int *error, int error_size) {
	for (int i = 0; i < error_size; i++) {
		//Return false on any nonzero error
		if (error[i] != 0) {
			return false;
		}
	}
	return true;
}
//Random number on range [min,max] inclusive
#define RANDINT(min,max) (rand() % (max + 1 - min)) + min

/*
* FUNCTION PROTOTYPES
*/
typedef struct Individual;
void initialize_population(bool **population, int population_size, int individual_length, int reduced_num_rules, int target_num_rules);
void natural_selection(Individual *individuals, int current_population_size, int individual_length, int target_population_size);
void proliferate(Individual *individuals, int current_population_size, int individual_length, int target_population_size);
void mutate(bool *parent, bool *child, int individual_length);
void mate(bool *parent1, bool *parent2, bool *child, int individual_length);
void reproduce(bool *parent, bool *child, int individual_length);
bool check_stopping_criteria(Individual *individuals, int error_size);
int cmp_error_asc(const void *pa, const void *pb);

typedef struct Individual {
	int error;
	bool* addr;
};

void initialize_population(bool **population, int population_size, int individual_length, int reduced_num_rules, int target_num_rules) {
	//Cycle through each individual
	for (int i = 0; i < population_size; i++) {
		//Add the reduced rules in since those are
		//present in every individual. Make the rest NULL
		for (int j = 0; j < reduced_num_rules; j++) {
			population[i][j] = 0; //No need to set init_val yet - PROTEIN[j].init_val;
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
			population[i][rule] = 0; //No need to set init_val yet - PROTEIN[rule].init_val;
		}
	}
}

void natural_selection(Individual *individuals, int current_population_size, int individual_length, int target_population_size) {
	//Sort individuals by asc error, therefore individuals[0:MU] are the best MU of the population
	qsort(individuals, current_population_size, sizeof(Individual), cmp_error_asc);
}

void proliferate(Individual *individuals, int current_population_size, int individual_length, int target_population_size) {
	double r;

	//Cycle through each individual
	for (int i = 0; i < target_population_size - current_population_size; i++) {
		//Need MOD in case target_pop is not divisible by current_pop
		int parent_index = i % current_population_size;
		int child_index = current_population_size + i;
		bool * parent = individuals[parent_index].addr;
		bool * child = individuals[child_index].addr;

		//Decide to mutate, mate, reproduce
		r = (double)rand() / RAND_MAX;
		if (0 < r && r < P_MUTATE) {
			//MUTATE!
			mutate(parent, child, individual_length);
		}
		else if (P_MUTATE < r && r < P_MATE + P_MUTATE) {
			//MATE!

			//Select a second parent
			int parent_2_index;
			do {
				parent_2_index = RANDINT(0, current_population_size - 1);
			} while (parent_2_index == parent_index);
			bool * parent_2 = individuals[parent_2_index].addr;

			mate(parent, parent_2, child, individual_length);
		}
		else {
			//REPRODUCE!
			reproduce(parent, child, individual_length);
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

bool check_stopping_criteria(Individual *individuals, int error_size) {
	for (int i = 0; i < error_size; i++) {
		//Return false on any nonzero error
		if (individuals[i].error != 0) {
			return false;
		}
	}
	return true;
}

int cmp_error_asc(const void *pa, const void *pb) {
	int a = ((Individual *)pa)->error;
	int b = ((Individual *)pb)->error;

	if ( a < b ) return -1;
	if ( a > b ) return +1;
	return 0;
}
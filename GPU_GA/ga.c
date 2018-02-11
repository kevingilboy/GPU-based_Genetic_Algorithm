//Random number on range [min,max] inclusive
#define RANDINT(min,max) (rand() % (max + 1 - min)) + min

/*
* FUNCTION PROTOTYPES
*/
struct Individual;
void initialize_population(char population[][FULL_SIZE], int population_size);
void natural_selection(Individual *individuals, int current_population_size);
void proliferate(Individual *individuals);
void mutate(char *parent, char *child);
void mate(char *parent1, char *parent2, char *child);
void reproduce(char *parent, char *child);
bool check_stopping_criteria(Individual *individuals);
int cmp_error_asc(const void *pa, const void *pb);

struct Individual {
	int error;
	char* addr;
};

void initialize_population(char population[][FULL_SIZE], int population_size) {
	//Cycle through each individual
	for (int i = 0; i < population_size; i++) {
		//Add the reduced rules in since those are
		//present in every individual. Make the rest -1
		for (int j = 0; j < REDUCED_RULES; j++) {
			population[i][j] = 0; //No need to set init_val yet - PROTEIN[j].init_val;
		}
		for (int j = REDUCED_RULES; j < FULL_SIZE; j++) {
			population[i][j] = -1;
		}

		//Select TARGET_SIZE unique rules on the range
		//[REDUCED_SIZE,FULL_SIZE) and initialize them
		for (int j = 0; j < EXTENSION_SIZE; j++) {
			//Select a unique rule on range [REDUCED_SIZE,FULL_SIZE)
			int rule;
			do {
				rule = RANDINT(REDUCED_RULES, FULL_SIZE - 1);
			} while (population[i][rule] != -1);

			//Initialize the rule in the individual
			population[i][rule] = 0; //No need to set init_val yet - PROTEIN[rule].init_val;
		}
	}
}

void natural_selection(Individual *individuals, int current_population_size) {
	//Sort individuals by asc error, therefore individuals[0:MU] are the best MU of the population
	qsort(individuals, current_population_size, sizeof(Individual), cmp_error_asc);
}

void proliferate(Individual *individuals) {
	double r;

	//Cycle through each individual
	for (int i = 0; i < TARGET_POPULATION_SIZE - SURVIVORS; i++) {
		//Need MOD in case target_pop is not divisible by current_pop
		int parent_index = i % SURVIVORS;
		int child_index = SURVIVORS + i;
		char * parent = individuals[parent_index].addr;
		char * child = individuals[child_index].addr;

		//Decide to mutate, mate, reproduce
		r = (double)rand() / RAND_MAX;
		if (0 < r && r < P_MUTATE) {
			//MUTATE!
			mutate(parent, child);
		}
		else if (P_MUTATE < r && r < P_MATE + P_MUTATE) {
			//MATE!

			//Select a second parent
			int parent_2_index;
			do {
				parent_2_index = RANDINT(0, SURVIVORS - 1);
			} while (parent_2_index == parent_index);
			char * parent_2 = individuals[parent_2_index].addr;

			mate(parent, parent_2, child);
		}
		else {
			//REPRODUCE!
			reproduce(parent, child);
		}
	}
}

void mutate(char *parent, char *child) {
	double r;
	int index;

	//Store the extended rules for the child here
	int indices_to_include[EXTENSION_SIZE];
	int num_indices = 0;

	//Cycle through each extended rule
	for (int i = REDUCED_RULES; i < FULL_SIZE; i++) {
		r = (double)rand() / RAND_MAX;

		//If index selected to be mutated, add random rule to the array
		if (r < P_MUTATE_INDEX) {
			indices_to_include[num_indices++] = RANDINT(REDUCED_RULES, FULL_SIZE - 1);
		}
		else {
			//Else if not -1, add it to the array
			if (parent[i] != -1) {
				indices_to_include[num_indices++] = i;
			}
		}

		//Might as well erase the child extension here
		child[i] = -1;
	}

	for (int i = 0; i < num_indices; i++) {
		index = indices_to_include[i];
		child[index] = 0;
	}
}

void mate(char *parent1, char *parent2, char *child) {
	//TODO
}

void reproduce(char *parent, char *child) {
	for (int i = 0; i < FULL_SIZE; i++) {
		child[i] = parent[i];
	}
}

bool check_stopping_criteria(Individual *individuals) {
	for (int i = 0; i < SURVIVORS; i++) {
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
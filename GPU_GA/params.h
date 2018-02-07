/*
 * Kevin Gilboy
 * Constants and macros used across the project
 */

/*
 * PROTEINS AND RULES FILE
 */
#include "tcell.c"

/*
 * SIMULATOR CONSTANTS
 */
#define STEPS 1500
#define TRIALS 200

/*
 * GA CONSTANTS
 */
#define INIT_POPULATION_SIZE 300
#define SURVIVORS 10 /*Mu*/
#define TARGET_POPULATION_SIZE 20 /*LAMBDA*/
#define P_MUTATE 0.2
#define P_MATE 0.3
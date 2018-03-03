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
#define P_MUTATE_INDEX 0.2

/*
 * DEBUGGING AND TIMING
 */
//Comment out STOPWATCH to remove the timer
#define CALC_PROGRAM_RUNTIME
#define CALC_FUNCTION_RUNTIME

#ifdef CALC_FUNCTION_RUNTIME
	#define START_TIMER	timer = clock();
	#define END_TIMER printf("\t Completion time: %.3f sec\n\n", (double)((double)(clock()-timer) / CLOCKS_PER_SEC));
#else
	#define START_TIMER  do {} while (0);
	#define END_TIMER  do {} while (0);
#endif

//Comment out DEBUG to remove print statements
#define DEBUG

#ifdef DEBUG
	#define DEBUG_PRINT(x) printf x;
#else
	#define DEBUG_PRINT(x) do {} while (0);
#endif
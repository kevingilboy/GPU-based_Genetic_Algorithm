
/*
 * Kevin Gilboy
 * GPU-ready main kernel
 */

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "simulator.c"
#include <stdio.h>

//Function declarations
void pause();

int main()
{
	printf("Hello world\n");

	pause();
    return 0;
}

void pause() {
	printf("Press [Enter] to continue . . .");
	fflush(stdout);
	getchar();
}
/* ----------------------------------------------------------- */
/* NAME : John Mortimore                     User ID: jgmortim */
/* DUE DATE : 03/22/2019                                       */
/* PROGRAM ASSIGNMENT #3                                       */
/* FILE NAME : thread-main.cpp                                 */
/* PROGRAM PURPOSE :                                           */
/*    A multithreaded implementation of the Even-Odd sorting   */
/*    algorithm. Tested with 0 <= n <= 1,000                   */
/* ----------------------------------------------------------- */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "thread.h"

using namespace std;
void printInitial(int* n);
void printIteration(int n, int iter);
void printFinal(int n, int iter);
void printArray(int n, bool build);
void cleanup();
void term();

int* x;
bool fl;

/* ----------------------------------------------------------- */
/* FUNCTION : main                                             */
/*    The main method for the program.                         */
/* PARAMETER USAGE :                                           */
/*    N/A                                                      */
/* FUNCTIONS CALLED :                                          */
/*    cleanup(), Exit(), JMThread::Begin(),                    */
/*    JMThread::JMThread(), JMThread::Join(), printFinal(),    */
/*    printInitial(), printIteration(), sprintf(), strlen(),   */
/*    write()                                                  */
/* ----------------------------------------------------------- */
int main(void) {
	int i, n, iter=1;
	char output[1024];
	/* Read in data and print inital array. */
	printInitial(&n);
	/* Calculated and create the nessicary number of threads. */
	int evenCount = n/2;
	int oddCount = (n-1)/2;
	JMThread* evenThreads[evenCount];
	JMThread* oddThreads[oddCount];
	/* Sort iterations. */
	if (n > 1) do {
		fl=false;	// Assume no swaps.
		/* Print iteration number and begin even pass. */
		sprintf(output, "\nIteration %d:\n", iter);
		write(1, output, strlen(output));		
		sprintf(output, "    ..........\n    Even Pass:\n");
		write(1, output, strlen(output));
		/* Create and start even threads. Wait for threads to finish before continuing. */
		for (i=0; i < evenCount; i++) evenThreads[i] = new JMThread(x, 2*i+1, &fl);
		for (i=0; i < evenCount; i++) evenThreads[i]->Begin();
		for (i=0; i < evenCount; i++) evenThreads[i]->Join();
		/* Begin odd pass. */
		sprintf(output, "    ..........\n    Odd Pass:\n");
		write(1, output, strlen(output));
		/* Create and start odd threads. Wait for threads to finish before continuing. */
		for (i=0; i < oddCount; i++) oddThreads[i] = new JMThread(x, 2*i+2, &fl);
		for (i=0; i < oddCount; i++) oddThreads[i]->Begin();
		for (i=0; i < oddCount; i++) oddThreads[i]->Join();
		sprintf(output, "    ..........\n");
		write(1, output, strlen(output));
		/* Print the results of the iteration if a swap happened. */
		if (fl)	printIteration(n, iter++);
	} while(fl); // Loop until no swaps happen.
	/* Print the sorted array, clean up, and exit. */
	printFinal(n, iter);
	cleanup();
	Exit();
}

/* ----------------------------------------------------------- */
/* FUNCTION : printInitial                                     */
/*    Reads in and prints out the array to sort.               */
/* PARAMETER USAGE :                                           */
/*    n {int*} - pointer to the size of x[].                   */
/* FUNCTIONS CALLED :                                          */
/*    printArray(), sprintf(), strlen(), write()               */
/* ----------------------------------------------------------- */
void printInitial(int* n) {
	int i;
	char output[1024];
	sprintf(output, "Concurrent Even-Odd Sort\n\n");
	write(1, output, strlen(output));
	cin >> *n; // Read-in the size of the array.
	if (*n < 0) term(); // Invalid input size.
	sprintf(output, "Number of input data = %d\n", *n);
	write(1, output, strlen(output));
	x = new int[*n]; // Create the array.
	sprintf(output, "Input array:\n");
	write(1, output, strlen(output));
	printArray(*n, true); // Populate the array.
}

/* ----------------------------------------------------------- */
/* FUNCTION : printIteration                                   */
/*    Prints out the array after an iteration of sorting.      */
/* PARAMETER USAGE :                                           */
/*    n {int} - size of x[].                                   */
/*    iter {int} - the iteration that finished prior to the    */
/*                 function call.                              */
/* FUNCTIONS CALLED :                                          */
/*    printArray(), sprintf(), strlen(), write()               */
/* ----------------------------------------------------------- */
void printIteration(int n, int iter) {
	char output[1024];
	sprintf(output, "Result after iteration %d:\n", iter);
	write(1, output, strlen(output));
	printArray(n, false);
}

/* ----------------------------------------------------------- */
/* FUNCTION : printFinal                                       */
/*    Prints out the sorted array.                             */
/* PARAMETER USAGE :                                           */
/*    n {int} - size of x[].                                   */
/*    iter {int} - the number of iterations required to sort.  */
/* FUNCTIONS CALLED :                                          */
/*    printArray(), sprintf(), strlen(), write()               */
/* ----------------------------------------------------------- */
void printFinal(int n, int iter) {
	char output[1024];
	sprintf(output, "Final result after iteration %d:\n", iter);
	write(1, output, strlen(output));
	printArray(n, false);
}

/* ----------------------------------------------------------- */
/* FUNCTION : printArray                                       */
/*    Prints out the array. Also creates the array is needed.  */
/*    Prints no more than 20 numbers per line.                 */
/* PARAMETER USAGE :                                           */
/*    n {int} - size of x[].                                   */
/*    build {bool} - Whether or not the array needs to be      */
/*                   read-in.                                  */
/* FUNCTIONS CALLED :                                          */
/*    sprintf(), strlen(), write()                             */
/* ----------------------------------------------------------- */
void printArray(int n, bool build) {
	int i;
	char output[1024];
	/* Print out the array. */
	for (i=0; i<n; i++) {
		if (build) cin >> x[i]; // If building the array, read-in the value first.
		sprintf(output, " %3d", x[i]);
		write(1, output, strlen(output));
		if ((i+1) % 20 == 0) write(1, "\n", strlen("\n"));
	}
	if (i % 20 != 0) write(1, "\n", strlen("\n"));
}

/* ----------------------------------------------------------- */
/* FUNCTION : cleanup                                          */
/*    Frees up allocated memory.                               */
/* PARAMETER USAGE :                                           */
/*    N/A                                                      */
/* FUNCTIONS CALLED :                                          */
/*    N/A                                                      */
/* ----------------------------------------------------------- */
void cleanup() {
	delete [] x;
}

/* ----------------------------------------------------------- */
/* FUNCTION : term                                             */
/*    Handles invalid input. And exits.                        */
/* PARAMETER USAGE :                                           */
/*    N/A                                                      */
/* FUNCTIONS CALLED :                                          */
/*    sprintf(), strlen(), write()                             */
/* ----------------------------------------------------------- */
void term() {
	char* output = "Invalid input. Program exits.\n";
	write(1, output, strlen(output));
	Exit();
}


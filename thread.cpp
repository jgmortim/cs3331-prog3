/* ----------------------------------------------------------- */
/* NAME : John Mortimore                     User ID: jgmortim */
/* DUE DATE : 03/22/2019                                       */
/* PROGRAM ASSIGNMENT #3                                       */
/* FILE NAME : thread.cpp                                      */
/* PROGRAM PURPOSE :                                           */
/*    Contains all class implementations for my threads.       */
/* ----------------------------------------------------------- */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "thread.h"

using namespace std;

/* ----------------------------------------------------------- */
/* FUNCTION : constructor                                      */
/*    Creates a new JMThread.                                  */
/* PARAMETER USAGE :                                           */
/*    X {int*} - pointer to the array to sort.                 */
/*    ID {Int} - the id of the thread.                         */
/*    Flag {bool*} - pointer to flag indicating if a swap      */
/*                   occured.                                  */
/* FUNCTIONS CALLED :                                          */
/*    ThreadName.seekp()                                       */
/* ----------------------------------------------------------- */
JMThread::JMThread(int* X, int ID, bool* Flag) {
	x=X;
	id=ID;
	flag=Flag;
	/* Give the thread a name for Thread Mentor. */
	ThreadName.seekp(0, ios::beg);
	if (id % 2 == 1)ThreadName << "Even_" << ID << '\0';
	if (id % 2 == 0)ThreadName << "Odd_" << ID << '\0';
}

/* ----------------------------------------------------------- */
/* FUNCTION : ThreadFunc                                       */
/*    Process for the thread to perform when begin() is called.*/
/* PARAMETER USAGE :                                           */
/*    N/A                                                      */
/* FUNCTIONS CALLED :                                          */
/*    Exit(), sprintf(), strlen(), Thread::ThreadFunc(),       */
/*    write()                                                  */
/* ----------------------------------------------------------- */
void JMThread::ThreadFunc() {
	Thread::ThreadFunc();
	char output[1024];
	char* tab="        ";
	int temp;
	/* Prints the thread's status. */
	sprintf(output, "%sThread %d created\n", tab, id);
	write(1, output, strlen(output));
	sprintf(output, "%sThread %d compares x[%d]=%d and x[%d]=%d\n", tab, id, id-1, x[id-1], id, x[id]);
	write(1, output, strlen(output));
	/* Compare and swap if needed. */
	if (x[id-1] > x[id]) {
		sprintf(output, "%sThread %d swaps x[%d]=%d and x[%d]=%d\n", tab, id, id-1, x[id-1], id, x[id]);
		write(1, output, strlen(output));
		temp = x[id-1];
		x[id-1] = x[id];
		x[id] = temp;
		*flag = true; // Flag that a swap happened.
	}
	/* Prints the thread's status and exit. */
	sprintf(output, "%sThread %d exits\n", tab, id);
	write(1, output, strlen(output));
	Exit();
}


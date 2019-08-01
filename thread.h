/* ----------------------------------------------------------- */
/* NAME : John Mortimore                     User ID: jgmortim */
/* DUE DATE : 03/22/2019                                       */
/* PROGRAM ASSIGNMENT #3                                       */
/* FILE NAME : thread.h                                        */
/* PROGRAM PURPOSE :                                           */
/*    Contains all class definitions for my threads.           */
/* ----------------------------------------------------------- */
#include "ThreadClass.h"

class JMThread : public Thread {
	public:
		JMThread(int* X, int ID, bool* Flag);
	private:
		void ThreadFunc();
		int* x;
		bool* flag;
		int id;
};


// os345signal.c - signals
// ***********************************************************************
// **   DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER   **
// **                                                                   **
// ** The code given here is the basis for the CS345 projects.          **
// ** It comes "as is" and "unwarranted."  As such, when you use part   **
// ** or all of the code, it becomes "yours" and you are responsible to **
// ** understand any algorithm or method presented.  Likewise, any      **
// ** errors or problems become your responsibility to fix.             **
// **                                                                   **
// ** NOTES:                                                            **
// ** -Comments beginning with "// ??" may require some implementation. **
// ** -Tab stops are set at every 3 spaces.                             **
// ** -The function API's in "OS345.h" should not be altered.           **
// **                                                                   **
// **   DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER ** DISCLAMER   **
// ***********************************************************************
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <assert.h>
#include <sys/queue.h>
#include "os345.h"
#include "os345signals.h"

extern TCB tcb[];							// task control block
extern int curTask;							// current task #

// ***********************************************************************
// ***********************************************************************
//	Call all pending task signal handlers
//
//	return 1 if task is NOT to be scheduled.
//
int signals(void)
{
	if (tcb[curTask].signal)
	{
		if (tcb[curTask].signal & mySIGINT)
		{
			tcb[curTask].signal &= ~mySIGINT;
			(*tcb[curTask].sigIntHandler)();
		}
		
		if (tcb[curTask].signal & mySIGTERM)
    {
      tcb[curTask].signal &= ~mySIGTERM;
      (*tcb[curTask].sigTermHandler)();
    }
    
    if (tcb[curTask].signal & mySIGCONT)
    {
      tcb[curTask].signal &= ~mySIGCONT;
      (*tcb[curTask].sigContHandler)();
    }
    if (tcb[curTask].signal & mySIGTSTP)
    {
      tcb[curTask].signal &= ~mySIGTSTP;
      (*tcb[curTask].sigTstpHandler)();
    }
    
	}
	return 0;
}


// **********************************************************************
// **********************************************************************
//	Register task signal handlers
//
int sigAction(void (*sigHandler)(void), int sig)
{
	switch (sig)
	{
		case mySIGINT:
		{
			tcb[curTask].sigIntHandler = sigHandler;		// mySIGINT handler
			return 0;
		}
    case mySIGTERM:
    {
      tcb[curTask].sigTermHandler = sigHandler;    // mySIGTERM handler
      return 0;
    }
    case mySIGCONT:
    {
      tcb[curTask].sigContHandler = sigHandler;    // mySIGCONT handler
      return 0;
    }
    case mySIGTSTP:
    {
      tcb[curTask].sigTstpHandler = sigHandler;    // mySIGTSTP handler
      return 0;
    }

	}
	return 1;
}


// **********************************************************************
//	sigSignal - send signal to task(s)
//
//	taskId = task (-1 = all tasks)
//	sig = signal
//
int sigSignal(int taskId, int sig)
{
	// check for task
	if ((taskId >= 0) && tcb[taskId].name)
	{
//    if (sig == mySIGTERM)  printf("\ntask %d told to die",taskId);
		tcb[taskId].signal |= sig;
		return 0;
	}
	else if (taskId == -1)
	{
		for (taskId=0; taskId<MAX_TASKS; taskId++)
		{
			sigSignal(taskId, sig);
		}
		return 0;
	}
	// error
	return 1;
}


// **********************************************************************
// **********************************************************************
//	Default signal handlers
//
void defaultSigIntHandler(void)			// task mySIGINT handler
{
  sigSignal(-1,mySIGTERM);
  //printf("\nAttempted to kill all tasks.");
	return;
}

void defaultSigContHandler(void)     // task mySIGCONT handler
{
//  printf("\ndefaultSigIntHandler");
  return;
}

void defaultSigTermHandler(void)     // task mySIGTERM handler
{
  killTask(curTask);
  return;
}

void defaultSigTstpHandler(void)     // task mySIGTSTP handler
{
  sigSignal(-1,mySIGSTOP);
  return;
}



void createTaskSigHandlers(int tid)
{
	tcb[tid].signal = 0;
	if (tid)
	{
		// inherit parent signal handlers
    tcb[tid].sigTermHandler = tcb[curTask].sigTermHandler;      // mySIGTERM handler
    tcb[tid].sigTstpHandler = tcb[curTask].sigTstpHandler;      // mySIGTERM handler
    tcb[tid].sigContHandler = tcb[curTask].sigContHandler;      // mySIGTSTP handler    
		tcb[tid].sigIntHandler = tcb[curTask].sigIntHandler;			// mySIGINT handler
	}
	else
	{
		// otherwise use defaults
		tcb[tid].sigIntHandler = defaultSigIntHandler;			// task mySIGINT handler
    tcb[tid].sigTermHandler = defaultSigTermHandler;      // task mySIGINT handler
    tcb[tid].sigContHandler = defaultSigContHandler;      // task mySIGINT handler
    tcb[tid].sigTstpHandler = defaultSigTstpHandler;      // task mySIGINT handler

	}
}

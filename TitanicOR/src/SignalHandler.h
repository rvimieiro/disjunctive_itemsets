/*
 * SignalHandler.h
 *
 *  Created on: 18/02/2014
 *      Author: Renato Vimieiro
 *  
 * CENTRE FOR BIOINFORMATICS, BIOMARKER-DISCOVERY & INFORMATION-BASED MEDICINE
 * THE UNIVERSITY UNIVERSITY OF NEWCASTLE <http://www.newcastle.edu.au/research-centre/cibm/>
 * HUNTER MEDICAL RESEARCH INSTITUTE <http://hmri.com.au/>
 * Kookaburra Circuit 1, New Lambton Heights, NSW 2305, AUSTRALIA
 */

#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_


#include<signal.h>
#include<iostream>

void terminateHandler (int signal){
	std::cerr << "Terminated with signal " << signal << std::endl;
	exit(signal);
}

/*
 * Adding handlers to finish program immediately
 * after receiving memory related signals.
 * This is to avoid core dumping when execution is abruptly aborted
 * due to memory constraints.
 */
void addMemorySignalHandlers (void){
	signal(SIGABRT,terminateHandler);
	signal(SIGSEGV,terminateHandler);
}

#endif /* SIGNALHANDLER_H_ */

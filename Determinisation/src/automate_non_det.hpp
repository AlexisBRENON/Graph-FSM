
#ifndef __AUTOMATE_NON_DET_H__
#define __AUTOMATE_NON_DET_H__

#include "automate_det.hpp"

struct Automate_Non_Det
{
	int*** Delta;
	int AlphabetSize;
	int NbStates;
	int StartState;
	int NbFinalStates;
	int* FinalStates;
};
typedef struct Automate_Non_Det Automate_Non_Det;


void automateNonDetInit 		(Automate_Non_Det& Aut);
void automateNonDetRelease	(Automate_Non_Det& Aut);

void automateNonDetFromFile	(Automate_Non_Det& Aut, const char* File);
void automateNonDetFromStd	(Automate_Non_Det& Aut);

void automateNonDetDeterminise (const Automate_Non_Det& AutNonDet,
								Automate_Det& AutDet);


int automateNonDetTransitionIter (
						const Automate_Non_Det& Aut,
						const char* strWord
						);

int automateNonDetTransition (
						const Automate_Non_Det& Aut,
						int iCurrentState,
						const char* strWord
						);

int automateNonDetIsFinalState (
						const Automate_Non_Det& Aut,
						int iState
						);

#endif

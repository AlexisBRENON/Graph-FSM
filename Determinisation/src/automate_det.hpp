
#ifndef __AUTOMATE_DET_H__
#define __AUTOMATE_DET_H__

/*
struct Automate_Det
{
	int** Delta;
	int AlphabetSize;
	int NbStates;
	int StartState;
	int NbFinalStates;
	int* FinalStates;
};
typedef struct Automate_Det Automate_Det;
*/
struct Automate_Non_Det;
typedef struct Automate_Non_Det Automate_Det;

void automateDetInit 		(Automate_Det& Aut);
void automateDetRelease	(Automate_Det& Aut);

void automateDetFromFile	(Automate_Det& Aut, const char* File);

int automateDetTransition (
						const Automate_Det& Aut,
						int iCurrentState,
						const char* strWord
						);

int automateDetIsFinalState (
						const Automate_Det& Aut,
						int iState
						);



#endif

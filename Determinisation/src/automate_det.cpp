
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "automate_non_det.hpp"
#include "automate_det.hpp"

void automateDetInit (Automate_Det& Aut)
{
	/*Aut.AlphabetSize = -1;
	Aut.NbStates = -1;
	Aut.Delta = NULL;
	Aut.StartState = -1;
	Aut.FinalStates = NULL;
	Aut.NbFinalStates = -1;*/
	automateNonDetInit(Aut);
}

void automateDetRelease (Automate_Det& Aut)
{
	/*int i;
	for (i = 0; i < Aut.AlphabetSize; i++)
	{
		free(Aut.Delta[i]);
	}
	free(Aut.Delta);
	Aut.StartState = -1;
	if (Aut.FinalStates != NULL) {free(Aut.FinalStates);}
	Aut.NbFinalStates = -1;
	Aut.AlphabetSize = -1;
	Aut.NbStates = -1;*/
	automateNonDetRelease(Aut);
}

void automateDetFromFile (Automate_Det& Aut, const char* file)
{
//	int i,j;
//	int state, newstate;
//	char trans;
//
//	FILE* Automate_DetFile = NULL;
//
//
//	Automate_DetFile = fopen(file, "r");
//
//	fscanf(Automate_DetFile, "%d %d %d\n", 	&(Aut.NbStates),
//										&(Aut.AlphabetSize),
//										&(Aut.NbFinalStates));
//
//	Aut.Delta = (int**) malloc(Aut.AlphabetSize*sizeof(int*));
//	for (i = 0; i < Aut.AlphabetSize; i++)
//	{
//		Aut.Delta[i] = (int*) malloc(Aut.NbStates*sizeof(int));
//	}
//	Aut.FinalStates = (int*) malloc(Aut.NbFinalStates*sizeof(int));
//
//	fscanf(Automate_DetFile, "%d\n", &(Aut.StartState));
//
//	for (i = 0; i < Aut.NbFinalStates; i++)
//	{
//		fscanf(Automate_DetFile, "%d\n", &(Aut.FinalStates[i]));
//	}
//
//	for (i = 0; i < Aut.NbStates; i++)
//	{
//		for (j = 0; j < Aut.AlphabetSize; j++)
//		{
//			fscanf (Automate_DetFile, "%d %c %d\n", &state, &trans, &newstate);
//			Aut.Delta[trans-97][state] = newstate;
//		}
//	}
//
//	fclose(Automate_DetFile);
	automateNonDetFromFile(Aut, file);
}

int automateDetTransition (
						const Automate_Det& Aut,
						int iCurrentState,
						const char* strWord
						)
{
//	int iFound = 0;
//	int iNewState = 0;
//
//	if (strWord[0] == '\0')
//	{
//		iFound = automateDetIsFinalState(Aut, iCurrentState);
//	}
//	else
//	{
//		iNewState = Aut.Delta[strWord[0]-'a'][iCurrentState];
//		iFound = automateDetTransition(Aut, iNewState, &(strWord[1]));
//	}
//
//	return iFound;

	return automateNonDetTransition (Aut, iCurrentState, strWord);
}


int automateDetIsFinalState (
						const Automate_Det& Aut,
						int iState
						)
{
//	int i;
//	for (i = 0; i < Aut.NbFinalStates; i++)
//	{
//		if (Aut.FinalStates[i] == iState)
//		{
//			return 1;
//		}
//		else
//		{
//		}
//	}
//	return 0;

	return automateNonDetIsFinalState(Aut, iState);
}

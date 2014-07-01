#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>

#include "automate_det.hpp"
#include "automate_non_det.hpp"

char** generateWords (int iLength, int iAlphabetSize);
void destroyWords (char*** Words, int iMaxLength, int iAlphabetSize);

int main()
{
	unsigned int i;
	Automate_Det AutDet;
	Automate_Non_Det AutNonDet;
	unsigned int iNbWords;
	char** Words;
	int resultNonDet;
	int resultDet;


	automateDetInit(AutDet);
	/* Charge l'automate depuis un fichier */
	automateNonDetFromFile(AutNonDet, "automate_nondet.txt");
	std::cout << "Automate initialisé via fichier." << std::endl;
	automateNonDetDeterminise(AutNonDet, AutDet);
	std::cout << "Automate déterminisé." << std::endl;

	Words = generateWords(5, AutDet.AlphabetSize-1);
	iNbWords = (int) pow(AutDet.AlphabetSize-1, 6);
	iNbWords = iNbWords-1;
	iNbWords = iNbWords/(AutDet.AlphabetSize-2);
	for (i = 0; i < iNbWords; i++)
	{
		std::cout << i << " : " << Words[i] << std::endl;
		resultNonDet = automateNonDetTransition(AutNonDet, AutNonDet.StartState, Words[i]);
		resultDet = automateDetTransition(AutDet, AutDet.StartState, Words[i]);
		if (resultNonDet == resultDet)
		{
			std::cout << "\tRésultat commun : ";
			if (resultNonDet == 1)
			{
				std::cout << "Accepté" << std::endl;
			}
			else
			{
				std::cout << "REFUSE" << std::endl;
			}
		}
		else
		{
			exit(-1);
		}


	}

	destroyWords(&Words, 5, AutDet.AlphabetSize-1);
	automateDetRelease(AutDet);
	automateNonDetRelease(AutNonDet);

    return 0;
}

char** generateWords (int iMaxLength, int iAlphabetSize)
{
	char** WordsArray = NULL;
	int* CounterArray = NULL;
	unsigned int NbWords;
	unsigned int i,j;

	NbWords = (int) pow(iAlphabetSize, iMaxLength+1);
	NbWords = NbWords-1;
	NbWords = NbWords/(iAlphabetSize-1);
	WordsArray = (char**) malloc(NbWords*sizeof(char*));
	CounterArray = (int*) malloc(iMaxLength*sizeof(int));

	for (i = 0; i < (unsigned int) iMaxLength; i++)
	{
		CounterArray[i] = 0;
	}

	for (i = 0; i < NbWords; i++)
	{
		WordsArray[i] = (char*) malloc(iMaxLength*sizeof(char));
		for (j = 0; j < (unsigned int) iMaxLength; j++)
		{
			if (CounterArray[j] == 0)
			{
				WordsArray[i][j] = 0;
			}
			else
			{
				WordsArray[i][j] = CounterArray[j]+96;
			}
		}
		CounterArray[0]++;
		for (j = 0; j < (unsigned int) iMaxLength; j++)
		{
			if (CounterArray[j] > iAlphabetSize)
			{
				CounterArray[j] = 1;
				CounterArray[j+1]++;
			}
		}
	}

	free(CounterArray);
	return WordsArray;
}

void destroyWords(char*** Words, int iMaxLength, int iAlphabetSize)
{
	unsigned int i, NbWords;

	NbWords = (int) pow(iAlphabetSize, iMaxLength+1);
	NbWords = NbWords-1;
	NbWords = NbWords/(iAlphabetSize-1);

	for (i = 0; i < NbWords; i++)
	{
		free((*Words)[i]);
	}
	free(*Words);
}

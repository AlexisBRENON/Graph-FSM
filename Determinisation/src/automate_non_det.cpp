#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <string>

#include "automate_det.hpp"
#include "automate_non_det.hpp"

using namespace std;

static int find(vector<set<int> > Tab, set<int> element);
int find(vector<set<int> > Tab, set<int> element)
{
	unsigned int it;

	for (it = 0;
		it < Tab.size();
		it++)
	{
		if (Tab[it] == element)
		{
			return it;
		}
	}

	return -1;
}

static int insertUnic(vector<set<int> >& Tab, set<int> element);
int insertUnic(vector<set<int> >& Tab, set<int> element)
{
	int finded = 0;

	finded = find(Tab, element);
	if (finded >= 0)
	{
		return finded;
	}
	else
	{
		Tab.push_back(element);
		return (Tab.size()-1);
	}
}

static bool containFinalState(const Automate_Non_Det& Aut, const set<int>& States);
bool containFinalState(const Automate_Non_Det& Aut, const set<int>& States)
{
	int i;
	set<int>::iterator it;

	for (i = 0;
		i < Aut.NbFinalStates;
		i++)
	{
		it = States.find(Aut.FinalStates[i]);

		if (it != States.end())
		{
			return true;
		}
	}

	return false;
}

void automateNonDetInit (Automate_Non_Det& Aut)
{
	Aut.AlphabetSize = -1;
	Aut.NbStates = -1;
	Aut.Delta = NULL;
	Aut.StartState = -1;
	Aut.FinalStates = NULL;
	Aut.NbFinalStates = -1;
}

void automateNonDetRelease (Automate_Non_Det& Aut)
{
	int i,j;

	for (i = 0; i < Aut.AlphabetSize; i++)
	{
		for (j = 0; j < Aut.NbStates; j++)
		{
			free(Aut.Delta[i][j]);
		}
		free(Aut.Delta[i]);
	}
	free(Aut.Delta);
	free(Aut.FinalStates);
	Aut.AlphabetSize = -1;
	Aut.NbStates = -1;
	Aut.StartState = -1;
	Aut.NbFinalStates = -1;
}

void automateNonDetFromFile (Automate_Non_Det& Aut, const char* file)
{
	int i,j;
	int state, newstate;
	char trans;

	FILE* AutomateFile = NULL;


	AutomateFile = fopen(file, "r");

	fscanf(AutomateFile, "%d %d %d\n", 	&(Aut.NbStates),
										&(Aut.AlphabetSize),
										&(Aut.NbFinalStates));
	/* On incrément la taille de l'alphabet pour prendre en compte 'e' qui
	ne fait pas parti de l'alphabet */
	Aut.AlphabetSize++;

	Aut.Delta = (int***) malloc(Aut.AlphabetSize*sizeof(int**));
	for (i = 0; i < Aut.AlphabetSize; i++)
	{
		Aut.Delta[i] = (int**) malloc(Aut.NbStates*sizeof(int*));
		for (j = 0; j < Aut.NbStates; j++)
		{
			Aut.Delta[i][j] = (int*) malloc((Aut.NbStates + 1)*sizeof(int));
			Aut.Delta[i][j][0] = 0;
		}
	}
	Aut.FinalStates = (int*) malloc(Aut.NbFinalStates*sizeof(int));

	fscanf(AutomateFile, "%d\n", &(Aut.StartState));

	for (i = 0; i < Aut.NbFinalStates; i++)
	{
		fscanf(AutomateFile, "%d\n", &(Aut.FinalStates[i]));
	}

	while (fscanf(AutomateFile, "%d %c %d\n", &state, &trans, &newstate) == 3)
	{
		int iNbChoice = 0;
		if (trans != 'e')
		{
			iNbChoice = Aut.Delta[trans-'a'+1][state][0];
			(Aut.Delta[trans-'a'+1][state][0])++;
			Aut.Delta[trans-'a'+1][state][iNbChoice+1] = newstate;
		}
		else
		{
			iNbChoice = Aut.Delta[0][state][0];
			(Aut.Delta[0][state][0])++;
			Aut.Delta[0][state][iNbChoice+1] = newstate;
		}
	}

	fclose(AutomateFile);
}


void automateNonDetDeterminise (const Automate_Non_Det& AutNonDet,
								Automate_Det& AutDet)
{
	int i, j;
	int iNbChoice;
	int result;
	bool reloop = true;

	int iNbFinalState = 0;
	FILE* file = NULL;

	string strDelta;
	ostringstream oss;
	vector<set<int> > QDet;
	unsigned int itQDet;
	set<int> CurrentNewState;
	set<int>::iterator itCurrentNewState;
	pair<set<int>::iterator, bool> insertResult;
	set<int> NextCurrentNewState;



/* On crée l'epsilon-fermeture de l'état initial */
	CurrentNewState.insert(AutNonDet.StartState);
	while (reloop == true)
	{
		reloop = false;
		for (itCurrentNewState = CurrentNewState.begin();
			itCurrentNewState != CurrentNewState.end();
			itCurrentNewState++)
		{
			iNbChoice = AutNonDet.Delta[0][*itCurrentNewState][0];
			for (j = 0; j < iNbChoice; j++)
			{
				insertResult = CurrentNewState.insert(AutNonDet.Delta[0][*itCurrentNewState][j+1]);
				if (insertResult.second == true) {reloop = true;}
			}
		}
	}
	insertUnic(QDet, CurrentNewState);

	for (i = 1; i < AutNonDet.AlphabetSize; i++)
	/* Pour chaque lettre de l'alphabet */
	{
		for (itCurrentNewState = CurrentNewState.begin();
			itCurrentNewState != CurrentNewState.end();
			itCurrentNewState++)
		/* On regarde pour chaque état de l'epsilon-fermeture, là où ça
		nous mene */
		{
			iNbChoice = AutNonDet.Delta[i][*itCurrentNewState][0];
			for (j = 0; j < iNbChoice; j++)
			{
				NextCurrentNewState.insert(AutNonDet.Delta[i][*itCurrentNewState][j+1]);
			}
		}
		result = insertUnic(QDet, NextCurrentNewState);
		oss << 0 << " " << (char) (i+96) << " " << result << endl;
		NextCurrentNewState.clear();
	}
	CurrentNewState.clear();
	NextCurrentNewState.clear();

/* Une fois qu'on a gèré l'état initial, on peut boucler pour le reste
des états de l'automate */

	for (itQDet = 1;
		itQDet < QDet.size();
		itQDet++)
	{
		CurrentNewState = QDet[itQDet];

		reloop = true;
		while (reloop == true)
		{
			reloop = false;
			for (itCurrentNewState = CurrentNewState.begin();
			itCurrentNewState != CurrentNewState.end();
			itCurrentNewState++)
			/* On calcule l'epsilon-fermeture de l'état courant */
			{
				iNbChoice = AutNonDet.Delta[0][*itCurrentNewState][0];
				for (j = 0; j < iNbChoice; j++)
				{
					insertResult = CurrentNewState.insert(AutNonDet.Delta[0][*itCurrentNewState][j+1]);
					if (insertResult.second == true) {reloop = true;}
				}
			}
			QDet[itQDet] = CurrentNewState;
		}

		for (i = 1; i < AutNonDet.AlphabetSize; i++)
		/* Pour chaque lettre de l'alphabet */
		{
			for (itCurrentNewState = CurrentNewState.begin();
				itCurrentNewState != CurrentNewState.end();
				itCurrentNewState++)
			/* On regarde pour chaque état de l'epsilon-fermeture, là où ça
			nous mene */
			{
				iNbChoice = AutNonDet.Delta[i][*itCurrentNewState][0];
				for (j = 0; j < iNbChoice; j++)
				{
					NextCurrentNewState.insert(AutNonDet.Delta[i][*itCurrentNewState][j+1]);
				}
			}
			result = insertUnic(QDet, NextCurrentNewState);
			oss << itQDet << " " << (char) (i+96) << " " << result << endl;
			NextCurrentNewState.clear();
		}
		CurrentNewState.clear();
		NextCurrentNewState.clear();
	}


	/* On écris un fichier qui permettra de créer l'automate deterministe */
	file = fopen("Temp.txt", "w");
	if (file != NULL)
	{
		for (itQDet = 0;
			itQDet < QDet.size();
			itQDet++)
		{
			if (containFinalState(AutNonDet, QDet[itQDet]) == true)
			{
				iNbFinalState++;
			}
		}

		fprintf(file, "%lu %d %d\n",
				QDet.size(),
				AutNonDet.AlphabetSize-1,
				iNbFinalState);
		fprintf(file, "0\n");

		for (itQDet = 0;
			itQDet < QDet.size();
			itQDet++)
		{
			if (containFinalState(AutNonDet, QDet[itQDet]) == true)
			{
				fprintf(file, "%d\n", itQDet);
			}
		}

		strDelta = oss.str();
		fprintf(file, "%s\n", strDelta.c_str());

		fclose(file);

		automateDetFromFile(AutDet, "Temp.txt");
	}
}


int automateNonDetTransitionIter (
						const Automate_Non_Det& Aut,
						const char* strWord
						)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int iFound = 0;
	int iNbChoice = 0;
	int* iarrStates = NULL;
	int* iarrChoice = NULL;
	int iCurrentState = 0;
	int iWordLength = 0;

	iWordLength = strlen(strWord);
	iWordLength++;
	iarrChoice = (int*) malloc(iWordLength*Aut.NbStates*sizeof(int));
	iarrStates = (int*) malloc(iWordLength*Aut.NbStates*sizeof(int));

	for (i = 0; i < (iWordLength*Aut.NbStates); i++)
	{
		iarrStates[i] = 0;
		iarrChoice[i] = 0;
	}

	i = 0;
	iCurrentState = Aut.StartState;
	iarrStates[0] = iCurrentState;
	iarrChoice[0] = 0;

	while (iFound == 0 && k < iWordLength)
	{
		/* On initialise nos variables */
		k = (k<0) ? 0 : k; /* Position dans le mot */
		iCurrentState = iarrStates[i];	/* Etat courant */
		i++;	/* On cherche le nouvel état */
		j = iarrChoice[i];	/* On regarde cmb de transitions ont a déja essayées */

		if (strWord[k] == '\0')
		/* Si on pointe sur la fin du mot */
		{
			/* On regarde si on est dans un état final */
			iFound = automateNonDetIsFinalState(Aut, iCurrentState);

			/* Si on est pas dans un état final */
			if (iFound == 0)
			{
				/* On regarde le nombre de transitions spontannées */
				iNbChoice = Aut.Delta[0][iCurrentState][0];

				if (j < iNbChoice)
				/* Si le nombre de tests déja faits est inférieur aux
				nombres de transitions possible */
				{
					/* On avance dans le prochain état possible */
					iarrStates[i] =
						Aut.Delta[0][iCurrentState][j+1];
					/* On stocke le nouveau nb de tests effectués */
					iarrChoice[i] = j+1;
				}
				else
				/* Sinon, si on a déja essayé toutes les transitions */
				{
					if (iCurrentState == Aut.StartState)
					/* Si on est à l'état initial et qu'on a tt essayé,
					c'est que le mot n'est pas accepté */
					{
						k = iWordLength;
					}
					else
					/* Sinon, on continue */
					{
						/* On remet à zéro notre tableau pour cette étape */
						iarrStates[i] = 0;
						iarrChoice[i] = 0;
						/* On revient dans l'état précédent */
						i-=2;
						/* On recule dans le mot */
						k--;
					}
				}
			}
		}
		else
		/* Si on est encore dans le mot */
		{
			/* On regarde le nombre de transitions correspondant à la
			lettre */
			iNbChoice = Aut.Delta[strWord[k]-'a'+1][iCurrentState][0];


			if (iFound == 0 && j < iNbChoice)
			/* S'il y a une transition possible que l'on a pas encore
			essayée */
			{
				/* On avance dans cet état */
				iarrStates[i] =
					Aut.Delta[strWord[k]-'a'+1][iCurrentState][j+1];
				/* On met le nouveau nb d'essais */
				iarrChoice[i] = j+1;
				/* On avance dans le mot */
				k++;
			}
			else
			/* Si on a déja essayé ts les choix ou qu'il n'y a pas de
			transition étiquetée. */
			{
				/* On regarde s'il n'y a pas de transition spontanée */
				iNbChoice = Aut.Delta[0][iCurrentState][0];
				if (j < iNbChoice)
				/* S'il y en a une non essayée */
				{
					/* On avance dans le nouvel état */
					iarrStates[i] =
						Aut.Delta[0][iCurrentState][j+1];
					/* On augmente le nb d'essais */
					iarrChoice[i] = j+1;
				}
				else
				/* Sinon, si on a tt essayé */
				{
					if (iCurrentState == Aut.StartState)
					/* Si on est à l'état initial et qu'on a tt essayé,
					c'est que le mot n'est pas accepté */
					{
						k = iWordLength;
					}
					else
					/* Sinon, on continue */
					{
						/* On remet à zéro notre tableau pour cette étape */
						iarrStates[i] = 0;
						iarrChoice[i] = 0;
						/* On revient dans l'état précédent */
						i-=2;
						/* On recule dans le mot */
						k--;
					}
				}
			}
		}
	}

	free(iarrChoice);
	free(iarrStates);

	return iFound;
}


int automateNonDetTransition (
						const Automate_Non_Det& Aut,
						int iCurrentState,
						const char* strWord
						)
{
	int iFound = 0;
	int i = 0;
	int iNbChoice = 0;
	int iNewState = 0;

	if (strWord[0] == '\0')
	{
		iFound = automateNonDetIsFinalState(Aut, iCurrentState);

		iNbChoice = Aut.Delta[0][iCurrentState][0];
		while (i < iNbChoice && iFound == 0)
		{
			iNewState = Aut.Delta[0][iCurrentState][i+1];
			iFound = automateNonDetTransition(Aut, iNewState, &(strWord[0]));
			i++;
		}

	}
	else
	{
		iNbChoice = Aut.Delta[strWord[0]-'a'+1][iCurrentState][0];

		/* Si on est bloqué dans un état (sans avoir lu tout le mot) */
		if (iNbChoice == 0)
		{
			i = 0;
			iFound = 0;

			iNbChoice = Aut.Delta[0][iCurrentState][0];
			while (i < iNbChoice && iFound == 0)
			{
				iNewState = Aut.Delta[0][iCurrentState][i+1];
				iFound = automateNonDetTransition(Aut, iNewState, &(strWord[0]));
				i++;
			}
		}
		else
		{
			i = 0;
			iFound = 0;
			while (i < iNbChoice && iFound == 0)
			{
				iNewState = Aut.Delta[strWord[0]-'a'+1][iCurrentState][i+1];
				iFound = automateNonDetTransition(Aut, iNewState, &(strWord[1]));
				i++;
			}

			i = 0;
			iNbChoice = Aut.Delta[0][iCurrentState][0];
			while (i < iNbChoice && iFound == 0)
			{
				iNewState = Aut.Delta[0][iCurrentState][i+1];
				iFound = automateNonDetTransition(Aut, iNewState, &(strWord[0]));
				i++;
			}
		}
	}

	return iFound;
}


int automateNonDetIsFinalState (
						const Automate_Non_Det& Aut,
						int iState
						)
{
	int i;
	for (i = 0; i < Aut.NbFinalStates; i++)
	{
		if (Aut.FinalStates[i] == iState)
		{
			return 1;
		}
		else
		{
		}
	}
	return 0;
}































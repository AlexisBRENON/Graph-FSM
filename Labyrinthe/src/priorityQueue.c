#include <stdlib.h>
#include <assert.h>

#include "dynamic_array.h"
#include "priorityQueue.h"

static int priorityQueueSearchIndex (PriorityQueue const* psQueue,
									int iPriority);
int priorityQueueSearchIndex (PriorityQueue const* psQueue,
							int iPriority)
/* Fonction de recherche dichotomique dans le tableau de priorité */
{
	int iMin, iMax, iMed;
	DynamicArray const* Tab = NULL;
	int iValue;

	assert (psQueue != NULL);
	assert (iPriority > 0);

	Tab = &(psQueue->Priority);
	iMin = 0;
	dynamicArrayGetSize(Tab, &iMax);

	while (iMin < iMax)
	{
		iMed = (iMin+iMax)/2;
		dynamicArrayGet(Tab, iMed, &iValue);
		if (iValue == iPriority)
		{
			return iMed;
		}
		else if (iValue > iPriority)
		{
			iMax = iMed;
		}
		else
		{
			iMin = iMed+1;
		}
	}

	return iMin;
}


PriorityQueue* priorityQueueCreate()
/* Alloue et initialise une file de priorité */
{
	PriorityQueue* psQueue = NULL;

	psQueue = (PriorityQueue*) malloc(sizeof(PriorityQueue));
	priorityQueueInit(psQueue);

	return psQueue;
}
void priorityQueueDestroy(PriorityQueue** ppsQueue)
/* Libère et désaloue une file de rpiorité */
{
	assert (ppsQueue != NULL);
	assert (*ppsQueue != NULL);

	priorityQueueRelease(*ppsQueue);
	free(*ppsQueue); *ppsQueue = NULL;
}

void priorityQueueInit(PriorityQueue* psQueue)
/* Initialise une file de priorité */
{
	assert (psQueue != NULL);

	dynamicArrayInit(&(psQueue->Priority));
	dynamicArrayInit(&(psQueue->Data));
}
void priorityQueueRelease (PriorityQueue* psQueue)
/* Libère une file de priorité */
{
	assert (psQueue != NULL);

	dynamicArrayRelease(&(psQueue->Priority));
	dynamicArrayRelease(&(psQueue->Data));
}


void priorityQueueInsert (PriorityQueue* psQueue,
						int iValue,
						int iPriority)
/* Insère une nouvelle entrée dans une file de priorité */
{
	int iIndex;

	assert (psQueue != NULL);

	iIndex = priorityQueueSearchIndex(psQueue, iPriority);
	dynamicArrayInsert(&(psQueue->Priority), iIndex, iPriority);
	dynamicArrayInsert(&(psQueue->Data), iIndex, iValue);
}

void priorityQueuePop (PriorityQueue* psQueue)
/* Supprime la tête de la file */
{
	assert (psQueue != NULL);

	dynamicArrayRemove(&(psQueue->Priority), 0);
	dynamicArrayRemove(&(psQueue->Data), 0);
}

int priorityQueueTop (PriorityQueue const* psQueue)
/* Consulte la valeur de priorité la plus faible (tête de file) */
{
	int iValue;

	assert (psQueue != NULL);

	dynamicArrayGet(&(psQueue->Data), 0, &iValue);

	return iValue;
}


int priorityQueueSize (PriorityQueue const* psQueue)
{
	int iSize;

	assert (psQueue != NULL);

	dynamicArrayGetSize(&(psQueue->Priority), &iSize);

	return iSize;
}


void priorityQueueChangePriority (PriorityQueue* psQueue,
								int iValue,
								int iNewPriority)
/* Modifie la priorité d'un élément s'il est déja présent */
{
	int i, iMax;
	int iOldValue;
	assert (psQueue != NULL);

	dynamicArrayGetSize(&(psQueue->Data), &iMax);

	for (i = 0; i < iMax; i++)
	{
		dynamicArrayGet(&(psQueue->Data), i, &iOldValue);
		if (iOldValue== iValue)
		{
			dynamicArrayRemove(&(psQueue->Data), i);
			dynamicArrayRemove(&(psQueue->Priority), i);
			priorityQueueInsert(psQueue, iValue, iNewPriority);
		}
	}
}

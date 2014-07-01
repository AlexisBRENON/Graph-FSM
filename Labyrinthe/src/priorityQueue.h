#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include "dynamic_array.h"

struct sPriorityQueue
{
	DynamicArray Priority;
	DynamicArray Data;
};
typedef struct sPriorityQueue PriorityQueue;


/* Fonctions de créations/destruction d'une file de priorité */
PriorityQueue* priorityQueueCreate ();
void priorityQueueDestroy (PriorityQueue** ppsQueue);

/* Fonctions d'allocation/libération d'une file de prio */
void priorityQueueInit ();
void priorityQueueRelease (PriorityQueue* psQueue);

/* Ajout/suppression d'un élément */
void priorityQueueInsert (PriorityQueue* psQueue,
						int iValue,
						int iPriority);
void priorityQueuePop (PriorityQueue* psQueue);

/* Accesseurs */
	/* Consultation du début de file */
int priorityQueueTop (PriorityQueue const* psQueue);
	/* Taille de la file */
int priorityQueueSize (PriorityQueue const* psQueue);

/* Mutateur */
	/* Modification d'un indice de priorité */
void priorityQueueChangePriority (PriorityQueue* psQueue,
								int iValue,
								int iNewPriority);































#endif

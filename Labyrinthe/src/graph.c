#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

#include "graph.h"
#include "priorityQueue.h"

Graph* graphCreate (int iWidth, int iHeight)
/* Alloue un graphe dans le tas et l'initialise */
{
    Graph* psGraph = NULL;

    assert (iWidth > 0);
    assert (iHeight > 0);

    psGraph = (Graph*) malloc(sizeof(Graph));

    graphInit(psGraph, iWidth, iHeight);

    return psGraph;
}
void graphDestroy (Graph** ppsGraph)
/* Libère un graphe et désalloue */
{
    assert (ppsGraph != NULL);
    assert (*ppsGraph != NULL);

    graphRelease (*ppsGraph);
    free(*ppsGraph);
    *ppsGraph = NULL;
}

void graphInit (Graph* psGraph, int iWidth, int iHeight)
/* Initialise un graph déja alloué */
{
    int i, j;

    assert (psGraph != NULL);
    assert (iWidth > 0);
    assert (iHeight > 0);

    psGraph->iWidth = iWidth;
    psGraph->iHeight= iHeight;

    psGraph->Tab = (Node***) malloc(iWidth*sizeof(Node**));
    for (i = 0; i < iWidth; i++)
    {
        psGraph->Tab[i] = (Node**) malloc(iHeight*sizeof(Node*));

        for (j = 0; j < iHeight; j++)
        {
            psGraph->Tab[i][j] = NULL;
        }
    }
}
void graphRelease (Graph* psGraph)
/* Libère un graphe */
{
    int i, j;

    assert (psGraph != NULL);

    for (i = 0; i < psGraph->iWidth; i++)
    {
        for (j = 0; j < psGraph->iHeight; j++)
        {
            if (psGraph->Tab[i][j] != NULL)
            {
                nodeDestroy(&(psGraph->Tab[i][j]));
            }
        }
        free(psGraph->Tab[i]);
    }
    free(psGraph->Tab);
}

void graphCreateNode (
    Graph* psGraph,
    int iX, int iY,
    int up, int right, int down, int left
)
/* Akoute un noeud au graphe (allocation, linkage aux voisins) */
{
    assert (psGraph != NULL);
    assert (iX < psGraph->iWidth && iX >= 0);
    assert (iY < psGraph->iHeight && iY >= 0);

    if (psGraph->Tab[iX][iY] != NULL)
    {
        fprintf(stderr, "**WARNING** : Le noeud existe deja...\n");
    }
    else
    {
        psGraph->Tab[iX][iY] = nodeCreate(NULL,
                                          iX, iY,
                                          NULL, 0,
                                          NULL, 0,
                                          NULL, 0,
                                          NULL, 0);
        if (iY > 0 && psGraph->Tab[iX][iY-1] != NULL)
        {
            graphActivateLink(psGraph, iX, iY, 'u', up);
            graphActivateLink(psGraph, iX, iY-1, 'd', up);
        }
        if (iY < psGraph->iHeight-1 && psGraph->Tab[iX][iY+1] != NULL)
        {
            graphActivateLink(psGraph, iX, iY, 'd', down);
            graphActivateLink(psGraph, iX, iY+1, 'u', down);
        }
        if (iX > 0 && psGraph->Tab[iX-1][iY] != NULL)
        {
            graphActivateLink(psGraph, iX, iY, 'l', left);
            graphActivateLink(psGraph, iX-1, iY, 'r', left);
        }
        if (iX < psGraph->iWidth-1 && psGraph->Tab[iX+1][iY] != NULL)
        {
            graphActivateLink(psGraph, iX, iY, 'r', right);
            graphActivateLink(psGraph, iX+1, iY, 'l', right);
        }
    }
}

/* Accesseurs */
Node* graphGetNode (
    const Graph* psGraph,
    int iX, int iY
)
/* Renvoi un noeud selon ses coordonnées */
{
    assert (psGraph != NULL);
    assert (iX < psGraph->iWidth && iX >= 0);
    assert (iY < psGraph->iHeight && iY >= 0);

    return (psGraph->Tab[iX][iY]);
}
Node* graphGetNodeSequential (Graph const* psGraph,
                              int iIndex)
/* Renvoi un noeud selon son index */
{
    int iX, iY;
    assert (iIndex >= 0 && iIndex < psGraph->iWidth*psGraph->iHeight);

    iX = iIndex/psGraph->iHeight;
    iY = iIndex - (iX*psGraph->iHeight);

    return psGraph->Tab[iX][iY];
}

void graphActivateLink (
    Graph* psGraph,
    int iX, int iY,
    char cDir, int iValue
)
/* Active ou modifie la valeur d'un lien du noeud de coordonées iX, iY */
{
    assert (psGraph != NULL);
    assert (iX >= 0 && iX < psGraph->iWidth);
    assert (iY >= 0 && iY < psGraph->iHeight);

    if (psGraph->Tab[iX][iY] != NULL)
    {
        switch (cDir)
        {
        case 'u':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        psGraph->Tab[iX][iY-1],
                        iValue);
            break;
        case 'r':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        psGraph->Tab[iX+1][iY],
                        iValue);
            break;
        case 'd':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        psGraph->Tab[iX][iY+1],
                        iValue);
            break;
        case 'l':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        psGraph->Tab[iX-1][iY],
                        iValue);
            break;
        default:
            break;
        }
    }
}

void graphDeactivateLink (
    Graph* psGraph,
    int iX, int iY,
    char cDir
)
/* Désactive un lien du noeud de coordonnées iX, iY. */
{
    assert (psGraph != NULL);
    assert (iX >= 0 && iX < psGraph->iWidth);
    assert (iY >= 0 && iY < psGraph->iHeight);

    if (psGraph->Tab[iX][iY] != NULL)
    {
        switch (cDir)
        {
        case 'u':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        NULL,
                        0);
            break;
        case 'r':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        NULL,
                        0);
            break;
        case 'd':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        NULL,
                        0);
            break;
        case 'l':
            nodeSetLink(psGraph->Tab[iX][iY],
                        cDir,
                        NULL,
                        0);
            break;
        default:
            break;
        }
    }
}


int graphGetWidth (
    const Graph* psGraph
)
{
    return psGraph->iWidth;
}







void graphPrint (const Graph* psGraph)
/* Affiche le graphe sur la sortie standard */
{
    int i, j;
    Link l;

    assert (psGraph != NULL);

    printf("      ");
    for (i = 0; i < psGraph->iWidth; i++)
    {
        printf("%3d  ", i);
    }
    printf("\n");
    for (j = 0; j < psGraph->iHeight; j++)
    {
        printf("      ");
        for (i = 0; i < psGraph->iWidth; i++)
        {
            if (psGraph->Tab[i][j] != NULL)
            {
                l = nodeGetLink(psGraph->Tab[i][j], 'u');
                if (linkGetDest(&l) != NULL)
                {
                    printf("  ^  ");
                }
                else
                {
                    printf("     ");
                }
            }
            else
            {
                printf("     ");
            }
        }
        printf("\n");
        printf("%3d   ", j);
        for (i = 0; i < psGraph->iWidth; i++)
        {
            if (psGraph->Tab[i][j] != NULL)
            {
                l = nodeGetLink(psGraph->Tab[i][j], 'l');
                if (linkGetDest(&l) != NULL)
                {
                    printf(" <");
                }
                else
                {
                    printf("  ");
                }
                printf("o");
                l = nodeGetLink(psGraph->Tab[i][j], 'r');
                if (linkGetDest(&l) != NULL)
                {
                    printf("> ");
                }
                else
                {
                    printf("  ");
                }
            }
            else
            {
                printf("     ");
            }
        }
        printf("\n");
        printf("      ");
        for (i = 0; i < psGraph->iWidth; i++)
        {
            if (psGraph->Tab[i][j] != NULL)
            {
                l = nodeGetLink(psGraph->Tab[i][j], 'd');
                if (linkGetDest(&l) != NULL)
                {
                    printf("  v  ");
                }
                else
                {
                    printf("     ");
                }
            }
            else
            {
                printf("     ");
            }
        }
        printf("\n");
    }

}

int graphCost (Graph const* psGraph, Node const* Nsrc, Node const* Ndest)
/* Renvoi le cout entre deux noeuds */
{
    Link l;

    assert (psGraph != NULL);
    assert (Nsrc != NULL);

    if (Ndest == NULL)
    {
        return INT_MAX;
    }

	if (Ndest == Nsrc)
	{
		return 0;
	}

    l = nodeGetLink(Nsrc, 'u');
    if (linkGetDest(&l) == Ndest)
    {
        return linkGetValue(&l);
    }
    l = nodeGetLink(Nsrc, 'r');
    if (linkGetDest(&l) == Ndest)
    {
        return linkGetValue(&l);
    }
    l = nodeGetLink(Nsrc, 'd');
    if (linkGetDest(&l) == Ndest)
    {
        return linkGetValue(&l);
    }
    l = nodeGetLink(Nsrc, 'l');
    if (linkGetDest(&l) == Ndest)
    {
        return linkGetValue(&l);
    }

    return INT_MAX;
}

unsigned int graphDijkstra (
    Graph const* psGraph,
    int iX1, int iY1,
    int iX2, int iY2,
    Node const*** paResult
)
/* Calcul le chemin le plus court du noeud de coord X1,Y1 a tous les autres
noeuds et le stocke dans paResult (à désallouer), et renvoi la longueur du
chemin entre (X1,Y1) et (X2,Y2) */
{
    int i;
    Node const** paPath = NULL;
    Node* startingNode = NULL;
    unsigned int* aiLength = NULL;
    int* abE = NULL;
    Node const* Ni = NULL;
    Node const* Nmin = NULL;
    int NbNode;
    int Nb;
    int iNiIndex;
    int iNMinIndex;
    int iResult;
    Link l;
    PriorityQueue pQueue;

    assert (psGraph != NULL);
    assert (iX1 >= 0 && iX1 < psGraph->iWidth);
    assert (iY1 >= 0 && iY1 < psGraph->iHeight);
    assert (iY2 >= 0 && iY2 < psGraph->iHeight);
    assert (iX2 >= 0 && iX2 < psGraph->iWidth);

    startingNode = graphGetNode(psGraph, iX1, iY1);
    assert (startingNode != NULL);

    NbNode = psGraph->iWidth*psGraph->iHeight;
    paPath = (Node const**) malloc(NbNode*sizeof(Node*));
    aiLength = (unsigned int*) malloc(NbNode*sizeof(unsigned int));
    abE = (int*) malloc(NbNode*sizeof(int));
    priorityQueueInit(&pQueue);

    /* Initialisation */
    for (i = 0; i < NbNode; i++)
    /* Pour chaque noeud */
    {
        int Dist = 0;
        Ni = graphGetNodeSequential(psGraph, i);
        abE[i] = 0;
        /* On calcule sa distance au noeud de départ */
        Dist = graphCost(psGraph, startingNode, Ni);
        aiLength[i] = Dist;

        if (Dist == INT_MAX)
        /* Si elle est infinie */
        {
        	/* On ne sait pas y aller */
            paPath[i] = NULL;
        }
        else
        /* Sinon */
        {
        	/* Sinon, on passe par le noeud de depart */
            paPath[i] = startingNode;
        }
        /* On insère dans la file de priorité pour un accès plus rapide au
        noeud le plus proche */
        if (Dist > 0) {priorityQueueInsert(&pQueue, i, Dist);}
    }
    abE[iX1*psGraph->iWidth+iY1] = 1;
    Nb = 1;

    while (Nb < NbNode)
    /* Tant qu'on a pas traités tous les noeuds */
    {
    	/* On récupère le noeud le plus proche via la file de priorité */
        i = priorityQueueTop(&pQueue);
		Nmin = graphGetNodeSequential(psGraph, i);
		iNMinIndex = i;
		priorityQueuePop(&pQueue);


		/* Pour chaque lien actif du noeud courant */


        l = nodeGetLink(Nmin, 'u');
        Ni = linkGetDest(&l);
        if (Ni != NULL)
        {
            iNiIndex = nodeGetX(Ni)*psGraph->iWidth+nodeGetY(Ni);
            if (abE[iNiIndex] == 0)
                /* Si le noeud destination n'a pas deja ete traite */
            {
                if (aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni) <
                        aiLength[iNiIndex])
				/* Si la nouvelle distance est inférieure à l'ancienne */
                {
                	/* On met à jour la distance dans le tableau */
					aiLength[iNiIndex] =
                        aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni);
					/* On met à jour la file de priorité */
					priorityQueueChangePriority(&pQueue,
												iNiIndex,
												aiLength[iNiIndex]);
					/* On met à jour le chemin du départ à ce noeud */
                    paPath[iNiIndex] = Nmin;
                }
            }
        }
        l = nodeGetLink(Nmin, 'r');
        Ni = linkGetDest(&l);
        if (Ni != NULL)
        {
            iNiIndex = nodeGetX(Ni)*psGraph->iWidth+nodeGetY(Ni);
            if (abE[iNiIndex] == 0)
                /* Si le noeud destination n'a pas deja ete traite */
            {
                if (aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni) <
                        aiLength[iNiIndex])
                {
					aiLength[iNiIndex] =
                        aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni);
					priorityQueueChangePriority(&pQueue,
												iNiIndex,
												aiLength[iNiIndex]);
                    paPath[iNiIndex] = Nmin;
                }
            }
        }
        l = nodeGetLink(Nmin, 'd');
        Ni = linkGetDest(&l);
        if (Ni != NULL)
        {
            iNiIndex = nodeGetX(Ni)*psGraph->iWidth+nodeGetY(Ni);
            if (abE[iNiIndex] == 0)
                /* Si le noeud destination n'a pas deja ete traite */
            {
                if (aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni) <
                        aiLength[iNiIndex])
                {
					aiLength[iNiIndex] =
                        aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni);
					priorityQueueChangePriority(&pQueue,
												iNiIndex,
												aiLength[iNiIndex]);
                    paPath[iNiIndex] = Nmin;
                }
            }
        }
        l = nodeGetLink(Nmin, 'l');
        Ni = linkGetDest(&l);
        if (Ni != NULL)
        {
            iNiIndex = nodeGetX(Ni)*psGraph->iWidth+nodeGetY(Ni);
            if (abE[iNiIndex] == 0)
                /* Si le noeud destination n'a pas deja ete traite */
            {
                if (aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni) <
                        aiLength[iNiIndex])
                {
					aiLength[iNiIndex] =
                        aiLength[iNMinIndex]+graphCost(psGraph, Nmin, Ni);
					priorityQueueChangePriority(&pQueue,
												iNiIndex,
												aiLength[iNiIndex]);
                    paPath[iNiIndex] = Nmin;
                }
            }
        }

        abE[iNMinIndex] = 1;
        Nb++;
    }

	/* On stocke les résultats */
	iResult = aiLength[iX2*psGraph->iWidth+iY2];
	*paResult = paPath;

	/* On libère tout */
    free(aiLength);
    aiLength = NULL;
    free(abE);
    abE = NULL;
    priorityQueueRelease(&pQueue);

    return iResult;
}




















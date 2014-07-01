#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "node.h"

struct sGraph
{
	int iWidth;
	int iHeight;

	Node*** Tab;		/* Tableau 2D de pointeurs sur noeuds*/
};
typedef struct sGraph Graph;


/* Fonctions de création/destruction d'un graphe */
Graph* graphCreate (int iWidth, int iHeight);
void graphDestroy (Graph** ppsGraph);

/* Fonction d'allocation/libération d'un graphe */
void graphInit (Graph* psGraph, int iWidth, int iHeight);
void graphRelease (Graph* psGraph);

/* Ajout d'un noeud au graphe */
void graphCreateNode (
					Graph* psGraph,
					int iX, int iY,
					int up, int right, int down, int left
					);
/* Suppression d'un noeud */
void graphDestroyNode (
						Graph* psGraph,
						int iX, int iY
						);

/* Activation d'un lien entre deux noeuds */
void graphActivateLink (
						Graph* psGraph,
						int iX, int iY,
						char cDir, int iValue
						);
/* Désactivation d'un lien entre deux noeuds */
void graphDeactivateLink (
						Graph* psGraph,
						int iX, int iY,
						char cDir
						);

/* Accesseur sur un noeud via ses coordonées*/
Node* graphGetNode (
					const Graph* psGraph,
					int iX, int iY
					);
/* Accesseur sur un noeud via son numéro : iIndex = X*Width+Y */
Node* graphGetNodeSequential (Graph const* psGraph,
							int iIndex);

/* Accesseur */
int graphGetWidth (
				const Graph* psGraph
				);

/* Affichage du graphe */
void graphPrint (const Graph* psGraph);

/* Calcul du cout entre deux noeuds */
int graphCost (Graph const* psGraph, Node const* Nsrc, Node const* Ndest);

/* Calcul du plus court chemin */
unsigned int graphDijkstra (
				Graph const* psGraph,
				int iX1, int iY1,
				int iX2, int iY2,
				Node const*** paPath
				);





























#endif

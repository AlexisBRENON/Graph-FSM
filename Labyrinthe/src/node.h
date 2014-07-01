#ifndef __NODE_H__
#define __NODE_H__

#include "link.h"

/* Structure représentant un noeud du graphe quadrillé */
struct sNode
{
	void const* Data; /* Donnée associée au noeud */

	int X; /* abscisse du noeud */
	int Y; /* ordonnée du noeud */
	Link up; /* Lien vers le haut */
	Link right; /* Lien vers la droite */
	Link down; /* Lien vers le bas */
	Link left; /* Lien vers la gauche */
};
typedef struct sNode Node;

/* Création/Destruction d'un noeud */
Node* nodeCreate (
				void const* pData,
				int iX, int iY,
				Node* pUp, int iUp,
				Node* pRight, int iRight,
				Node* pDown, int iDown,
				Node* pLeft, int iLeft
				);
void nodeDestroy (
				Node** ppN
				);

/* Initialisation/Libération d'un noeud */
void nodeInit (
			Node* pN,
			void const* pData,
			int iX, int iY,
			Node* pUp, int iUp,
			Node* pRight, int iRight,
			Node* pDown, int iDown,
			Node* pLeft, int iLeft
			);
void nodeRelease (
				Node* pN
				);

/* Accesseurs/Mutateurs */
int nodeGetX (Node const* pN);
int nodeGetY (Node const* pN);

void nodeSetData (Node* pN, void* pData);
void const* nodeGetData (Node* pN);

void nodeSetLink (Node* pN, char cLink, Node const* pDest, int iValue);
Link nodeGetLink (Node const* pN, char cLink);

#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "node.h"


Node* nodeCreate (
				void const* pData,
				int iX, int iY,
				Node* pUp, int iUp,
				Node* pRight, int iRight,
				Node* pDown, int iDown,
				Node* pLeft, int iLeft
				)
/* Création et initialisation d'un noeud */
{
	Node* pN = NULL;

	pN = (Node*) malloc(sizeof(Node));

	nodeInit(pN, pData, iX, iY,
			pUp, iUp,
			pRight, iRight,
			pDown, iDown,
			pLeft, iLeft);

	return pN;
}
void nodeDestroy (
				Node** ppN
				)
/* Libération et désalocation d'un noeud */
{
	assert (ppN != NULL);
	assert (*ppN != NULL);

	nodeRelease(*ppN);
	free(*ppN);
	*ppN = NULL;
}

void nodeInit (
			Node* pN,
			void const* pData,
			int iX, int iY,
			Node* pUp, int iUp,
			Node* pRight, int iRight,
			Node* pDown, int iDown,
			Node* pLeft, int iLeft
			)
/* Initialise un noeud */
{
	assert (pN != NULL);
	assert (iX >= 0);
	assert (iY >= 0);

	pN->Data = pData;
	pN->X = iX;
	pN->Y = iY;

	linkInit(&(pN->up));
	linkInit(&(pN->right));
	linkInit(&(pN->down));
	linkInit(&(pN->left));

	linkSetDest(&(pN->up), pUp);
	linkSetDest(&(pN->right), pRight);
	linkSetDest(&(pN->down), pDown);
	linkSetDest(&(pN->left), pLeft);

	linkSetValue(&(pN->up), iUp);
	linkSetValue(&(pN->right), iRight);
	linkSetValue(&(pN->down), iDown);
	linkSetValue(&(pN->left), iLeft);
}
void nodeRelease (
				Node* pN
				)
/* Libère un noeud */
{
	assert(pN != NULL);

	pN->Data = NULL;
	pN->X = -1;
	pN->Y = -1;

	linkRelease(&(pN->up));
	linkRelease(&(pN->right));
	linkRelease(&(pN->down));
	linkRelease(&(pN->left));
}

/* Accesseurs */
int nodeGetX (Node const* pN)
{
	assert (pN != NULL);

	return pN->X;
}
int nodeGetY (Node const* pN)
{
	assert (pN != NULL);

	return pN->Y;
}

/* Accesseur/Mutateur des données */
void nodeSetData (Node* pN, void* pData)
{
	assert (pN != NULL);

	pN->Data = pData;
}
void const* nodeGetData (Node* pN)
{
	assert (pN != NULL);

	return pN->Data;
}

/* Accesseur/mutateur sur les liens */
void nodeSetLink (Node* pN, char cLink, Node const* pDest, int iValue)
{
	assert (pN != NULL);

	switch (cLink)
	{
		case 'u':
			linkSetDest(&(pN->up), pDest);
			linkSetValue(&(pN->up), iValue);
			break;
		case 'r':
			linkSetDest(&(pN->right), pDest);
			linkSetValue(&(pN->right), iValue);
			break;
		case 'd':
			linkSetDest(&(pN->down), pDest);
			linkSetValue(&(pN->down), iValue);
			break;
		case 'l':
			linkSetDest(&(pN->left), pDest);
			linkSetValue(&(pN->left), iValue);
			break;
		default:
			fprintf (stderr,
					"Modification lien impossible, mauvais caractere.\n");
			break;
	}
}
Link nodeGetLink (Node const* pN, char cLink)
{
	assert (pN != NULL);

	switch (cLink)
	{
		case 'u':
			return (pN->up);
			break;
		case 'r':
			return (pN->right);
			break;
		case 'd':
			return (pN->down);
			break;
		case 'l':
			return (pN->left);
			break;
		default:
			fprintf (stderr,
					"Lecture lien impossible, mauvais caractere.\n");
			return (pN->up);
			break;
	}
}
































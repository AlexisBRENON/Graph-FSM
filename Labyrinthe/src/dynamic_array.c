/**
  * @brief Fichier d'implementation du module @em DYNAMIC_ARRAY.
  * Implémente les tableaux dynamiques.
  *
  * @author Alexis BRENON in STELLODY TEAM
  * @file dynamic_array.c
  */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "dynamic_array.h"


/* ********************************************************************* */
/*                                                                       */
/*                 Fonctions relatives à la structure                    */
/*                                                                       */
/* ********************************************************************* */


DynamicArray* dynamicArrayCreate (void)
{
	DynamicArray* pArray = NULL;

	pArray = (DynamicArray*) malloc(sizeof(DynamicArray));

	dynamicArrayInit(pArray);

	return pArray;
}

ArrayError dynamicArrayDestroy (DynamicArray** ppArray)
{
	if (ppArray == NULL || *ppArray == NULL) {return ARRAY_NULL_POINTER;}

	dynamicArrayRelease(*ppArray);
	free(*ppArray); *ppArray = NULL;

	return ARRAY_OK;
}

ArrayError dynamicArrayInit (DynamicArray* pArray)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	pArray->ppFisrtCell = (int*) malloc(10*sizeof(int));
	pArray->iAllocatedSize = 10;
	pArray->iFirstEmptyCell = 0;

	return ARRAY_OK;
}

ArrayError dynamicArrayRelease (DynamicArray* pArray)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	free(pArray->ppFisrtCell); pArray->ppFisrtCell = NULL;
	pArray->iAllocatedSize = 0;
	pArray->iFirstEmptyCell = -1;

	return ARRAY_OK;
}

ArrayError dynamicArraySet (DynamicArray* pArray,
							int iIndex,
							int iValue)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	if (iIndex >= pArray->iFirstEmptyCell) {return ARRAY_INDEX_OVERFLOW;}

	(pArray->ppFisrtCell)[iIndex] = iValue;

	return ARRAY_OK;
}

ArrayError dynamicArrayGet (const DynamicArray* pArray,
							int iIndex,
							int* piValue)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	if (iIndex >= pArray->iFirstEmptyCell) {return ARRAY_INDEX_OVERFLOW;}

	*piValue = (pArray->ppFisrtCell)[iIndex];

	return ARRAY_OK;
}

ArrayError dynamicArrayGetIndex (const DynamicArray* pArray,
								int iValue,
								int* piIndex)
{
	int i;
	int* pPtr = NULL;

	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	for (i=0; i<pArray->iFirstEmptyCell; i++)
	{
		dynamicArrayGet(pArray, i, pPtr);
		if (*pPtr == iValue)
		{
			*piIndex = i;
			i = pArray->iFirstEmptyCell;
		}
	}

	return ARRAY_OK;
}


ArrayError dynamicArrayPush (DynamicArray* pArray,
				int iValue)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	if (pArray->iFirstEmptyCell >= pArray->iAllocatedSize)
	{
		int* piNewFirstCell = NULL;
		int iNewAllocatedSize = (pArray->iAllocatedSize)*2;
		int i = 0;

		piNewFirstCell = (int*) malloc(iNewAllocatedSize*sizeof(int));

		for (i = 0; i < pArray->iFirstEmptyCell; i++)
		{
			piNewFirstCell[i] = (pArray->ppFisrtCell)[i];
		}
		free(pArray->ppFisrtCell); pArray->ppFisrtCell = NULL;

		pArray->ppFisrtCell = piNewFirstCell;
		pArray->iAllocatedSize = iNewAllocatedSize;
	}

	pArray->ppFisrtCell[pArray->iFirstEmptyCell] = iValue;
	pArray->iFirstEmptyCell = pArray->iFirstEmptyCell+1;

	return ARRAY_OK;
}

ArrayError dynamicArrayPop (DynamicArray* pArray)
{
	int iReductionSize = 0;

	if (pArray == NULL) {return ARRAY_NULL_POINTER;}

	pArray->ppFisrtCell[pArray->iFirstEmptyCell-1] = 0;
	pArray->iFirstEmptyCell = pArray->iFirstEmptyCell-1;

	iReductionSize = pArray->iAllocatedSize;
	iReductionSize = iReductionSize*2;
	iReductionSize = iReductionSize/3;

	/*if (pArray->iFirstEmptyCell <= iReductionSize)
	{
		int* ppNewFirstCell = NULL;
		int iNewAllocatedSize = iReductionSize;
		int i = 0;

		ppNewFirstCell = (int*) malloc(iNewAllocatedSize*sizeof(int));

		for (i = 0; i < pArray->iFirstEmptyCell; i++)
		{
			ppNewFirstCell[i] = (pArray->ppFisrtCell)[i];
		}
		free(pArray->ppFisrtCell); pArray->ppFisrtCell = NULL;

		pArray->ppFisrtCell = ppNewFirstCell;
		pArray->iAllocatedSize = iNewAllocatedSize;
	}*/

	return ARRAY_OK;
}

ArrayError dynamicArrayGetSize (const DynamicArray* pArray,
								int* piSize)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}
	if (piSize == NULL) {return ARRAY_BAD_ARGUMENTS;}

	*piSize = pArray->iFirstEmptyCell;

	return ARRAY_OK;
}

ArrayError dynamicArrayGetMaxSize (const DynamicArray* pArray,
								int* piMaxSize)
{
	if (pArray == NULL) {return ARRAY_NULL_POINTER;}
	if (piMaxSize == NULL) {return ARRAY_BAD_ARGUMENTS;}

	*piMaxSize = pArray->iAllocatedSize;

	return ARRAY_OK;
}

ArrayError dynamicArrayRemove (DynamicArray* pArray,
								int iIndex)
{
	int i = 0;
	int iValue;

	if (pArray == NULL) {return ARRAY_NULL_POINTER;}
	if (iIndex > pArray->iFirstEmptyCell) {return ARRAY_INDEX_OVERFLOW;}

	for (i = iIndex; i < pArray->iFirstEmptyCell; i++)
	{
		dynamicArrayGet(pArray, i+1, &iValue);
		dynamicArraySet(pArray, i, iValue);
	}

	dynamicArrayPop(pArray);

	return ARRAY_OK;
}

ArrayError dynamicArrayInsert (DynamicArray* pArray,
							int iIndex,
							int iValue)
{
	int* apTemp = NULL;
	int i, iTempSize;

	if (pArray == NULL) {return ARRAY_NULL_POINTER;}
	if (iIndex > pArray->iFirstEmptyCell) {return ARRAY_INDEX_OVERFLOW;}

	iTempSize = pArray->iFirstEmptyCell-iIndex;
	apTemp = (int*) malloc(iTempSize*sizeof(int));

	for (i = iTempSize-1; i >= 0; i--)
	{
		dynamicArrayGet(pArray, iIndex+i, &(apTemp[i]));
		dynamicArrayPop(pArray);
	}

	dynamicArrayPush(pArray, iValue);

	for (i = 0; i < iTempSize; i++)
	{
		dynamicArrayPush(pArray, apTemp[i]);
	}

	free(apTemp);

	return ARRAY_OK;
}



/* ********************************************************************* */
/*                                                                       */
/*                          Test de regression                           */
/*                                                                       */
/* ********************************************************************* */


int dynamicArrayRegressionTest ()
{
	DynamicArray* pArray = NULL;
	int iTest = 0;
	int i = 0;

	printf("\n\t\t == TEST DYNAMIC_ARRAY == \n\n");

	printf("Création...\n");
	pArray = dynamicArrayCreate();
	assert(pArray != NULL);

	printf("Interrogation taille max...\n");
	assert (dynamicArrayGetMaxSize(pArray, &iTest) == ARRAY_OK);
	assert (iTest == 10);

	printf("Interrogation taille actuelle...\n");
	assert (dynamicArrayGetSize(pArray, &iTest) == ARRAY_OK);
	assert (iTest == 0);

	printf("Insertion...\n");
	for (i = 0; i < 15; i++)
	{
		assert (dynamicArrayPush(pArray, i) == ARRAY_OK);
	}

	printf("Interrogation taille max...\n");
	assert (dynamicArrayGetMaxSize(pArray, &iTest) == ARRAY_OK);
	assert (iTest == 20);

	printf("Interrogation taille actuelle...\n");
	assert (dynamicArrayGetSize(pArray, &iTest) == ARRAY_OK);
	assert (iTest == 15);

	printf("Obtention...\n");
	assert (dynamicArrayGet(pArray, 13, &iTest) == ARRAY_OK);
	assert(iTest == 13);

	printf("Diminution...\n");
	for (i = 15; i > 10; i--)
	{
		assert(dynamicArrayPop(pArray) == ARRAY_OK);
	}
	printf("Interrogation taille actuelle...\n");
	assert(dynamicArrayGetSize(pArray, &iTest) == ARRAY_OK);
	assert(iTest == 10);
	printf("Interrogation taille max...\n");
	assert(dynamicArrayGetMaxSize(pArray, &iTest) == ARRAY_OK);
	assert(iTest == 13);

	printf("Destruction...\n");
	assert(dynamicArrayDestroy(&pArray) == ARRAY_OK);


	printf("\n\t == FIN == \n");
	return EXIT_SUCCESS;
}


#include <stdlib.h>
#include <assert.h>

#include "link.h"

void linkInit(Link* l)
/* Initialise un noeud */
{
	assert (l != NULL);

	l->dest = NULL;
	l->Value = 0;
}
void linkRelease(Link* l)
/* Libère un noeud */
{
	assert (l != NULL);

	l->dest = NULL;
	l->Value = 0;
}

/* Accesseur/Mutateur sur la valeur */
void linkSetValue(Link* l, int iValue)
{
	assert (l != NULL);

	l->Value = iValue;
}
int linkGetValue(const Link* l)
{
	assert (l != NULL);

	return l->Value;
}

/* Accesseur/Mutateur sur la destination */
void linkSetDest(Link* l, const struct sNode* pDest)
{
	assert (l != NULL);

	l->dest = pDest;
}
struct sNode const* linkGetDest(const Link* l)
{
	assert (l != NULL);

	return l->dest;
}

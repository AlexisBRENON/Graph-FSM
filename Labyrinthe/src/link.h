#ifndef __LINK_H__
#define __LINK_H__

struct sNode;

/* Lien orienté, valué */
struct sLink
{
	struct sNode const* dest; /* Noeud de destination */
	int Value; /* Valeur du noeud */
};
typedef struct sLink Link;

/* Fonctions d'initialisation/libération d'un noeud */
void linkInit (Link* l);
void linkRelease (Link* l);

/* Accesseur/Mutateur sur la valeur du lien */
void linkSetValue (Link* l, int iValue);
int linkGetValue (const Link* l);

/* Accesseur/Mutateur sur la destination du lien */
void linkSetDest (Link* l, const struct sNode* pDest);
struct sNode const* linkGetDest (const Link* l);

#endif

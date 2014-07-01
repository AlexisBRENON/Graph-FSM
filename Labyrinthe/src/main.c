#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "graph.h"
#include "dynamic_array.h"

int main()
{
    int i, j;
    int iWidth = 8;
    int iHeight = 8;
    char dir;
    int iX1, iY1, iX2, iY2;
    int iLength;
    Node const** aPath = NULL;
    Node const* N = NULL;

    Graph Laby;
    graphInit(&Laby, iWidth, iHeight);

    srand(time(NULL));

    for (i = 0; i < iWidth; i++)
    {
        for (j = 0; j < iHeight; j++)
        {
        	graphCreateNode(&Laby, i, j, 1, 1, 1, 1);
        }
    }

	printf("Desactivation de certains liens.\n");
	for (i = 0; i < 2*iWidth*iHeight; i++)
	{
		iX1 = rand()%iWidth;
		iY1 = rand()%iHeight;
		dir = rand()%4;
		switch (dir)
		{
			case 0:
				graphDeactivateLink(&Laby, iX1, iY1, 'u');
				break;
			case 1:
				graphDeactivateLink(&Laby, iX1, iY1, 'r');
				break;
			case 2:
				graphDeactivateLink(&Laby, iX1, iY1, 'd');
				break;
			case 3:
				graphDeactivateLink(&Laby, iX1, iY1, 'l');
				break;
		}
	}
	graphPrint(&Laby);

    printf("Quel chemin voulez-vous calculer? x1,y1 x2,y2\n");
    while (scanf("%d,%d %d,%d", &iX1, &iY1, &iX2, &iY2) == 4)
    {
        iLength = (int) graphDijkstra(&Laby, iX1, iY1, iX2, iY2, &aPath);
        printf("Ditance : %d\n\n", iLength);
        if (iLength != INT_MAX)
        {
            i = iX2*iWidth+iY2;
            printf("(%d,%d) ", iX2, iY2);
            do
            {
                N = aPath[i];
                printf("<- (%d,%d) ", nodeGetX(N), nodeGetY(N));
                i = nodeGetX(N)*iWidth + nodeGetY(N);
            }
            while (i != iX1*iWidth+iY1);
            printf("\n\n");
        }
        else
        {
            printf("Noeud inateignable...\n\n");
        }

		free(aPath);
        printf("Quel chemin voulez-vous calculer? x1,y1 x2,y2\n");
    }

    graphRelease(&Laby);
    return 0;
}

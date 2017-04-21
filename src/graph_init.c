

/************************************************************************************
    Implementation of generic Graph Data Structure (Undirected Version)
    Initialization and destruction functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "graph.h"
#include <bst.h>
#include <list.h>
#include <dlist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_INPUT_CHAR			200
#define MAX_NAME_CHAR			50






int graph_init(Graph *g, int (*cmp_v) (const void *va, const void *vb),
                            int (*cmp_e) (const void *ea, const void *eb),
                            void (*destroy_vertex) (void *vertex),
                            void (*destroy_vertex_data) (void *vData),
                            void (*destroy_edge) (void *edge),
                            void (*destroy_edge_data) (void *eData))
{
    
    if (g == 0 || cmp_v == 0 || cmp_e == 0) {
        return -1;
    }
    
    bst_init(&g->treeVertexData, cmp_v, destroy_vertex, destroy_vertex_data);
    bst_init(&g->treeVertexUndirectedEdge, cmp_v, 0, 0);
    
    bst_init(&g->treeUndirectedEdgeData, cmp_e, destroy_edge, destroy_edge_data);
    bst_init(&g->treeUndirectedEdgeSource1, cmp_e, 0, 0);
    bst_init(&g->treeUndirectedEdgeSource2, cmp_e, 0, 0);
    
    g->cmp_vertex = cmp_v;
    g->cmp_edge = cmp_e;
    
    return 0;
}





void graph_destroy(Graph *g)
{
    
    DList *edgeList;
    List edgeListAll;
    ListElem *elem;
    int opRes;
    
    if (g == 0) {
        return;
    }
    
    list_init(&edgeListAll, 0);
    opRes = bst_listElements(&g->treeVertexUndirectedEdge, &edgeListAll);
    
    if (opRes == 0) {
        elem = list_head(&edgeListAll);
        while (elem != 0) {
            edgeList = (DList *) list_data(elem);
            dlist_destroy(edgeList);
            free((void *) edgeList);
            elem = list_next(elem);
        }
    }
    list_destroy(&edgeListAll);
    
    bst_destroy(&g->treeVertexUndirectedEdge);
    bst_destroy(&g->treeUndirectedEdgeSource1);
    bst_destroy(&g->treeUndirectedEdgeSource2);
    
    bst_destroy(&g->treeVertexData);
    bst_destroy(&g->treeUndirectedEdgeData);
    
    g->cmp_vertex = 0;
    g->cmp_edge = 0;
    return;
}





int graph_readGraphFromText(Graph *g, FILE *pFile) {
	
	char strInput[MAX_INPUT_CHAR];
	char strVertex[MAX_NAME_CHAR], strEdge[MAX_NAME_CHAR];
	char strVertex1[MAX_NAME_CHAR], strVertex2[MAX_NAME_CHAR];
	char *pVertex, *pEdge;
	unsigned int tVertex, tEdge;
	unsigned int i;
	unsigned int sLen;
	int findVertex1, findVertex2;
	char *pVertex1, *pVertex2;
	
	if (g == 0 || pFile == 0) {
		return -1;
	}
	
	fgets(strInput, MAX_INPUT_CHAR, pFile);
	sscanf(strInput, "%u %u", &tVertex, &tEdge);
	graph_init(g, strcmp, strcmp, free, 0, free, 0);
	/* printf("** tVertex (%u) tEdge (%u)\n", tVertex, tEdge); */
	
	for (i = 0; i < tVertex; i++) {
		fgets(strVertex, MAX_NAME_CHAR, pFile);
		sLen = strlen(strVertex);
		*(strVertex + sLen - 1) = 0;
		pVertex = (char *) malloc(sLen);
		strcpy(pVertex, (const char *) strVertex);
		graph_insertVertex(g, pVertex, 0);
	}
	
	for (i = 0; i < tEdge; i++) {
		fgets(strInput, MAX_INPUT_CHAR, pFile);
		sscanf(strInput, "%s %s %s", strEdge, strVertex1, strVertex2);
		
		findVertex1 = graph_getVertex(g, (const void *) strVertex1, (void **) &pVertex1, 0);
		findVertex2 = graph_getVertex(g, (const void *) strVertex2, (void **) &pVertex2, 0);
		
		if (findVertex1 == 1 && findVertex2 == 1) {
			pEdge = (char *) malloc(strlen(strEdge) + 1);
			strcpy(pEdge, strEdge);
			graph_insertEdge(g, (const void *) pEdge, 0, (void *) pVertex1, (void *) pVertex2);
		}
	}
	return 0;
}




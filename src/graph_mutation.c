

/************************************************************************************
    Implementation of generic Graph Data Structure (Undirected Version)
    Mutation (insert, remove) functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "graph.h"
#include <bst.h>
#include <dlist.h>
#include <stdlib.h>






int graph_insertEdge(Graph *g, const void *edge, const void *data, void *vertex1, void *vertex2)
{
    
    BisTree *vertexEdgeTree;
    BisTree *edgeDataTree;
    BisTree *edgeEnd1Tree, *edgeEnd2Tree;
    DList *inciEdgeList1, *inciEdgeList2;
    DListElem *elem1, *elem2;
    int findEdge, findVertex1, findVertex2;
    int areVertexPresent;
    int areAdjacent;
	void *pRealVertex1, *pRealVertex2;
    
    vertexEdgeTree = (BisTree*) &g->treeVertexUndirectedEdge;
    edgeDataTree = (BisTree*) &g->treeUndirectedEdgeData;
    edgeEnd1Tree = (BisTree*) &g->treeUndirectedEdgeSource1;
    edgeEnd2Tree = (BisTree*) &g->treeUndirectedEdgeSource2;
    
    findEdge = graph_getEdge((const Graph*) g, edge, 0, 0);
    findVertex1 = graph_getVertex((const Graph*) g, (const void*) vertex1, &pRealVertex1, 0);
    findVertex2 = graph_getVertex((const Graph*) g, (const void*) vertex2, &pRealVertex2, 0);
    areVertexPresent = findVertex1 & findVertex2;
    if (areVertexPresent != 1)
        return -1;
        
    areAdjacent = graph_areAdjacent((const Graph*) g, (const void*) vertex1, (const void*) vertex2);
    if (areAdjacent == 1)
        return -2;
        
    if (findEdge == 1)
        return -3;
        
    bst_findElement(vertexEdgeTree, (void*) vertex1, (void**) &inciEdgeList1);
    bst_findElement(vertexEdgeTree, (void*) vertex2, (void**) &inciEdgeList2);
        
    bst_insert(edgeDataTree, (void*) edge, (void*) data);
    bst_insert(edgeEnd1Tree, (void*) edge, (void*) pRealVertex1);
    bst_insert(edgeEnd2Tree, (void*) edge, (void*) pRealVertex2);
    
    elem1 = dlist_tail(inciEdgeList1);
    elem2 = dlist_tail(inciEdgeList2);
    dlist_ins_next(inciEdgeList1, elem1, (const void*) edge);
    dlist_ins_next(inciEdgeList2, elem2, (const void*) edge);
    
    return 0;
}





int graph_removeEdge(Graph *g, const void *edge, void **pRealEdge, void **edgeData)
{
    
    BisTree *edgeDataTree;
    BisTree *edgeEnd1Tree, *edgeEnd2Tree;
    BisTree *vertexEdgeTree;
    void *vertex1, *vertex2;
    void *tmpEdge, *tmpEdgeData;
    DList *inciEdgeList1, *inciEdgeList2;
    DListElem *elem;
    int findEdge;
    
    edgeDataTree = (BisTree*) &g->treeUndirectedEdgeData;
    edgeEnd1Tree = (BisTree*) &g->treeUndirectedEdgeSource1;
    edgeEnd2Tree = (BisTree*) &g->treeUndirectedEdgeSource2;
    vertexEdgeTree = (BisTree*) &g->treeVertexUndirectedEdge;
    
    findEdge = graph_getEdge((const Graph*) g, edge, pRealEdge, 0);
    if (findEdge == 0)
        return -1;
    
    bst_remove(edgeDataTree, (void*) edge, 0, &tmpEdgeData);
    bst_remove(edgeEnd1Tree, (void*) edge, 0, &vertex1);
    bst_remove(edgeEnd2Tree, (void*) edge, 0, &vertex2);
    
    bst_findElement(vertexEdgeTree, vertex1, (void**) &inciEdgeList1);
    bst_findElement(vertexEdgeTree, vertex2, (void**) &inciEdgeList2);
    
    elem = dlist_head(inciEdgeList1);
    while (elem != 0 && dlist_data(elem) != edge)
        elem = dlist_next(elem);
    dlist_remove(inciEdgeList1, elem, &tmpEdge);
    
    elem = dlist_head(inciEdgeList2);
    while (elem != 0 && dlist_data(elem) != edge)
        elem = dlist_next(elem);
    dlist_remove(inciEdgeList2, elem, &tmpEdge);
    
    if (edgeData != 0)
        *edgeData = tmpEdgeData;
    
    return 0;
}





int graph_insertVertex(Graph *g, const void *vertex, const void *data)
{
    
    BisTree *vertexDataTree;
    BisTree *vertexEdgeTree;
    DList *edgeList;
    int findVertex;
    
    vertexDataTree = (BisTree*) &g->treeVertexData;
    vertexEdgeTree = (BisTree*) &g->treeVertexUndirectedEdge;
    
    findVertex = graph_getVertex((const Graph*) g, vertex, 0, 0);
    if (findVertex == 1)
        return -1;

    edgeList = (DList*) malloc(sizeof(DList));
    dlist_init(edgeList, 0);
    
    bst_insert(vertexDataTree, (void*) vertex, (void*) data);
    bst_insert(vertexEdgeTree, (void*) vertex, (void*) edgeList);
    
    return 0;
}





int graph_removeVertex(Graph *g, const void *vertex,
								void **pRealVertex, void **vertexData,
								DList *inciEdgeList, DList *inciEdgeDataList)
{
    
    BisTree *vertexDataTree;
    BisTree *vertexEdgeTree;
    DList edgeList, *actualEdgeList;
    DListElem *elem;
	DListElem *elem_out_edge, *elem_out_edge_data;
    void *anEdge, *anEdgeData;
    int findVertex;
    
    vertexDataTree = (BisTree*) &g->treeVertexData;
    vertexEdgeTree = (BisTree*) &g->treeVertexUndirectedEdge;
    
    findVertex = graph_getVertex((const Graph*) g, vertex, 0, 0);
    if (findVertex == 0)
        return -1;

    dlist_init(&edgeList, 0);
    graph_incidentEdges((const Graph*) g, vertex, &edgeList);
	
	if (inciEdgeList != 0) {
		elem_out_edge = dlist_tail(inciEdgeList);
	}
	if (inciEdgeDataList != 0) {
		elem_out_edge_data = dlist_tail(inciEdgeDataList);
	}
    
    elem = dlist_head(&edgeList);
    while (elem != 0) {
        anEdge = dlist_data(elem);
        graph_removeEdge(g, (const void*) anEdge, 0, &anEdgeData);
        elem = dlist_next(elem);
		
		if (inciEdgeList != 0) {
			dlist_ins_next(inciEdgeList, elem_out_edge, (const void *) anEdge);
			elem_out_edge = dlist_tail(inciEdgeList);
		}
		if (inciEdgeDataList != 0) {
			dlist_ins_next(inciEdgeDataList, elem_out_edge_data, (const void *) anEdgeData);
			elem_out_edge_data = dlist_tail(inciEdgeDataList);
		}
    }
    
    dlist_destroy(&edgeList);
    bst_remove(vertexDataTree, (void*) vertex, pRealVertex, vertexData);
    bst_remove(vertexEdgeTree, (void*) vertex, 0,			(void**) &actualEdgeList);
    dlist_destroy(actualEdgeList);
    free((void*) actualEdgeList);
    
    return 0;
}




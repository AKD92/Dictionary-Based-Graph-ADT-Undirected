

#include "graph.h"
#include <stdlib.h>
#include <BST.h>
#include <dlist.h>



int graph_insertEdge(Graph *g, const void *edge, const void *data, void *vertex1, void *vertex2)
{
	
	BST *vertexEdgeTree;
	BST *edgeDataTree;
	BST *edgeEnd1Tree, *edgeEnd2Tree;
	DList *inciEdgeVertex1, *inciEdgeVertex2;
	DListElem *elem1, *elem2;
	int findEdge, findVertex1, findVertex2;
	int areVertexPresent;
	int areAdjacent;
	
	vertexEdgeTree = (BST*) &g->treeVertexUndirectedEdge;
	edgeDataTree = (BST*) &g->treeUndirectedEdgeData;
	edgeEnd1Tree = (BST*) &g->treeUndirectedEdgeSource1;
	edgeEnd2Tree = (BST*) &g->treeUndirectedEdgeSource2;
	
	findEdge = graph_isEdgePresent((const Graph*) g, edge);
	findVertex1 = graph_isVertexPresent((const Graph*) g, (const void*) vertex1);
	findVertex2 = graph_isVertexPresent((const Graph*) g, (const void*) vertex2);
	
	areVertexPresent = findVertex1 & findVertex2;
	if (areVertexPresent != 1)
		return -1;
		
	areAdjacent = graph_areAdjacent((const Graph*) g, (const void*) vertex1, (const void*) vertex2);
	if (areAdjacent == 1)
		return -2;

	if (findEdge == 1)
		return -3;

	bst_findElement(vertexEdgeTree, (void*) vertex1, (void**) &inciEdgeVertex1);
	bst_findElement(vertexEdgeTree, (void*) vertex2, (void**) &inciEdgeVertex2);
		
	bst_insert(edgeDataTree, (void*) edge, (void*) data);
	bst_insert(edgeEnd1Tree, (void*) edge, (void*) vertex1);
	bst_insert(edgeEnd2Tree, (void*) edge, (void*) vertex2);
	
	elem1 = dlist_tail(inciEdgeVertex1);
	elem2 = dlist_tail(inciEdgeVertex2);
	dlist_ins_next(inciEdgeVertex1, elem1, (const void*) edge);
	dlist_ins_next(inciEdgeVertex2, elem2, (const void*) edge);
	
	return 0;
}


int graph_removeEdge(Graph *g, const void *edge, void **edgeData)
{
	
	BST *edgeDataTree;
	BST *edgeEnd1Tree, *edgeEnd2Tree;
	BST *vertexEdgeTree;
	void *vertex1, *vertex2;
	void *tmpEdge, *tmpEdgeData;
	DList *inciEdgeVertex1, *inciEdgeVertex2;
	DListElem *elem;
	int findEdge;
	
	edgeDataTree = (BST*) &g->treeUndirectedEdgeData;
	edgeEnd1Tree = (BST*) &g->treeUndirectedEdgeSource1;
	edgeEnd2Tree = (BST*) &g->treeUndirectedEdgeSource2;
	vertexEdgeTree = (BST*) &g->treeVertexUndirectedEdge;
	
	findEdge = graph_isEdgePresent((const Graph*) g, edge);
	if (findEdge == 0)
		return -1;
	
	bst_remove(edgeDataTree, (void*) edge, &tmpEdgeData);
	bst_remove(edgeEnd1Tree, (void*) edge, &vertex1);
	bst_remove(edgeEnd2Tree, (void*) edge, &vertex2);
	
	bst_findElement(vertexEdgeTree, vertex1, (void**) &inciEdgeVertex1);
	bst_findElement(vertexEdgeTree, vertex2, (void**) &inciEdgeVertex2);
	
	elem = dlist_head(inciEdgeVertex1);
	while (elem != 0 && dlist_data(elem) != edge)
		elem = dlist_next(elem);
	dlist_remove(inciEdgeVertex1, elem, &tmpEdge);
	
	elem = dlist_head(inciEdgeVertex2);
	while (elem != 0 && dlist_data(elem) != edge)
		elem = dlist_next(elem);
	dlist_remove(inciEdgeVertex2, elem, &tmpEdge);
	
	*edgeData = tmpEdgeData;
	
	return 0;
}


int graph_insertVertex(Graph *g, const void *vertex, const void *data)
{
	
	BST *vertexDataTree;
	BST *vertexEdgeTree;
	DList *edgeList;
	int findVertex;
	
	vertexDataTree = (BST*) &g->treeVertexData;
	vertexEdgeTree = (BST*) &g->treeVertexUndirectedEdge;
	
	findVertex = graph_isVertexPresent((const Graph*) g, vertex);
	if (findVertex == 1)
		return -1;

	edgeList = (DList*) malloc(sizeof(DList));
	dlist_init(edgeList, 0);
	
	bst_insert(vertexDataTree, (void*) vertex, (void*) data);
	bst_insert(vertexEdgeTree, (void*) vertex, (void*) edgeList);
	
	return 0;
}


int graph_removeVertex(Graph *g, const void *vertex, void **vertexData)
{
	
	BST *vertexDataTree;
	BST *vertexEdgeTree;
	DList edgeList, *actualEdgeList;
	DListElem *elem;
	void *anEdge, *tmpEdgeData, *tmpVertexData;
	int findVertex;
	
	vertexDataTree = (BST*) &g->treeVertexData;
	vertexEdgeTree = (BST*) &g->treeVertexUndirectedEdge;
	
	findVertex = graph_isVertexPresent((const Graph*) g, vertex);
	if (findVertex == 0)
		return -1;

	dlist_init(&edgeList, 0);
	graph_incidentEdges((const Graph*) g, vertex, &edgeList);
	
	elem = dlist_head(&edgeList);
	while (elem != 0) {
		anEdge = dlist_data(elem);
		graph_removeEdge(g, (const void*) anEdge, &tmpEdgeData);
		elem = dlist_next(elem);
	}
	
	dlist_destroy(&edgeList);
	bst_remove(vertexDataTree, (void*) vertex, &tmpVertexData);
	bst_remove(vertexEdgeTree, (void*) vertex, (void**) &actualEdgeList);
	dlist_destroy(actualEdgeList);
	free((void*) actualEdgeList);
	
	*vertexData = tmpVertexData;
	
	return 0;
}



#include "graph.h"
#include <BST.h>
#include <list.h>
#include <dlist.h>



unsigned int graph_numVertices(const Graph *g) {

	unsigned int verCount;
	verCount = bst_size(&g->treeVertexData);
	return verCount;
}


unsigned int graph_numEdges(const Graph *g) {

	unsigned int edgeCount;
	edgeCount = bst_size(&g->treeUndirectedEdgeData);
	return edgeCount;
}


int graph_verticesToList(const Graph *g, DList *vertexOutList)
{

	List vertexList;
	BST *vertexTree;
	ListElem *elem;
	DListElem *dElemLast;
	void *aVertex;

	vertexTree = (BST*) &g->treeVertexData;
	bst_keys(vertexTree, &vertexList);

	dlist_init(vertexOutList, 0);
	elem = list_head(&vertexList);
	dElemLast = dlist_tail(vertexOutList);

	while (elem != 0) {
		aVertex = list_data(elem);
		dlist_ins_next(vertexOutList, dElemLast, (const void*) aVertex);
		elem = list_next(elem);
		dElemLast = dlist_tail(vertexOutList);
	}

	list_destroy(&vertexList);

	return 0;
}


int graph_edgesToList(const Graph *g, DList *edgeOutList)
{

	List edgeList;
	BST *edgeTree;
	ListElem *elem;
	DListElem *dElemLast;
	void *anEdge;

	edgeTree = (BST*) &g->treeUndirectedEdgeData;
	bst_keys(edgeTree, &edgeList);

	dlist_init(edgeOutList, 0);
	elem = list_head(&edgeList);
	dElemLast = dlist_tail(edgeOutList);

	while (elem != 0) {
		anEdge = list_data(elem);
		dlist_ins_next(edgeOutList, dElemLast, (const void*) anEdge);
		elem = list_next(elem);
		dElemLast = dlist_tail(edgeOutList);
	}

	list_destroy(&edgeList);

	return 0;
}


int graph_isVertexPresent(const Graph *g, const void *vertex)
{
	
	BNode *verNode;
	BST *vertexTree;
	int isPresent;
	
	vertexTree = (BST*) &g->treeVertexData;
	verNode = bst_treeSearch(vertexTree, (void*) vertex, bst_root(vertexTree));
	isPresent = bst_isInternal(verNode) == 1 ? 1 : 0;
	
	return isPresent;
}


int graph_isEdgePresent(const Graph *g, const void *edge)
{
	
	BNode *edgeNode;
	BST *edgeTree;
	int isPresent;
	
	edgeTree = (BST*) &g->treeUndirectedEdgeData;
	edgeNode = bst_treeSearch(edgeTree, (void*) edge, bst_root(edgeTree));
	isPresent = bst_isInternal(edgeNode) == 1 ? 1 : 0;
	
	return isPresent;
}


int graph_degreeOfVertex(const Graph *g, const void *vertex, unsigned int *degree)
{

	BST *vertexTree;
	DList *edgeList;
	int findOpResult;

	vertexTree = (BST*) &g->treeVertexUndirectedEdge;
	findOpResult = bst_findElement(vertexTree, (void*) vertex, (void**) &edgeList);

	if (findOpResult == -1)
		return -1;
	else
		*degree = dlist_size(edgeList);

	return 0;
}


int graph_endVertices(const Graph *g, const void *edge, void **vertex1, void **vertex2)
{

	BST *edgeTree1, *edgeTree2;
	void *tmpVertex1, *tmpVertex2;
	int findOpResult1, findOpResult2;

	edgeTree1 = (BST*) &g->treeUndirectedEdgeSource1;
	edgeTree2 = (BST*) &g->treeUndirectedEdgeSource2;

	findOpResult1 = bst_findElement(edgeTree1, (void*) edge, &tmpVertex1);
	findOpResult2 = bst_findElement(edgeTree2, (void*) edge, &tmpVertex2);

	if (findOpResult1 == -1 || findOpResult2 == -1) {
		return -1;
	}
	else {
		*vertex1 = tmpVertex1;
		*vertex2 = tmpVertex2;
	}

	return 0;
}


int graph_oppositeVertex(const Graph *g, const void *edge, const void *vOne, void **vAnother)
{

	void *vertex1, *vertex2;
	BST *edgeTree1, *edgeTree2;
	int findOpResult1, findOpResult2;

	edgeTree1 = (BST*) &g->treeUndirectedEdgeSource1;
	edgeTree2 = (BST*) &g->treeUndirectedEdgeSource2;

	findOpResult1 = bst_findElement(edgeTree1, (void*) edge, &vertex1);
	findOpResult2 = bst_findElement(edgeTree2, (void*) edge, &vertex2);

	if (findOpResult1 == -1 || findOpResult2 == -1) {
		return -1;
	}
	else {
		if (g->cmp_vertex(vertex1, vOne) == 0)
			*vAnother = vertex2;
		else if (g->cmp_vertex(vertex2, vOne) == 0)
			*vAnother = vertex1;
		else
			return -2;
	}

	return 0;
}


int graph_incidentEdges(const Graph *g, const void *vertex, DList *incidentEdgeList)
{

	BST *vertexTree;
	DList *tmpEdgeList;
	DListElem *elem;
	DListElem *dElemLast;
	void *anEdge;
	int findOpResult;
	
	vertexTree = (BST*) &g->treeVertexUndirectedEdge;
	findOpResult = bst_findElement(vertexTree, (void*) vertex, (void**) &tmpEdgeList);
	
	if (findOpResult == -1) {
		return -1;
	}
	else {
		dlist_init(incidentEdgeList, 0);
		elem = dlist_head(tmpEdgeList);
		dElemLast = dlist_tail(incidentEdgeList);
		
		while (elem != 0) {
			anEdge = dlist_data(elem);
			dlist_ins_next(incidentEdgeList, dElemLast, (const void*) anEdge);
			elem = dlist_next(elem);
			dElemLast = dlist_tail(incidentEdgeList);
		}
	}

	return 0;
}



int graph_incidentEdge(const Graph *g, const void *vertex1, const void *vertex2, void **edge)
{
	
	BST *vertexEdgeTree;
	DList *vertex1Edges, *vertex2Edges;
	DListElem *elem;
	void *edge1, *edge2, *anEdge, *aVertex;
	int findOpResult1, findOpResult2, cmpVertexVal, cmpEdgeVal;
	int findBoth;
	
	edge1 = edge2 = 0;

	vertexEdgeTree = (BST*) &g->treeVertexUndirectedEdge;
	findOpResult1 = bst_findElement(vertexEdgeTree, (void*) vertex1, (void**) &vertex1Edges);
	findOpResult2 = bst_findElement(vertexEdgeTree, (void*) vertex2, (void**) &vertex2Edges);
	
	findBoth = findOpResult1 == -1 || findOpResult2 == -1 ? 0 : 1;
	if (findBoth == 0)
		return -1;
		
	elem = dlist_head(vertex1Edges);
	while (elem != 0) {
		
		anEdge = dlist_data(elem);
		graph_oppositeVertex(g, (const void*) anEdge, vertex1, &aVertex);
		cmpVertexVal = g->cmp_vertex((const void*) aVertex, (const void*) vertex2);
		if (cmpVertexVal == 0) {
			edge1 = anEdge;
			break;
		}
		elem = dlist_next(elem);
	}
	
	elem = dlist_head(vertex2Edges);
	while (elem != 0) {

		anEdge = dlist_data(elem);
		graph_oppositeVertex(g, (const void*) anEdge, vertex2, &aVertex);
		cmpVertexVal = g->cmp_vertex((const void*) aVertex, (const void*) vertex1);
		if (cmpVertexVal == 0) {
			edge2 = anEdge;
			break;
		}
		elem = dlist_next(elem);
	}
	
	cmpEdgeVal = g->cmp_edge((const void*) edge1, (const void*) edge2);
	if (cmpEdgeVal != 0)
		return -1;
	else
		*edge = edge1;
	
	return 0;
}



int graph_adjacentVertices(const Graph *g, const void *vertex, DList *adjacentVertexList)
{
	
	DList incidentEdges;
	DListElem *elemEdge, *elemVertex;
	void *tmpEdge, *tmpVertex;
	int inciEdgeOpResult;
	
	inciEdgeOpResult = graph_incidentEdges(g, vertex, &incidentEdges);
	
	if (inciEdgeOpResult == -1) {
		return -1;
	}
	else {
		dlist_init(adjacentVertexList, 0);
		elemEdge = dlist_head(&incidentEdges);
		elemVertex = dlist_tail(adjacentVertexList);
		
		while (elemEdge != 0) {
			tmpEdge = dlist_data(elemEdge);
			graph_oppositeVertex(g, (const void*) tmpEdge, (const void*) vertex, &tmpVertex);
			dlist_ins_next(adjacentVertexList, elemVertex, (const void*) tmpVertex);
			elemEdge = dlist_next(elemEdge);
			elemVertex = dlist_tail(adjacentVertexList);
		}
		
		dlist_destroy(&incidentEdges);
	}
	
	return 0;
}


int graph_areAdjacent(const Graph *g, const void *vertex1, const void *vertex2)
{
	
	DList adjacentVertices;
	DListElem *elem;
	void *aVertex;
	int adjVerticesOpResult;
	int finishResult;
	
	finishResult = 0;
	adjVerticesOpResult = graph_adjacentVertices(g, vertex1, &adjacentVertices);
	
	if (adjVerticesOpResult == -1) {
		return -1;
	}
	else {
		
		elem = dlist_head(&adjacentVertices);
		while (elem != 0) {
			aVertex = dlist_data(elem);
			if (aVertex == vertex2) {
				finishResult = 1;
				break;
			}
			elem = dlist_next(elem);
		}
	}
	
	dlist_destroy(&adjacentVertices);
	
	return finishResult;
}

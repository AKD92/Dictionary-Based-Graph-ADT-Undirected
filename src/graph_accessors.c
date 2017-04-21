

/************************************************************************************
    Implementation of generic Graph Data Structure (Undirected Version)
    Accessor and query functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "graph.h"
#include <bst.h>
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
    BisTree *vertexTree;
    ListElem *elem;
    DListElem *elem_out;
    void *aVertex;

    vertexTree = (BisTree*) &g->treeVertexData;
	if (bst_size(vertexTree) == 0) {
		return -1;
	}
	
    list_init(&vertexList, 0);
    bst_listKeys(vertexTree, &vertexList);
    
    elem = list_head(&vertexList);
    elem_out = dlist_tail(vertexOutList);

    while (elem != 0) {
        aVertex = list_data(elem);
        dlist_ins_next(vertexOutList, elem_out, (const void*) aVertex);
        elem = list_next(elem);
        elem_out = dlist_tail(vertexOutList);
    }
    list_destroy(&vertexList);

    return 0;
}





int graph_edgesToList(const Graph *g, DList *edgeOutList)
{

    List edgeList;
    BisTree *edgeTree;
    ListElem *elem;
    DListElem *elem_out;
    void *anEdge;

    edgeTree = (BisTree*) &g->treeUndirectedEdgeData;
	if (bst_size(edgeTree) == 0) {
		return -1;
	}
	
    list_init(&edgeList, 0);
    bst_listKeys(edgeTree, &edgeList);
    
    elem = list_head(&edgeList);
    elem_out = dlist_tail(edgeOutList);

    while (elem != 0) {
        anEdge = list_data(elem);
        dlist_ins_next(edgeOutList, elem_out, (const void*) anEdge);
        elem = list_next(elem);
        elem_out = dlist_tail(edgeOutList);
    }
    list_destroy(&edgeList);

    return 0;
}





int graph_getVertex(const Graph *g, const void *vertex, void **pRealVertex, void **pVertexData)
{
    
    BNode *verNode;
    BisTree *vertexTree;
    int isPresent;
    
    vertexTree = (BisTree*) &g->treeVertexData;
    verNode = bst_binarySearch(vertexTree, (void*) vertex, bst_root(vertexTree));
    isPresent = bst_isInternal(verNode) == 1 ? 1 : 0;
	
	if (isPresent == 1) {
		if (pRealVertex != 0) {
			*pRealVertex = verNode->pKey;
		}
		if (pVertexData != 0) {
			*pVertexData = verNode->pElement;
		}
	}
    
    return isPresent;
}





int graph_getEdge(const Graph *g, const void *edge, void **pRealEdge, void **pEdgeData)
{
    
    BNode *edgeNode;
    BisTree *edgeTree;
    int isPresent;
    
    edgeTree = (BisTree*) &g->treeUndirectedEdgeData;
    edgeNode = bst_binarySearch(edgeTree, (void*) edge, bst_root(edgeTree));
    isPresent = bst_isInternal(edgeNode) == 1 ? 1 : 0;
	
	if (isPresent == 1) {
		if (pRealEdge != 0) {
			*pRealEdge = edgeNode->pKey;
		}
		if (pEdgeData != 0) {
			*pEdgeData = edgeNode->pElement;
		}
	}
    
    return isPresent;
}





int graph_degreeOfVertex(const Graph *g, const void *vertex, unsigned int *degree)
{

    BisTree *vertexTree;
    DList *edgeList;
    int findOpResult;

    vertexTree = (BisTree*) &g->treeVertexUndirectedEdge;
    findOpResult = bst_search(vertexTree, (void*) vertex, 0, (void**) &edgeList);

    if (findOpResult == -1)
        return -1;
    else
        *degree = dlist_size(edgeList);

    return 0;
}





int graph_endVertices(const Graph *g, const void *edge, void **vertex1, void **vertex2)
{

    BisTree *edgeTree1, *edgeTree2;
    void *tmpVertex1, *tmpVertex2;
    int findOpResult1, findOpResult2;

    edgeTree1 = (BisTree*) &g->treeUndirectedEdgeSource1;
    edgeTree2 = (BisTree*) &g->treeUndirectedEdgeSource2;

    findOpResult1 = bst_search(edgeTree1, (void*) edge, 0, &tmpVertex1);
    findOpResult2 = bst_search(edgeTree2, (void*) edge, 0, &tmpVertex2);

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
    BisTree *edgeTree1, *edgeTree2;
    int findOpResult1, findOpResult2;

    edgeTree1 = (BisTree*) &g->treeUndirectedEdgeSource1;
    edgeTree2 = (BisTree*) &g->treeUndirectedEdgeSource2;

    findOpResult1 = bst_search(edgeTree1, (void*) edge, 0, &vertex1);
    findOpResult2 = bst_search(edgeTree2, (void*) edge, 0, &vertex2);

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

    BisTree *vertexTree;
    DList *realEdgeList;
    DListElem *elem;
    DListElem *elem_out;
    void *anEdge;
    int findOpResult;
    
    vertexTree = (BisTree*) &g->treeVertexUndirectedEdge;
    findOpResult = bst_search(vertexTree, (void*) vertex, 0, (void**) &realEdgeList);
    
    if (findOpResult == -1) {
        return -1;
    }
    else {
        elem = dlist_head(realEdgeList);
        elem_out = dlist_tail(incidentEdgeList);
        
        while (elem != 0) {
            anEdge = dlist_data(elem);
            dlist_ins_next(incidentEdgeList, elem_out, (const void*) anEdge);
            elem = dlist_next(elem);
            elem_out = dlist_tail(incidentEdgeList);
        }
    }

    return 0;
}





int graph_incidentEdge(const Graph *g, const void *vertex1, const void *vertex2, void **edge)
{
    
    BisTree *vertexEdgeTree;
    DList *vertex1Edges, *vertex2Edges;
    DListElem *elem;
    void *edge1, *edge2, *anEdge, *aVertex;
    int findOpResult1, findOpResult2, cmpVertexVal, cmpEdgeVal;
    
    edge1 = edge2 = 0;

    vertexEdgeTree = (BisTree*) &g->treeVertexUndirectedEdge;
    findOpResult1 = bst_search(vertexEdgeTree, (void*) vertex1, 0, (void**) &vertex1Edges);
    findOpResult2 = bst_search(vertexEdgeTree, (void*) vertex2, 0, (void**) &vertex2Edges);
    
    if (findOpResult1 == -1 || findOpResult2 == -1)
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
        return -2;
    else
        if (edge != 0)
			*edge = edge1;
    
    return 0;
}





int graph_adjacentVertices(const Graph *g, const void *vertex, DList *adjacentVertexList)
{
    
    DList incidentEdges;
    DListElem *elemEdge, *elemVertex;
    void *tmpEdge, *tmpVertex;
    int inciOpResult;
	int retValue;
    
	retValue = 0;
	dlist_init(&incidentEdges, 0);
    inciOpResult = graph_incidentEdges(g, vertex, &incidentEdges);
    
    if (inciOpResult == -1) {
        retValue = -1;
		goto END;
    }
	
    else {
        elemEdge = dlist_head(&incidentEdges);
        elemVertex = dlist_tail(adjacentVertexList);
        
        while (elemEdge != 0) {
            tmpEdge = dlist_data(elemEdge);
            graph_oppositeVertex(g, (const void*) tmpEdge, (const void*) vertex, &tmpVertex);
            dlist_ins_next(adjacentVertexList, elemVertex, (const void*) tmpVertex);
            elemEdge = dlist_next(elemEdge);
            elemVertex = dlist_tail(adjacentVertexList);
        }
    }
	
	END:
	dlist_destroy(&incidentEdges);
    return retValue;
}





int graph_areAdjacent(const Graph *g, const void *vertex1, const void *vertex2)
{
    
    DList adjacentVertices;
    DListElem *elem;
    void *aVertex;
    int adjVerticesOpResult;
    int retValue;
    
    retValue = 0;
	dlist_init(&adjacentVertices, 0);
    adjVerticesOpResult = graph_adjacentVertices(g, vertex1, &adjacentVertices);
    
    if (adjVerticesOpResult == -1) {
        retValue = -1;
		goto END;
    }
	
    else {
        elem = dlist_head(&adjacentVertices);
        while (elem != 0) {
            aVertex = dlist_data(elem);
            if (aVertex == vertex2) {
                retValue = 1;
                break;
            }
            elem = dlist_next(elem);
        }
    }
	
	END:
    dlist_destroy(&adjacentVertices);
    return retValue;
}



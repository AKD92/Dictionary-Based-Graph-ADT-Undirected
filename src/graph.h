

#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H

#include <BST.h>
#include <dlist.h>




struct Graph_ {
	
	BST treeVertexData;
	BST treeVertexUndirectedEdge;
	
	BST treeUndirectedEdgeData;
	BST treeUndirectedEdgeSource1;
	BST treeUndirectedEdgeSource2;
	
	int (*cmp_vertex) (const void *va, const void* vb);
	int (*cmp_edge) (const void *ea, const void *eb);
	
};


typedef struct Graph_ Graph;








/*
 *********************************************************************
 *********************************************************************
 **********************						**************************
 *********************  CREATION FUNCTIONS  **************************
 **********************						**************************
 *********************************************************************
 *********************************************************************
*/





/*
 *  Initializes a graph g with two comparison functions
 *  to identify and compare dfferent vertices and edges.
 *
 *  Parameter:
 *      g       :   The Graph being initalized
 *		cmp_v   :   Comparison function of vertices
 *		cmp_e   :   Comparison function of edges
 *
 *  Returns 0 for successful (always)
*/
int graph_init(Graph *g, int (*cmp_v) (const void *va, const void *vb),
							int (*cmp_e) (const void *ea, const void *eb));
							
							

/*
 *  Destroys a graph g. Deallocated all the memrory resources also.
 *
 *  Parameter:
 *      g       : The graph structure being destroyes
 *
 *  Returns 0 for successful (always)
*/
int graph_destroy(Graph *g);







/*
 *********************************************************************
 *********************************************************************
 **********************						**************************
 *********************  ACCESSOR FUNCTIONS  **************************
 **********************						**************************
 *********************************************************************
 *********************************************************************
*/




/*
 * Returns the number of vertices in the graph g
 *
 * Parameter:
 * 		g		: the graph
*/
unsigned int graph_numVertices(const Graph *g);



/*
 * Retuns the number of undirected edges in the graph g
*/
unsigned int graph_numEdges(const Graph *g);



/*
 * Returns the degree of the graph g itself
*/
unsigned int graph_degree(const Graph *g);




/*
 * Copy all the vertex pointers to the Linkedlist vertexOutList
 * vertedOutList will be allocated by the caller, but
 * initialized by this function. This list must be destroyes
 * by the caller also.
 *
 * Returns 0 for successful
*/
int graph_verticesToList(const Graph *g, DList *vertexOutList);




/*
 * Copy all the edge pointers to the Linkedlist edgeOutList
 * edgeOutList will be allocated by the caller, but
 * initialized by this function. This list must be destroyes
 * by the caller also.
 *
 * Returns 0 for successful
*/
int graph_edgesToList(const Graph *g, DList *edgeOutList);




/*
 * Query if the specified vertex exists to this graph or not.
 *
 * Returns 1 if present, 0 otherwise.
*/
int graph_isVertexPresent(const Graph *g, const void *vertex);




/*
 * Query if the specified edge exists to this graph or not.
 *
 * Returns 1 if present, 0 otherwise.
*/
int graph_isEdgePresent(const Graph *g, const void *edge);




/*
 * Computes the degree of a vertex to a given graph
 *
 * Returns the degree as a positive integer, -1 if vertex does not exist.
*/
int graph_degreeOfVertex(const Graph *g, const void *vertex, unsigned int *degree);




/*
 * Acquire the pointers of two endpoints of an undirected edge.
 *
 * Returns 0 for successful, -1 if any of the vertex is absent.
*/
int graph_endVertices(const Graph *g, const void *edge, void **vertex1, void **vertex2);





/*
 * Query for the other endpoint of an edge by specifying one endpoint.
 *
 * Returns 0 for successful, -1 if any of the vertex is missing for the edge,
 *      or -2 if the vertex provided in vOne is not a valid vertex
*/
int graph_oppositeVertex(const Graph *g, const void *edge, const void *vOne, void **vAnother);




/*
 * Inserts the pointers of all the incident undirected edges of a vertex
 * to the linked list provided in incidentEdgeList
 *
 * Linked list incidentEdgeList must be created & destroyed by caller.
 * This function only initializes the list.
 *
 * Returns 0 for successful, -1 if vertex is not valid to this graph g.
*/
int graph_incidentEdges(const Graph *g, const void *vertex, DList *incidentEdgeList);


int graph_incidentEdge(const Graph *g, const void *vertex1, const void *vertex2, void **edge);



/*
 * Inserts the pointers of all the adjacent vertices of a vertex
 * to the linked list provided in adjacentVertexList.
 *
 * Linked list adjacentVertexList must be created & destroyed by caller.
 * This function only initializes the list.
 *
 * Returns 0 for successful, -1 if vertex is not valid to this graph g.
*/
int graph_adjacentVertices(const Graph *g, const void *vertex, DList *adjacentVertexList);





/*
 * Check to see if two vertices are adjacent
 *
 * Returns 0 if not adjacent, 1 if adjacent, -1 if any vertex is not valid to this graph g
*/
int graph_areAdjacent(const Graph *g, const void *vertex1, const void *vertex2);









/*
 *********************************************************************
 *********************************************************************
 **********************						**************************
 *********************  MUTATION FUNCTIONS  **************************
 **********************						**************************
 *********************************************************************
 *********************************************************************
*/


/*
 * Inserts a new undirected edge ponted by edge to this graph g.
 * The two vertex in the parameter must be present in g already.
 * data is the pointer to the data being associated with this edge.
 *
 * Returns
 *		 0 for successful insertion
 *      -1 if any vertex is not present in g
 *      -2 if the vertices are already adjacent
 *      -3 if an undirected edge pointed by this edge is already available
 *      in the graph g
*/
int graph_insertEdge(Graph *g, const void *edge, const void *data, void *vertex1, void *vertex2);




/*
 * Inserts a new vertex to this graph g.
 * The vertex to be inserted must not be present in g already.
 * data is the pointer to the data being associated with this vertex.
 *
 * Returns
 *		 0 for successful insertion
 *      -1 if the vertex is already present in g
*/
int graph_insertVertex(Graph *g, const void *vertex, const void *data);




/*
 * Remove an undirected edge from this graph g, which is already present in g.
 * Variable edgeData will point to the data associated by this edge being removed.
 *
 *
 * Returns
 *		 0 for successful removal
 *      -1 if the edge is not present in g
*/
int graph_removeEdge(Graph *g, const void *edge, void **edgeData);




/*
 * Remove a vertex from this graph g, which is already present in g.
 * Variable vertexData will point to the data associated by this vertex being removed.
 *
 *
 * Returns
 *		 0 for successful removal
 *      -1 if the vertex is not present in g
*/
int graph_removeVertex(Graph *g, const void *vertex, void **vertexData);





#endif

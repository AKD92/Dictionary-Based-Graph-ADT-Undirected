

/************************************************************************************
    Program Interface of generic Graph Data Structure (Undirected Version)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/







#ifndef GRAPH_ADT_H
#define GRAPH_ADT_H



#include <bst.h>
#include <dlist.h>
#include <stdio.h>





/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************      DATA STRUCTURES      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



struct Graph_ {
    
    BisTree treeVertexData;
    BisTree treeVertexUndirectedEdge;
    
    BisTree treeUndirectedEdgeData;
    BisTree treeUndirectedEdgeSource1;
    BisTree treeUndirectedEdgeSource2;
    
    int (*cmp_vertex) (const void *va, const void* vb);
    int (*cmp_edge) (const void *ea, const void *eb);
    
};
typedef struct Graph_ Graph;







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************   INIT & DEST FUNCTIONS   **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/


/*
 *  Initializes a graph g with two comparison functions
 *  to identify and compare dfferent vertices and edges.
 *
 *  Parameter:
 *      g           :   The Graph being initalized
 *      cmp_v       :   Comparison function of vertices
 *      cmp_e       :   Comparison function of edges
 *
 *  Returns
 *      0 for successful
 *      -1 if g is NULL or cmp_v is NULL or cmp_e is NULL
*/
int graph_init(Graph *g, int (*cmp_v) (const void *va, const void *vb),
                            int (*cmp_e) (const void *ea, const void *eb),
                            void (*destroy_vertex) (void *vertex),
                            void (*destroy_vertex_data) (void *vData),
                            void (*destroy_edge) (void *edge),
                            void (*destroy_edge_data) (void *eData));
                            
                            

/*
 *  Destroys a graph g. Deallocated all the memrory resources also.
 *
 *  Parameter:
 *      g           : The graph structure being destroyes
 *
*/
void graph_destroy(Graph *g);





/*
 *  Read text data frpm pFile and initialize the specified graph object
 *  According to the data read
 *
 *  Parameter:
 *      g           :   The Graph being created, it must not be initialized
 *      pFile       :   Pointer to a FILE object which contains graph data
 *
 *  Returns
 *      0 for successful
 *      -1 pFile or g is NULL
*/
int graph_readGraphFromText(Graph *g, FILE *pFile);








/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************      QUERY FUNCTIONS      **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 * Returns the number of vertices in the graph g
 *
 * Parameter:
 *      g           : the graph
 *
 * Returns:
 *      n >= 0, n is the number of vertices
*/
unsigned int graph_numVertices(const Graph *g);





/*
 * Returns the number of undirected edges in the graph g
 *
 * Parameter:
 *      g           : the graph
 *
 * Returns:
 *      n >= 0, n is the number of undirected edges
*/
unsigned int graph_numEdges(const Graph *g);





/*
 * Returns the degree of the graph g
 *
 * Parameter:
 *      g           : the graph
 *
 * Returns:
 *      n >= 0, n is the degree of the graph
*/
unsigned int graph_degree(const Graph *g);





/*
 * Copy all the pointers of vertices to the Doubly Linkedlist vertexOutList
 *
 * vertedOutList will be allocated and initialized by the caller
 * This doubly linkedlist must be destroyes by the caller also
 *
 * Parameters:
 *      g               : the graph
 *      vertexOutList   : a pointer to the doubly linked list
 *
 * Returns:
 *      0 for successful
 *      -1 if no vertex exists to the graph
*/
int graph_verticesToList(const Graph *g, DList *vertexOutList);





/*
 * Copy all the pointers of undirected edges of the graph
 * to the Doubly Linkedlist edgeOutList
 *
 * edgeOutList will be allocated and initialized by the caller
 * This doubly linkedlist must be destroyes by the caller also
 *
 * Parameters:
 *      g               : the graph
 *      edgeOutList     : a pointer to the doubly linked list
 *
 * Returns:
 *      0 for successful
 *      -1 if no edge exists to the graph
*/
int graph_edgesToList(const Graph *g, DList *edgeOutList);





/*
 * Query if the specified vertex exists to this graph or not
 *
 * Parameters:
 *      g:          : the graph
 *      vertex      : the vertex to query about
 *
 * Returns:
 *      1 if exists
 *      0 if does not exist
*/
int graph_getVertex(const Graph *g, const void *vertex, void **pRealVertex, void **pVertexData);





/*
 * Query if the specified edge exists to this graph or not.
 *
 * Parameters:
 *      g:          : the graph
 *      edge        : the edge to query about
 *
 * Returns:
 *      1 if exists
 *      0 if does not exists
*/
int graph_getEdge(const Graph *g, const void *edge, void **pRealEdge, void **pEdgeData);





/*
 * Computes the degree of a vertex to a given graph
 *
 * Parameters:
 *      g:          : the graph
 *      vertex      : the vertex for which the degree will be computed
 *      degree      : pointer to an unsigned integer on which the computed
 *                    will be stored
 *
 * Returns:
 *      0 if the degree is computed and stored successfully to the memory
 *      -1 if the specified vertex does not exist to the specified graph
*/
int graph_degreeOfVertex(const Graph *g, const void *vertex, unsigned int *degree);





/*
 * Retrives the pointers of two endpoints of an undirected edge
 *
 * Parameters:
 *      g           : the graph
 *      edge        : the edge in question
 *      vertex1     : pointer to a pointer variable where the pointer of
 *                    one endpoint vertexof the edge will be stored
 *      vertex2     : pointer to a pointer variable where the pointer of
 *                    other endpoint of the edge will be stored
 *
 * Returns:
 *      0 for successful
 *      -1 if the specified edge does not exist on the specified graph
*/
int graph_endVertices(const Graph *g, const void *edge, void **vertex1, void **vertex2);





/*
 * Retrives the pointer to the other endpoint vertex of an edge
 *
 * Parameters:
 *      g           : the graph
 *      edge        : the edge in question
 *      vOne        : pointer to a vertex which is present on graph g
 *      vertex2     : pointer to a pointer variable where the pointer of
 *                    other endpoint of the edge will be stored
 *
 * Returns:
 *      0 for successful
 *      -1 if the specified edge does not exist on the specified graph
 *      -2 if the specified edge exists but it is not an incident edge of the vertex vOne
*/
int graph_oppositeVertex(const Graph *g, const void *edge, const void *vOne, void **vAnother);





/*
 * Copies the pointers of all the incident undirected edges of a vertex
 * to the doubly linked list provided by incidentEdgeList
 *
 * Linked list incidentEdgeList must be created, initialized & destroyed by caller
 *
 * Parameters:
 *      g                   : the graph
 *      vertex              : pointer to a vertex
 *      incidentEdgeList    : pointer to a doubly linkedlist to which the incident edges will be inserted
 *
 * Returns:
 *      0 if successful
 *      -1 if vertex does not exist on this graph g
*/
int graph_incidentEdges(const Graph *g, const void *vertex, DList *incidentEdgeList);





/*
 * Retrives the incident edge (if present) between two adjacent vertices
 *
 * Parameter:
 *      g           : the graph
 *      vertex1     : pointer to a vertex
 *      vertex2     : pointer to another vertex which is adjacent to vertex1
 *      edge        : pointer to a pointer variable where the pointer of the
 *                    incident edge will be stored
 *
 * Returns:
 *      0 if successful
 *      -1 if any of the specified vertices does not exist on this graph g
 *      -2 if the specified edge is not incident between vertex1 and vertex2
*/
int graph_incidentEdge(const Graph *g, const void *vertex1, const void *vertex2, void **edge);





/*
 * Copies the pointers of all the adjacent vertices of a vertex
 * to the doubly linked list provided by adjacentVertexList
 *
 * Linked list adjacentVertexList must be created, initialized & destroyed by caller
 *
 * Parameters:
 *      g                   : the graph
 *      vertex              : pointer to a vertex in question
 *      adjacentVertexList  : pointer to a doubly linkedlist where the pointers of
 *                            adjacent vertices will be inserted
 *
 * Returns:
 *      0 if successful
 *      -1 if vertex does not exist on graph g
*/
int graph_adjacentVertices(const Graph *g, const void *vertex, DList *adjacentVertexList);





/*
 * Check to see if two vertices are adjacent
 *
 * Parameters:
 *      g           : the graph
 *      vertex1     : pointer to a vertex
 *      vertex2     : pointer to another vertex
 *
 * Returns:
 *      0 if vertex1 and vertex2 are not adjacent
 *      1 if vertex1 and vertex2 are adjacent
 *      -1 if any of the specified vertices does not exist on graph g
*/
int graph_areAdjacent(const Graph *g, const void *vertex1, const void *vertex2);







/**********************************************************************************************/
/*********************************                           **********************************/
/*********************************     MUTATION FUNCTIONS    **********************************/
/*********************************                           **********************************/
/**********************************************************************************************/



/*
 * Inserts a new undirected edge ponted by edge to this graph g
 * The two vertex in the parameter must be present in g already
 * data is the pointer to the data being associated with this edge
 *
 * Parameters:
 *      g           : the graph
 *      edge        : pointer to an edge which will be inserted
 *      data        : pointer to any data object which is associated with this edge (optional)
 *      vertex1     : pointer to a vertex to which the specified edge is incident
 *      vertex2     : pointer to another vertex to which the specified edge is incident
 *
 * Returns:
 *       0 for successful insertion
 *      -1 if any vertex is not present in g
 *      -2 if the vertices are already adjacent
 *      -3 if an undirected edge pointed by this edge is already available on graph g
*/
int graph_insertEdge(Graph *g, const void *edge, const void *data, void *vertex1, void *vertex2);





/*
 * Inserts a new vertex to this graph g
 * The vertex to be inserted must not be present in g already
 * data is the pointer to the data being associated with this vertex
 *
 * Parameters:
 *      g           : the graph
 *      edge        : pointer to a vertex which will be inserted
 *      data        : pointer to any data object which is associated with this vertex (optional)
 *
 * Returns:
 *       0 for successful insertion
 *      -1 if the vertex is already present in g
*/
int graph_insertVertex(Graph *g, const void *vertex, const void *data);





/*
 * Remove an undirected edge from this graph g, which is already present in g
 * Variable edgeData will point to the data associated by this edge being removed
 *
 * Parameters:
 *      g           : the graph
 *      edge        : pointer to an edge which will be removed
 *      edgeData    : pointer to a pointer variable which will point
 *                    to the associated data object of the removed edge
 *
 * Returns:
 *       0 for successful removal
 *      -1 if the edge is not present in g
*/
int graph_removeEdge(Graph *g, const void *edge, void **pRealEdge, void **edgeData);





/*
 * Remove a vertex from this graph g, which is already present in g
 * Variable vertexData will point to the data associated by this vertex being removed
 *
 * Parameters:
 *      g           : the graph
 *      vertex      : pointer to a vertex which will be removed
 *      vertexData  : pointer to a pointer variable which will point
 *                    to the associated data object of the removed vertex
 *
 * Returns:
 *       0 for successful removal
 *      -1 if the vertex is not present in g
*/
int graph_removeVertex(Graph *g, const void *vertex,
                                void **pRealVertex, void **vertexData,
                                DList *inciEdgeList, DList *inciEdgeDataList);







#endif

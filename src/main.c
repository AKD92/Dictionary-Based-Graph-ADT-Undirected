

#include "graph.h"
#include <dlist.h>
#include <stdio.h>
#include <string.h>


int main(void);
int cmp_char(const void *c1, const void *c2);
void printList(DList *list);
void graph_print(Graph *g);




int main(void) {
	
	Graph g;
	DList list;
	int opRes;
	char *v1, *v2, *v3, *v4, *v5;
	char *e1, *e2, *e3;
	FILE *pFile;
	
	void *remEdgeData;
	
	v1 = "Vertex 1";
	v2 = "Vertex 2";
	v3 = "Vertex 3";
	v4 = "Vertex 4";
	v5 = "Vertex 5";
	e1 = "Edge 1";
	e2 = "Edge 2";
	e3 = "Edge 3";
	
	graph_init(&g, cmp_char, cmp_char, 0, 0, 0, 0);
	dlist_init(&list, 0);
	
	opRes = graph_insertVertex(&g, (const void*) v1, 0);
	printf("Inserting vertex %s, result %d\n", v1, opRes);
	opRes = graph_insertVertex(&g, (const void*) v2, 0);
	printf("Inserting vertex %s, result %d\n", v2, opRes);
	opRes = graph_insertVertex(&g, (const void*) v3, 0);
	printf("Inserting vertex %s, result %d\n", v3, opRes);
	opRes = graph_insertVertex(&g, (const void*) v3, 0);
	printf("Inserting vertex %s, result %d\n", v3, opRes);
	opRes = graph_insertVertex(&g, (const void*) v4, 0);
	printf("Inserting vertex %s, result %d\n", v4, opRes);
	opRes = graph_insertVertex(&g, (const void*) v5, 0);
	printf("Inserting vertex %s, result %d\n", v5, opRes);
	
	opRes = graph_insertEdge(&g, (const void*) e1, 0, v1, v2);
	printf("Inserting edge %s, result %d\n", e1, opRes);
	opRes = graph_insertEdge(&g, (const void*) e2, 0, v2, v3);
	printf("Inserting edge %s, result %d\n", e2, opRes);
	opRes = graph_insertEdge(&g, (const void*) e3, (void *) "String data E3", v3, v1);
	printf("Inserting edge %s, result %d\n", e3, opRes);
	opRes = graph_insertEdge(&g, (const void*) e3, 0, v4, v4);
	printf("Inserting edge %s, result %d\n\n", e3, opRes);
	
	printf("Priting Graph:\n");
	graph_print(&g);
	
	opRes = graph_getVertex(&g, (const void *) "Vertex 3", 0, 0);
	printf("IsVertexPresent %s? %d\n", "Vertex 3", opRes);
	opRes = graph_getVertex(&g, (const void *) "V5", 0, 0);
	printf("IsVertexPresent %s? %d\n", "V5", opRes);
	
	opRes = graph_getEdge(&g, (const void *) "Edge 2", 0, 0);
	printf("IsEdgePresent %s? %d\n", "Edge 2", opRes);
	opRes = graph_getEdge(&g, (const void *) "Edge 102", 0, 0);
	printf("IsEdgePresent %s? %d\n", "Edge 102", opRes);
	
	
	printf("Removing edge %s\n", e3);
	opRes = graph_removeEdge(&g, (const void *) e3, 0, &remEdgeData);
	printf("Remove edge %s, result %d, dataPointer %p, data: %s\n",
        e3, opRes, remEdgeData, (char *) remEdgeData);
	
	printf("Removing edge %s\n", e3);
	opRes = graph_removeEdge(&g, (const void *) e3, 0, &remEdgeData);
	printf("Remove edge %s, result %d, dataPointer %p\n", e3, opRes, remEdgeData);
	
	printf("Removing edge %s\n", e1);
	opRes = graph_removeEdge(&g, (const void *) e1, 0, &remEdgeData);
	printf("Remove edge %s, result %d, dataPointer %p\n", e1, opRes, remEdgeData);
	
	dlist_init(&list, 0);
	printf("Incident edges of V1:\n");
	graph_incidentEdges(&g, (const void*) v1, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	printf("Incident edges of V2:\n");
	graph_incidentEdges(&g, (const void*) v2, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	printf("Incident edges of V3:\n");
	graph_incidentEdges(&g, (const void*) v3, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	printf("Adjacent vertices of V1:\n");
	graph_adjacentVertices(&g, (const void*) v1, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	printf("Adjacent vertices of V2:\n");
	graph_adjacentVertices(&g, (const void*) v2, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	printf("Adjacent vertices of V3:\n");
	graph_adjacentVertices(&g, (const void*) v3, &list);
	printList(&list);
	dlist_destroy(&list);
	
	printf("\nPrinting Graph\n");
	graph_print(&g);
	
	printf("Removing vertex %s\n", v1);
	opRes = graph_removeVertex(&g, (const void *) v1, 0, &remEdgeData, 0, 0);
	printf("Remove vertex %s, result %d, dataPointer %p\n", v1, opRes, remEdgeData);
	
	printf("\nPrinting Graph\n");
	graph_print(&g);
	
	printf("Removing vertex %s\n", v3);
	opRes = graph_removeVertex(&g, (const void *) v3, 0, &remEdgeData, 0, 0);
	printf("Remove vertex %s, result %d, dataPointer %p\n", v3, opRes, remEdgeData);
	
	printf("\nPrinting Graph\n");
	graph_print(&g);
	
	graph_destroy(&g);
	
	printf("\nReading graph from file : input.txt\n");
	pFile = fopen("input.txt", "r");
	if (pFile == 0) {
        printf("File not exist\n");
        goto END;
	}
	graph_readGraphFromText(&g, pFile);
	printf("Read successful\n");
	fclose(pFile);
	
	printf("\nPrinting Read Graph\n");
	graph_print(&g);
	
	
	
	graph_destroy(&g);
	
	END:
	return 0;
}




int cmp_char(const void *ca, const void *cb) {
	
	return strcmp((char*) ca, (char*) cb);
}


void printList(DList *list) {
	
	DListElem *elem;
	char *frmt = "%s, ";
	elem = dlist_head(list);
	
	while (elem != 0) {
		printf(frmt, (char*) dlist_data(elem));
		elem = dlist_next(elem);
	}
	printf("\n");
	
	return;
}


void graph_print(Graph *g) {
	
	DList objList;
	DList vertexList;
	DListElem *elem, *elem2;
	DList inciEdge, adjVertex;
	char *strVertex, *strEdge;
	char *strAdj;

	printf("%u Vertices : %u Edges\n", graph_numVertices(g), graph_numEdges(g));
	
	dlist_init(&objList, 0);
	graph_verticesToList(g, &objList);
	printf("Vertices: ");
	printList(&objList);
	dlist_destroy(&objList);
	
	dlist_init(&objList, 0);
	graph_edgesToList(g, &objList);
	printf("Edges: ");
	printList(&objList);
	dlist_destroy(&objList);
	
	dlist_init(&vertexList, 0);
	graph_verticesToList(g, &vertexList);
	
	elem = dlist_head(&vertexList);
	while (elem != 0) {
        strVertex = (char *) dlist_data(elem);
        printf("%s\n", strVertex);
        
        dlist_init(&inciEdge, 0);
        graph_incidentEdges(g, (const void *) strVertex, &inciEdge);
        elem2 = dlist_head(&inciEdge);
        printf("Incident edges: ");
        while (elem2 != 0) {
            strEdge = (char *) dlist_data(elem2);
            printf("%s, ", strEdge);
            elem2 = dlist_next(elem2);
        }
        printf("\n");
        dlist_destroy(&inciEdge);
        
        dlist_init(&adjVertex, 0);
        graph_adjacentVertices(g, (const void *) strVertex, &adjVertex);
        printf("Adjacent Vertices:\n");
        elem2 = dlist_head(&adjVertex);
        
        while (elem2 != 0) {
            strAdj = (char *) dlist_data(elem2);
            graph_incidentEdge(g, (const void *) strVertex, (const void *) strAdj, (void **) &strEdge);
            printf("%s by %s\n", strAdj, strEdge);
            elem2 = dlist_next(elem2);
        }
        printf("\n");
        dlist_destroy(&adjVertex);
        elem = dlist_next(elem);
	}
	
	dlist_destroy(&vertexList);
	printf("\n");
	return;
}



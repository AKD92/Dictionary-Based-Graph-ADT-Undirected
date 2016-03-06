

#include "graph.h"
#include <dlist.h>
#include <stdio.h>
#include <string.h>


int main(void);

int cmp_char(const void *c1, const void *c2);

void printList(DList *list);


int main(void) {
	
	Graph g;
	DList list;
	int opRes;
	char *v1, *v2, *v3;
	char *e1, *e2, *e3;
	
	v1 = "Vertex 1";
	v2 = "vertex 2";
	v3 = "Vertex 3";
	e1 = "Edge 1";
	e2 = "Edge 2";
	e3 = "Edge 3";
	
	graph_init(&g, cmp_char, cmp_char);
	dlist_init(&list, 0);
	
	opRes = graph_insertVertex(&g, (const void*) v1, 0);
	printf("Inserting vertex %s, result %d\n", v1, opRes);
	opRes = graph_insertVertex(&g, (const void*) v2, 0);
	printf("Inserting vertex %s, result %d\n", v2, opRes);
	opRes = graph_insertVertex(&g, (const void*) v3, 0);
	printf("Inserting vertex %s, result %d\n", v2, opRes);
	
	opRes = graph_insertEdge(&g, (const void*) e1, 0, v1, v2);
	printf("Inserting edge %s, result %d\n", e1, opRes);
	opRes = graph_insertEdge(&g, (const void*) e2, 0, v2, v3);
	printf("Inserting edge %s, result %d\n", e2, opRes);
	opRes = graph_insertEdge(&g, (const void*) e3, 0, v3, v1);
	printf("Inserting edge %s, result %d\n", e3, opRes);
	
	dlist_init(&list, 0);
	graph_incidentEdges(&g, (const void*) v1, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	graph_incidentEdges(&g, (const void*) v2, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	graph_incidentEdges(&g, (const void*) v3, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	graph_adjacentVertices(&g, (const void*) v1, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	graph_adjacentVertices(&g, (const void*) v2, &list);
	printList(&list);
	dlist_destroy(&list);
	
	dlist_init(&list, 0);
	graph_adjacentVertices(&g, (const void*) v3, &list);
	printList(&list);
	dlist_destroy(&list);
	
	graph_destroy(&g);
	
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
	
	DList vertice;
	DList edge;

	printf("Number of vertces: %d\n", graph_numVertices(g));
	printf("Number of edges: %d\n", graph_numEdges(g));
	
	dlist_init(&vertice, 0);
	graph_verticesToList(g, &vertice);
	dlist_init(&edge, 0);
	graph_edgesToList(g, &edge);
	
	printf("Vertices: ");
	printList(&vertice);
	printf("Edges: ");
	printList(&edge);
	dlist_destroy(&vertice);
	dlist_destroy(&edge);
	
	return;
}

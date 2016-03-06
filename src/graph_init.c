

#include "graph.h"
#include <BST.h>



int graph_init(Graph *g, int (*cmp_v) (const void *va, const void *vb),
							int (*cmp_e) (const void *ea, const void *eb))
{

	bst_init(&g->treeVertexData, cmp_v);
	bst_init(&g->treeVertexUndirectedEdge, cmp_v);
	
	g->treeVertexData.destroy_key = 0;
	g->treeVertexData.destroy_data = 0;
	g->treeVertexUndirectedEdge.destroy_key = 0;
	g->treeVertexUndirectedEdge.destroy_data = 0;
	

	bst_init(&g->treeUndirectedEdgeData, cmp_e);
	bst_init(&g->treeUndirectedEdgeSource1, cmp_e);
	bst_init(&g->treeUndirectedEdgeSource2, cmp_e);
	
	g->treeUndirectedEdgeData.destroy_key = 0;
	g->treeUndirectedEdgeData.destroy_data = 0;
	g->treeUndirectedEdgeSource1.destroy_key = 0;
	g->treeUndirectedEdgeSource1.destroy_data = 0;
	g->treeUndirectedEdgeSource2.destroy_key = 0;
	g->treeUndirectedEdgeSource2.destroy_data = 0;

	g->cmp_vertex = cmp_v;
	g->cmp_edge = cmp_e;

	return 0;
}


int graph_destroy(Graph *g)
{

	bst_destroy(&g->treeVertexData);
	bst_destroy(&g->treeVertexUndirectedEdge);

	bst_destroy(&g->treeUndirectedEdgeData);
	bst_destroy(&g->treeUndirectedEdgeSource1);
	bst_destroy(&g->treeUndirectedEdgeSource2);

	g->cmp_vertex = 0;
	g->cmp_edge = 0;

	return 0;
}


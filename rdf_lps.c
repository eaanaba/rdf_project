#include "rdf_lps.h"

void decomposing(rdf_graph G)
{
	
}

void decompose(rdf_graph G, rdf_graph S, rdf_node_set V)
{
	// obtengo el primer nodo
	rdf_node v1 = V->value;
	
	//if(S == NULL && suc != NULL)
	//	S = V
}

rdf_node_set successors(rdf_graph G, rdf_node_set V)
{
	rdf_node_set suc = rdf_node_set_new();
	rdf_node_set aux = V;
}
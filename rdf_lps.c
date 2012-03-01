#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_graph.h"
#include "rdf_lps.h"

void decomposing(rdf_graph G)
{
	
}

rdf_graph decompose(rdf_graph G, rdf_graph Smax, rdf_node_set V)
{
	// obtengo los sucesores
	rdf_node_set suc = successors(G, V->value);
	print_successors(suc);
	
	//if(rdf_graph_isempty(Smax) && suc != NULL)
	//	rdf_node_set_add_node(Smax->V, V->value);
	//else if(!rdf_graph_isempty(Smax) && suc != NULL)
	//	printf("hola\n");

}

rdf_node_set successors(rdf_graph G, rdf_node v1)
{
	
}

void print_successors(rdf_node_set V)
{
	rdf_node_set aux = V;
	
	if(V->value = NULL)
	{
		printf("Successors vacio!\n");
		return;
	}

	while(aux != NULL)
	{
		printf("contenido: %s\n", aux->value->value.string);
		aux = aux->next;
	}
}
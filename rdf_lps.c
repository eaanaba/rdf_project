#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_graph.h"
#include "rdf_lps.h"

void decomposing(rdf_graph G)
{
	
}

rdf_graph decompose(rdf_graph G, rdf_graph Smax)
{
	// lista de grafos
	rdf_node_set V = G->V;

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
	rdf_node auxnode;
	rdf_node_set suc;

	suc = rdf_node_set_new();
	auxnode = rdf_edge_set_get_pair(G->E, v1);

	if(auxnode == NULL)
		return NULL;

	if(suc->value == NULL)
		suc->value = auxnode;

	while(auxnode)
	{
		while(suc->next)
			suc = suc->next;

		rdf_node_set nuevo = rdf_node_set_new();
		suc->next = nuevo;
		nuevo->value = auxnode;
		auxnode = rdf_edge_set_get_pair(G->E, auxnode);
	}

	return suc;
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
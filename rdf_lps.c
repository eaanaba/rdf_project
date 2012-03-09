#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_graph.h"
#include "rdf_lps.h"

int buscarn(rdf_database db, rdf_graph G, int inicio, int fin)
{
	rdf_database aux = db;
	int flag = 0;

	while(aux != NULL)
	{
		if(aux->n >= inicio && aux->n <= inicio )
			if(lps(G, aux->G))
				flag = 1;
		aux = aux->next;
	}

	return flag;
}

int buscar(rdf_database db, rdf_graph G)
{
	rdf_database aux = db;
	int flag = 0;

	while(aux != NULL)
	{
		if(lps(G, aux->G))
			flag = 1;
		aux = aux->next;
	}

	return flag;
}

int lps(rdf_graph G1, rdf_graph G2)
{
	if(decomposing(G1, G2))
	{
		int match = matching_graphs(G1, G2);
		return match;
	}
	else
		return 0;
}

int decomposing(rdf_graph G1, rdf_graph G2)
{
	rdf_graph smax1 = NULL;
	rdf_graph smax2 = NULL;

	smax1 = decompose(G1);
	smax2 = decompose(G2);

	int match = matching_subgraphs(G1, smax1, G2, smax2);

	return match;
}

rdf_graph decompose(rdf_graph G)
{
	// obtengo los sucesores
	rdf_edge_set suc = successors(G, G->V->value);
	rdf_edge maxe;
	rdf_graph smax = rdf_graph_new();

	// retorno el edge con mayor costo
	maxe = rdf_edge_set_max_cost(suc);

	// agregamos a smax
	rdf_graph_add_node(smax, maxe->subject);
	rdf_graph_add_node(smax, maxe->object);
	rdf_graph_add_edge(smax, maxe);

	return smax;
}

rdf_edge_set successors(rdf_graph G, rdf_node v1)
{
	rdf_edge_set suc = rdf_graph_get_pair(G, v1);
	return suc;
}

int matching_subgraphs(rdf_graph G1, rdf_graph S1, rdf_graph G2, rdf_graph S2)
{
	int ng1 = rdf_graph_count_nodes(G1);
	int ng2 = rdf_graph_count_nodes(G2);

	if(S1->cost == S2->cost && G1->cost == G2->cost && ng1 == ng2)
	{
		rdf_edge_set aux1 = S1->E;
		rdf_edge_set aux2 = S2->E;
		rdf_edge e1;
		rdf_edge e2;

		while(aux1 != NULL && aux2 != NULL)
		{
			e1 = aux1->value;
			e2 = aux2->value;

			if(strcmp(e1->subject->value.string, e2->subject->value.string) && strcmp(e1->object->value.string, e2->object->value.string) && e1->subject->arity != e2->subject->arity && e1->object->arity != e2->object->arity)
				return 0;
			
			aux1 = aux1->next;
			aux2 = aux2->next;
		}

		if(aux1 != NULL || aux2 != NULL)
			return 0; //false

		return 1; // los subgraph son iguales
	}
	else
		return 0;
}

int matching_graphs(rdf_graph G1, rdf_graph G2)
{
	rdf_node_set aux1 = G1->V;

	while(aux1 != NULL)
	{
		rdf_node_set aux2 = G2->V;
		while(aux2 != NULL)
		{
			if(strcmp(aux1->value->value.string, aux1->value->value.string))
				return 0;
			aux2 = aux2->next;
		}

		aux1 = aux1->next;
	}

	return 1;
}
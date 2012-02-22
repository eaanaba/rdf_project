#include "rdf_graph.h"

/*****
****** funciones rdf_graph
*****/
rdf_graph rdf_graph_new()
{
	rdf_graph nuevo;
	nuevo = (rdf_graph)malloc(sizeof(rdf_graph));
	nuevo->V = rdf_node_set_new();
	nuevo->E = rdf_edge_set_new();
	return nuevo;
}

void rdf_graph_node_add(rdf_graph g, rdf_node v)
{
	rdf_node_set_add(g->V, v);
}

void rdf_graph_edge_add(rdf_graph g, rdf_edge e)
{
	rdf_edge_set_add(g->E, e);
}

/*****
****** funciones rdf_node
*****/
rdf_node rdf_node_new()
{
	rdf_node nuevo;
	nuevo = (rdf_node)malloc(sizeof(rdf_node));
	return nuevo;
}

void rdf_node_set_label(rdf_node v, unsigned char *label)
{
	strcpy(v->value.string, label);
	v->value.string_len = strlen(label);
}

void rdf_node_set_arity(rdf_node v, unsigned int arity)
{
	v->arity = arity;
}

/*****
****** funciones rdf_edge
*****/
rdf_edge rdf_edge_new(rdf_node v1, rdf_node v2)
{
	rdf_edge nuevo;
	nuevo = (rdf_edge)malloc(sizeof(rdf_edge));
	nuevo->subject = v1;
	nuevo->object = v2;
	return nuevo;
}

void rdf_edge_set_label(rdf_edge e, unsigned char *label)
{
	strcpy(e->predicate.string, label);
	e->predicate.string_len = strlen(label);
}

/*****
****** funciones rdf_node_set
*****/
rdf_node_set rdf_node_set_new()
{
	rdf_node_set nuevo;
	nuevo = (rdf_node_set)malloc(sizeof(rdf_node_set));
	nuevo->value = NULL;
	nuevo->next = NULL;
	return nuevo;
}	

void rdf_node_set_add(rdf_node_set V, rdf_node v)
{
	// TODO
}

/*****
****** funciones rdf_edge_set
*****/
rdf_edge_set rdf_edge_set_new()
{
	rdf_edge_set nuevo;
	nuevo = (rdf_edge_set)malloc(sizeof(rdf_edge_set));
	nuevo->value = NULL;
	nuevo->next = NULL;
	return nuevo;
}

void rdf_edge_set_add(rdf_edge_set E, rdf_edge e)
{
	// TODO
}

rdf_node rdf_edge_set_get_pair(rdf_edge_set E, rdf_node sub)
{
	rdf_edge_set aux = E;
	while(aux->next)
	{
		if(aux->value->subject == sub)
			return aux->value->object;
		else
			aux = aux->next;
	}

	return NULL;
}
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

int rdf_graph_isempty(rdf_graph G)
{
	if(G->V->value == NULL)
		return 1;
	else
		return 0;
}

void rdf_graph_print(rdf_graph G)
{
	rdf_node_set aux = G->V;
	
	if(aux->value == NULL)
	{
		printf("Graph vacio!\n");
		return;
	}

	while(aux != NULL)
	{
		printf("contenido: %s\n", aux->value->value.string);
		aux = aux->next;
	}
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

void rdf_node_set_label(rdf_node v, char *label)
{
	unsigned int labelen = strlen(label);
	v->value.string = (char *)calloc(labelen, sizeof(char*));
	
	sprintf(v->value.string, "%s", label);
	v->value.string_len = labelen;
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

void rdf_edge_set_label(rdf_edge e, char *label)
{
	unsigned int labelen = strlen(label);
	e->predicate.string = (char *)calloc(labelen, sizeof(char*));
	
	sprintf(e->predicate.string, "%s", label);
	e->predicate.string_len = labelen;
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

void rdf_node_set_add(rdf_node_set V, char *label)
{
	rdf_node_set aux = V;
	rdf_node_set nuevo = rdf_node_set_new();
	
	rdf_node nnode = rdf_node_new();
	rdf_node_set_label(nnode, label);

	while(aux->next != NULL)
		aux = aux->next;
	
	if(aux->value == NULL)
		aux->value = nnode;
	else
	{
		aux->next = nuevo;
		nuevo->value = nnode;
	}
}

int rdf_node_set_exist(rdf_node_set V, char *label)
{
	rdf_node_set aux = V;
	
	if(aux->value == NULL)
		return 0;
	
	while(aux != NULL)
	{
		if(strcmp(label, aux->value->value.string) == 0)
			return 1;
		aux = aux->next;
	}
	
	return 0;
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
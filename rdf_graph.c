#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_graph.h"

/**********************************************************************
****** funciones rdf_graph
**********************************************************************/
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
	rdf_edge_set auxe = G->E;
	
	if(rdf_graph_isempty(G))
	{
		printf("Graph vacio!\n");
		return;
	}

	rdf_edge_set_print(auxe);
}

rdf_node rdf_graph_add_node(rdf_graph G, rdf_node node)
{
	rdf_node_set aux = G->V;

	if(aux->value == NULL)
	{
    	aux->value = node;
		return node;
	}
	else
	{
		while(aux->next != NULL)
			aux = aux->next;
		
		rdf_node_set nuevo = rdf_node_set_new();
		nuevo->value = node;
		aux->next = nuevo;
		return node;
	}
}

rdf_edge rdf_graph_add_edge(rdf_graph G, rdf_edge edge)
{
	rdf_edge_set aux = G->E;

	if(aux->value == NULL)
	{
    	aux->value = edge;
		return edge;
	}
	else
	{
		while(aux->next != NULL)
			aux = aux->next;
		
		rdf_edge_set nuevo = rdf_edge_set_new();
		nuevo->value = edge;
		aux->next = nuevo;
		return edge;
	}
}

rdf_node rdf_graph_node_exist(rdf_graph G, char *string)
{
	rdf_node_set aux = G->V;
	
	if(aux->value == NULL)
		return NULL;
	else
	{
		while(aux != NULL)
		{
			if(strcmp(string, aux->value->value.string) == 0)
				return aux->value;
			aux = aux->next;
		}
		return NULL;
	}
}

rdf_edge_set rdf_graph_get_pair(rdf_graph G, rdf_node sub)
{
	rdf_edge_set aux = G->E;
	rdf_edge_set nuevo = rdf_edge_set_new();
	
	while(aux)
	{
		if(aux->value->subject == sub)
			rdf_edge_set_add(nuevo, aux->value);
		aux = aux->next;
	}

	return nuevo;
}


/**********************************************************************
****** funciones rdf_node
**********************************************************************/
rdf_node rdf_node_new()
{
	rdf_node nuevo;
	nuevo = (rdf_node)malloc(sizeof(nuevo));
	return nuevo;
}

void rdf_node_set_label(rdf_node v, char *label)
{
	int labelen = strlen(label);
	v->value.string = (char*)calloc(labelen, sizeof(char*));

	strcpy(v->value.string, label);
	v->value.string_len = labelen;
}


/**********************************************************************
****** funciones rdf_edge
**********************************************************************/
rdf_edge rdf_edge_new()
{
	rdf_edge nuevo;
	nuevo = (rdf_edge)malloc(sizeof(*nuevo));
	return nuevo;
}

void rdf_edge_add(rdf_edge e, rdf_node sub, rdf_node obj, char *label)
{
	e->subject = sub;
	e->object = obj;
	rdf_edge_set_label(e, label);
}

void rdf_edge_set_label(rdf_edge e, char *label)
{
	int labelen = strlen(label);
	e->predicate.string = (char*)calloc(labelen, sizeof(char*));

	strcpy(e->predicate.string, label);
	e->predicate.string_len = labelen;
}


/**********************************************************************
****** funciones rdf_node_set
**********************************************************************/
rdf_node_set rdf_node_set_new()
{
	rdf_node_set nuevo;
	nuevo = (rdf_node_set)malloc(sizeof(nuevo));
	nuevo->value = NULL;
	nuevo->next = NULL;
	return nuevo;
}


/**********************************************************************
****** funciones rdf_edge_set
**********************************************************************/
rdf_edge_set rdf_edge_set_new()
{
	rdf_edge_set nuevo;
	nuevo = (rdf_edge_set)malloc(sizeof(nuevo));
	nuevo->value = NULL;
	nuevo->next = NULL;
	return nuevo;
}

void rdf_edge_set_add(rdf_edge_set E, rdf_edge e)
{
	rdf_edge_set aux = E;

	if(aux->value == NULL)
		aux->value = e;
	else
	{
		while(aux->next != NULL)
			aux = aux->next;
		rdf_edge_set nuevo = rdf_edge_set_new();
		nuevo->value = e;
		aux->next = nuevo;
	}
}

void rdf_edge_set_print(rdf_edge_set E)
{
	rdf_edge_set aux = E;
	rdf_edge arco;

	while(aux)
	{
		arco = aux->value;
		printf("%s %s %s\n", arco->subject->value.string, arco->predicate.string, arco->object->value.string);
		aux = aux->next;
	}
}


/**********************************************************************
****** funciones rdf_database
**********************************************************************/
rdf_database rdf_database_new()
{
	rdf_database db;
	db = (rdf_database)malloc(sizeof(rdf_database));
	db->G = rdf_graph_new();
	db->next = NULL;
	return db;
}

int rdf_database_count_nodes(rdf_database db)
{
	int count = 0;
	rdf_database aux = db;
	while(aux)
	{
		rdf_node_set aux2 = aux->G->V;
		while(aux2 && aux2->value != NULL)
		{
			count++;
			aux2 = aux2->next;
		}
		aux = aux->next;
	}

	return count;
}

rdf_graph rdf_database_add_graph(rdf_database db)
{
	rdf_database aux = db;

	while(aux->next != NULL)
		aux = aux->next;

	rdf_database nuevo = rdf_database_new();
	aux->next = nuevo;
	CURRENT_GRAPH = nuevo->G;
}

void rdf_database_print(rdf_database db)
{
	rdf_database aux = db;
	while(aux)
	{
		printf("grafo---\n");
		rdf_graph_print(aux->G);
		aux = aux->next;
	}
}

void rdf_database_add_triple(rdf_database db, char *s, char *o, char *p)
{
	rdf_graph G = CURRENT_GRAPH;

	rdf_edge arco = rdf_edge_new();

	rdf_node subject = rdf_graph_node_exist(G, s);
	rdf_node object = rdf_graph_node_exist(G, o);

	if(subject && !object)
	{
		object = rdf_node_new();
		rdf_node_set_label(object, o);
		rdf_graph_add_node(G, object);
		rdf_edge_add(arco, subject, object, p);
    	rdf_graph_add_edge(G, arco);
	}
	else if(!subject && object)
	{
		subject = rdf_node_new();
		rdf_node_set_label(subject, s);
		rdf_graph_add_node(G, subject);
		rdf_edge_add(arco, subject, object, p);
    	rdf_graph_add_edge(G, arco);
	}
	else if(!subject && !object)
	{
		if(!rdf_graph_isempty(G))
			G = rdf_database_add_graph(db);

		subject = rdf_node_new();
		rdf_node_set_label(subject, s);
		rdf_graph_add_node(G, subject);

		object = rdf_node_new();
		rdf_node_set_label(object, o);
		rdf_graph_add_node(G, object);

		rdf_edge_add(arco, subject, object, p);
    	rdf_graph_add_edge(G, arco);
	}
}
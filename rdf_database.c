#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_database.h"

/********************************************************
*** Funciones para rdf_database
*********************************************************/
rdf_database rdf_database_new()
{
    rdf_database new;
    rdf_graph grafo;
    new = (rdf_database) malloc(sizeof(rdf_database));
    grafo = (rdf_graph) malloc(sizeof(rdf_graph));

    new->graphs = grafo;
    new->current = grafo;

    return new;
}

void rdf_database_add_graph(rdf_database db, rdf_graph g)
{
    rdf_graph aux = db->graphs;
    db->current = g;

    while(aux->next != NULL)
        aux = aux->next;
    
    aux->next = g;
}

/********************************************************
*** Funciones para rdf_graph
*********************************************************/
rdf_graph rdf_graph_new()
{
    rdf_graph new;
    rdf_node nodeset; // node_set vacio
    rdf_edge edgeset; // edge_set vacio

    nodeset = rdf_node_new();
    edgeset = rdf_edge_new();

    new = (rdf_graph) malloc(sizeof(rdf_graph));
    new->next = NULL;
    new->node_set = nodeset;
    new->edge_set = edgeset;

    return new;
}

/********************************************************
*** Funciones para rdf_edge
*********************************************************/
rdf_edge rdf_edge_new()
{
    rdf_edge new;
    new = (rdf_edge) malloc(sizeof(rdf_edge));
    new->subject = NULL;
    new->object = NULL;
    new->next = NULL;
    return new;
}

void rdf_edge_add(rdf_edge edge, rdf_node sub, rdf_node obj, unsigned char* pre)
{
    rdf_edge aux = edge;
    rdf_edge new = rdf_edge_new();

    while(aux->next != NULL)
        aux = aux->next;
    
    new->subject = sub;
    new->object = obj;
    new->predicate.string = (unsigned char*) calloc(strlen(pre), sizeof(unsigned char*));
    strcpy(new->predicate.string, pre);
    new->predicate.string_len = strlen(pre);

}

/********************************************************
*** Funciones para rdf_node
*********************************************************/
rdf_node rdf_node_new()
{
    rdf_node new;
    new = (rdf_node) malloc(sizeof(rdf_node));
    new->next = NULL;
    return new;
}

void rdf_node_set_label(rdf_node node, unsigned char *label)
{
    node->value.string = (unsigned char*) calloc(strlen(label), sizeof(unsigned char));
    strcpy(node->value.string, label);
    node->value.string_len = strlen(label);
}

// agrega un nodo al node set
void rdf_node_add(rdf_node nodes, rdf_node new)
{
    rdf_node aux = nodes;

    while(aux->next != NULL)
        aux = aux->next;
    
    aux->next = new;
}
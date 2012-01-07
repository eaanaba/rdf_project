#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_database.h"

/*****
** Crea un grafo rdf vacio.
*****/
rdf_graph rdf_graph_new()
{
    rdf_graph new;
    new.next = NULL;
    return new;
}


/*****
** Anade una nueva tripleta al grafo.
*****/
int rdf_graph_add_edge(rdf_graph *g, rdf_edge *e)
{
    /* TODO */
    while(g->next != NULL)
        g = g->next;
    
    rdf_graph *nuevo = (rdf_graph*) malloc(sizeof(rdf_graph));
    nuevo->edge = *e;
    nuevo->next = NULL;
    g->next = nuevo;
}


/*****
** Imprime un grafo en pantalla
** TODO
*****/
void rdf_graph_print(rdf_graph *g)
{
    while(g->next != NULL)
    {
        printf("SUJETO: %s\n", g->edge.subject->value);
        g = g->next;
    }
}


/*****
** Crea una nueva tripleta con valores.
*****/
rdf_edge rdf_edge_new(rdf_node *s, rdf_node *o, rdf_node_value *prop)
{
    rdf_edge new;
    new.subject = s;
    new.object = o;
    new.property = prop;

    return new;
}
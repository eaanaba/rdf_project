#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_database.h"

/*****
** Crea una nueva base de datos RDF.
*****/
rdf_database rdf_database_new()
{
    rdf_database nueva;
    nueva = (rdf_database) malloc(sizeof(rdf_database));
    nueva->item = NULL;
    nueva->next = NULL;
    return nueva;
}

/*****
** Objecto el ultimo grafo de la bd
*****/
rdf_database rdf_database_get_last(rdf_database db)
{
    rdf_database aux = db;
    while(aux->next != NULL)
        aux = aux->next;
    return aux;
}

rdf_graph rdf_database_get_last_graph(rdf_database db)
{
    rdf_database aux = rdf_database_get_last(db);
    return aux->item;
}

int rdf_database_add_graph(rdf_database db, rdf_graph g)
{
    rdf_database aux = rdf_database_get_last(db);

    if(aux->item != NULL)
    {
        rdf_database nuevo = rdf_database_new();
        nuevo->item = g;
        aux->next = nuevo;
    }
    else
    {
        aux->item = g;
    }
}

/*****
** Crea un grafo rdf vacio.
*****/
rdf_graph rdf_graph_new()
{
    rdf_graph nuevo;
    nuevo = (rdf_graph) malloc(sizeof(rdf_graph));
    nuevo->triple = NULL;
    nuevo->next = NULL;
    return nuevo;
}

/*****
** Anade una nueva tripleta al grafo.
*****/
int rdf_graph_add_edge(rdf_graph g, rdf_edge e)
{
    rdf_graph aux = g;
    rdf_graph nuevo = rdf_graph_new();

    while(aux->next != NULL)
        aux = aux->next;
    
    aux->next = nuevo;
    nuevo->triple = e;
}

/*****
** Crea una nueva tripleta con valores.
*****/
rdf_edge rdf_edge_new(rdf_node s, rdf_node o, unsigned char *p)
{
    rdf_edge nuevo;
    nuevo = (rdf_edge) malloc(sizeof(rdf_edge));
    
    nuevo->predicate.string = p;
    nuevo->subject = s;
    nuevo->object = o;

    return nuevo;
}

/*****
** Crea un grafo rdf vacio.
*****/
rdf_node rdf_node_new()
{
    rdf_node nuevo;
    nuevo = (rdf_node) malloc(sizeof(rdf_node));
    return nuevo;
}
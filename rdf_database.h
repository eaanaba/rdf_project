/***********************************************************
** rdf_database.h.
** contiene cabeceras de todas las funciones para crear y manejar
** la base de datos de grafos RDF, contiene las estructuras.
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compilacion: gcc -o rdfprint rdf_database.c `pkg-config raptor2 --cflags --libs`
// BNBrdfdc01.ntriples  contiene 6.773.422 triples.

/*****
** Me indica tipo de nodo.
*****/
typedef enum {
    RDF_VALUE_TYPE_UNKOWN,
    RDF_VALUE_TYPE_URI,
    RDF_VALUE_TYPE_LITERAL,
    RDF_VALUE_TYPE_BLANK
} rdf_node_value_type;


/*****
** Estructura para el valor del nodo.
*****/
typedef struct {
    unsigned char *string;
    unsigned int string_len;
} rdf_node_value;


/*****
** Cada nodo pertenece a un tipo (blank, literal, uri).
** y contiene valor. Nodo de una tripleta.
*****/
typedef struct {
    rdf_node_value_type type;
    rdf_node_value value;
} rdf_node;


/*****
** Edge - estructura que forma una tripleta
*****/
typedef struct {
    rdf_node *subject;
    rdf_node *object;
    rdf_node_value *property;
} rdf_edge;

/*****
** Estructura que guarda un grafo completo rdf.
** Una lista ligada de grafos.
*****/
typedef struct graph {
    rdf_edge edge;
    struct graph *next;
} rdf_graph;

/*********************************************
** FUNCIONES PARA RDF_GRAPH
**********************************************/

/*****
** Crea un grafo rdf vacio.
*****/
rdf_graph rdf_graph_new();

void rdf_graph_print(rdf_graph *g);

/*****
** Crea un grafo rdf vacio.
*****/
int rdf_graph_add_edge(rdf_graph *g, rdf_edge *e);

/*********************************************
** FUNCIONES PARA RDF_EDGE
**********************************************/

/*****
** Crea una nueva tripleta con valores.
*****/
rdf_edge rdf_edge_new(rdf_node *s, rdf_node *o, rdf_node_value *prop);

/*****
** Toma cada uno de las tripletas del archivo y las descompone
*****/
void save_triple(void *user, raptor_statement *triple);

/*****
** Lee el archivo que contiene las tripletas RDF
** y hace el llamado a la funcion para guardarlos
*****/
void rdf_parse_file(char *file);
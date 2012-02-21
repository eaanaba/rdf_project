#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_graph.h"

// database
typedef struct database {
    rdf_graph G;
    struct database *next;
} *rdf_database;

/*****
*** Funciones
*****/
rdf_database rdf_database_new();
int rdf_database_add_graph(rdf_database db, rdf_graph g);
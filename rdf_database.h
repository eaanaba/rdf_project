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
    char *string;
} rdf_node_value;


/*****
** Cada nodo pertenece a un tipo (blank, literal, uri).
** y contiene valor. Nodo de una tripleta.
*****/
typedef struct {
    rdf_node_value_type type;
    rdf_node_value value;
} *rdf_node;


/*****
** Edge - estructura que forma una tripleta
*****/
typedef struct {
    rdf_node subject;
    rdf_node object;
    rdf_node_value predicate;
} *rdf_edge;


/*****
** Estructura que guarda un grafo completo rdf.
** Una lista ligada de grafos.
*****/
typedef struct graph {
    rdf_edge triple;
    struct graph *next;
} *rdf_graph;

/*****
** Estructura que guarda un grafo completo rdf.
** Una lista ligada de grafos.
*****/
typedef struct database {
    rdf_graph item;
    struct database *next;
} *rdf_database;

/*********************************************
** FUNCIONES PARA RDF_GRAPH
**********************************************/
rdf_database rdf_database_new();
rdf_database rdf_database_get_last(rdf_database db);
rdf_graph rdf_database_get_last_graph(rdf_database db);
int rdf_database_add_graph(rdf_database db, rdf_graph g);

/*********************************************
** FUNCIONES PARA RDF_GRAPH
**********************************************/
rdf_graph rdf_graph_new();
int rdf_graph_add_edge(rdf_graph g, rdf_edge e);

/*********************************************
** FUNCIONES PARA RDF_EDGE
**********************************************/
rdf_edge rdf_edge_new(rdf_node s, rdf_node o, unsigned char *p);

/*********************************************
** FUNCIONES PARA RDF_NODE
**********************************************/
rdf_node rdf_node_new();
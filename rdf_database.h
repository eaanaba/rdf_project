// compilacion: gcc -o rdfprint rdf_database.c `pkg-config raptor2 --cflags --libs`
// BNBrdfdc01.ntriples  contiene 6.773.422 triples.

// tipo de cada nodo
typedef enum {
    RDF_VALUE_TYPE_UNKOWN = 0,
    RDF_VALUE_TYPE_URI = 1,
    RDF_VALUE_TYPE_LITERAL = 2,
    RDF_VALUE_TYPE_BLANK = 4
} rdf_node_value_type;

// valor del nodo
typedef struct {
    unsigned char *string;
    unsigned int string_len;
} rdf_node_value;

// nodos
typedef struct node {
    unsigned int arity;
    rdf_node_value_type type;
    rdf_node_value value;
    struct node *next;
} *rdf_node;

// edges subcontunjo rdf_node x rdf_node
typedef struct edge {
    rdf_node subject;
    rdf_node object;
    rdf_node_value predicate;
    struct edge *next;
} *rdf_edge;

// graphs
typedef struct graph{
    rdf_node node_set;
    rdf_edge edge_set;
    struct graph *next;
} *rdf_graph;

// database
typedef struct database {
    rdf_graph graphs;
    rdf_graph current;
} *rdf_database;

// guardo ultimo registro

/********************************************************
*** Funciones para rdf_database
*********************************************************/
rdf_database rdf_database_new();
void rdf_database_add_graph(rdf_database db, rdf_graph g);

/********************************************************
*** Funciones para rdf_graph
*********************************************************/
rdf_graph rdf_graph_new();
int rdf_graph_have_node(rdf_graph g, rdf_node node);

/********************************************************
*** Funciones para rdf_edge
*********************************************************/
rdf_edge rdf_edge_new();
void rdf_edge_add(rdf_edge edge, rdf_node sub, rdf_node obj, unsigned char* pre);

/********************************************************
*** Funciones para rdf_node
*********************************************************/
rdf_node rdf_node_new();
void rdf_node_set_label(rdf_node node, unsigned char* label);
void rdf_node_add(rdf_node nodes, rdf_node new);
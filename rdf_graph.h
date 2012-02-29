// valor del nodo
typedef struct {
    unsigned char *string;
    int string_len;
} rdf_label;

// nodos
typedef struct {
    unsigned int arity;
    rdf_label value;
} *rdf_node;

// edges subcontunjo rdf_node x rdf_node
typedef struct {
    rdf_node subject;
    rdf_node object;
    rdf_label predicate;
} *rdf_edge;

// edge set
typedef struct edge_set {
    rdf_edge value;
    struct edge_set *next;
} *rdf_edge_set;

// node set
typedef struct node_set {
    rdf_node value;
    struct node_set *next;
} *rdf_node_set;

// graphs
typedef struct {
    rdf_node_set V;
    rdf_edge_set E;
} *rdf_graph;

// database
typedef struct database {
    rdf_graph G;
    struct database *next;
} *rdf_database;


/*****
*** GLOBAL VARIABLE
***/
rdf_graph CURRENT_GRAPH;


/*****
*** Funciones
*****/
rdf_node rdf_node_new();
void rdf_node_set_label(rdf_node v, char *label);

rdf_edge rdf_edge_new();
void rdf_edge_set_label(rdf_edge e, char *label);
void rdf_edge_add(rdf_edge e, rdf_node v1, rdf_node v2, char *label);

rdf_node_set rdf_node_set_new();
int rdf_node_set_add_node(rdf_node_set V, rdf_node nuevo);

rdf_edge_set rdf_edge_set_new();
rdf_node rdf_edge_set_get_pair(rdf_edge_set E, rdf_node sub);

rdf_graph rdf_graph_new();
int rdf_graph_isempty(rdf_graph G);
void rdf_graph_print(rdf_graph G);
rdf_node rdf_graph_add_node(rdf_graph G, rdf_node node);
rdf_edge rdf_graph_add_edge(rdf_graph G, rdf_edge edge);
rdf_node rdf_graph_node_exist(rdf_graph G, char *string);

rdf_database rdf_database_new();
rdf_graph rdf_database_add_graph(rdf_database db);
int rdf_database_count_nodes(rdf_database db);
void rdf_database_print(rdf_database db);
void rdf_database_add_triple(rdf_database db, char *s, char *o, char *p);
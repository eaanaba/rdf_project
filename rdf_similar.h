lista lista_new();

query_result database_query_graph(rdf_database db, rdf_graph G, lista l);
query_result database_query_graph_parallel(rdf_database db,
    rdf_graph G, lista l, int size, int loc);

lista database_get_terms(rdf_database db);
void lista_add_from_graph(lista l, rdf_graph G);
void lista_add_term(lista l, char *s);
void lista_add_string(lista l, char *s);
int lista_proc(lista l, rdf_database db);
void lista_print(lista l);

void rdf_graph_set_terms(rdf_graph G);
void rdf_graph_proc(rdf_graph G, lista l, int d);

query_result rdf_graph_compare(rdf_database db, rdf_graph G);
query_result rdf_graph_compare_parallel(rdf_database db, rdf_graph G, int size, int loc);

double rdf_graph_similar(rdf_graph G1, rdf_graph G2);

void rm_substring(char *s, char *subs);
void space_to_slash(char *str);
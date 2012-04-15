lista lista_new();
lista database_get_terms(rdf_database db);
void lista_add_from_graph(lista l, rdf_graph G);
void lista_add_term(lista l, char *s);
void lista_add_string(lista l, char *s);
void lista_proc(lista l, rdf_database db);
void lista_print(lista l);

void rm_substring(char *s, char *subs);
void space_to_slash(char *str);
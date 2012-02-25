#include "rdf_parser.h"

/*****
** Toma cada uno de las tripletas del archivo y las descompone
** va guardando en la BD.
*****/
static void save_triple(void *user, raptor_statement *triple)
{
    rdf_database db = (rdf_database)user;
    short int isblank = 0;

    char *s = raptor_term_to_string (triple->subject);
    char *o = raptor_term_to_string (triple->object);
    char *p = raptor_term_to_string (triple->predicate);

    // si existen los nodos
    int si_s = rdf_node_set_exist(CURRENT_GRAPH->V, s);
    int si_o = rdf_node_set_exist(CURRENT_GRAPH->V, o);

    if(strncmp(s, "_:genid", 7) == 0)
        isblank = 1;

    if(rdf_graph_isempty(CURRENT_GRAPH))
    {
        rdf_node_set_add(CURRENT_GRAPH->V, s);
        rdf_node_set_add(CURRENT_GRAPH->V, o);
    }
    else if(si_s && !si_o)
        rdf_node_set_add(CURRENT_GRAPH->V, o);
    else if(!si_s && si_o)
        rdf_node_set_add(CURRENT_GRAPH->V, s);
    else if(si_s && si_o)
        return;
    else if(!si_s && !si_o && isblank == 1)
    {
        rdf_node_set_add(CURRENT_GRAPH->V, s);
        rdf_node_set_add(CURRENT_GRAPH->V, o);
    }
    else
    {
        rdf_graph nuevo = rdf_graph_new();
        rdf_database_add_graph(db, nuevo);
        CURRENT_GRAPH = nuevo;

        rdf_node_set_add(CURRENT_GRAPH->V, s);
        rdf_node_set_add(CURRENT_GRAPH->V, o);
    }
}


/*****
** Lee el archivo que contiene las tripletas RDF
** y hace el llamado a la funcion save_triple() para guardarlos
*****/
void rdf_database_read_file(rdf_database db, const char *file)
{
    raptor_world *world = NULL;
    raptor_parser *rdf_parser = NULL;
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;

    // parser
    world = raptor_new_world();
    rdf_parser = raptor_new_parser(world, "rdfxml");

    // seteo funcion handler para cada nodo
    raptor_parser_set_statement_handler(rdf_parser, (void*)db, save_triple);

    uri_string = raptor_uri_filename_to_uri_string(file);
    uri = raptor_new_uri(world, uri_string);
    base_uri = raptor_uri_copy(uri);

    // empieza parseo y guardado en memoria
    raptor_parser_parse_file(rdf_parser, uri, base_uri);

    // liberar ram
    raptor_free_parser(rdf_parser);
    raptor_free_uri(base_uri);
    raptor_free_uri(uri);
    raptor_free_memory(uri_string);
    raptor_free_world(world);
}
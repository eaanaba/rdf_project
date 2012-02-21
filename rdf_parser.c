#include "rdf_parser.h"

/*****
** Toma cada uno de las tripletas del archivo y las descompone
** va guardando en la BD.
*****/
static void save_triple(void *user, raptor_statement *triple)
{
    rdf_database db = (rdf_database)user;

    unsigned char *s = raptor_term_to_string (triple->subject);
    unsigned char *o = raptor_term_to_string (triple->object);
    unsigned char *p = raptor_term_to_string (triple->predicate);

    raptor_statement_print_as_ntriples(triple, stdout);
    fputc('\n', stdout);
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
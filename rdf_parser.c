#include <string.h>
#include <stdlib.h>
#include <raptor2.h>

#include "rdf_graph.h"

raptor_parser *rdf_parser = NULL;
int count = 0;

/*****
** Toma cada uno de las tripletas del archivo y las descompone
** va guardando en la BD.
*****/
static void save_triple(void *user, raptor_statement *triple)
{
    rdf_database db = (rdf_database)user;

    char *s = raptor_uri_to_string(triple->subject->value.uri);
    char *p = raptor_uri_to_string(triple->predicate->value.uri);
    char *o;

    if(triple->object->type == 1)
        o = raptor_uri_to_string(triple->object->value.uri);
    else
        o = triple->object->value.literal.string;
    
    // con 100000 y persondata50.rdf tengo la mitad de la bd isomorfa
    if(db->n == 17000)
    {
        raptor_parser_parse_abort(rdf_parser);
    }
    else
        rdf_database_add_triple(db, s, p, o);
    
    count++;
}


/*****
** Lee el archivo que contiene las tripletas RDF
** y hace el llamado a la funcion save_triple() para guardarlos
*****/
void rdf_database_read_file(rdf_database db, const char *file)
{
    raptor_world *world = NULL;
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
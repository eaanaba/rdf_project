#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include "rdf_database.h"

/*****
** Toma cada uno de las tripletas del archivo y las descompone
** va guardando en la BD.
*****/
static void save_triple(void *user, raptor_statement *triple)
{
    rdf_database db = (rdf_database) user;

    printf("obtengo la bd\n"  );

    rdf_node subject = rdf_node_new();
    rdf_node object = rdf_node_new();

    printf("creo los dos nodos\n");

    /**
    ** VER EL TEMA DE LA MEMORIA
    **/
    subject->value.string = (char*) malloc(sizeof(char));

    printf("Le di memoria\n"  );

    sprintf(subject->value.string, "%s", raptor_term_to_string (triple->subject));
    //strcpy(object->value.string, raptor_term_to_string (triple->object));

    //edge que los une
    rdf_edge edge = rdf_edge_new(subject, object, raptor_term_to_string (triple->predicate));

    // se agrega a la bd
    rdf_graph lastGraph = rdf_database_get_last_graph(db);
    rdf_graph_add_edge(lastGraph, edge);

    raptor_free_statement(triple);
}


/*****
** Lee el archivo que contiene las tripletas RDF
** y hace el llamado a la funcion save_triple() para guardarlos
*****/
void rdf_database_read_file(rdf_database database, const char *file)
{
    raptor_world *world = NULL;
    raptor_parser *rdf_parser = NULL;
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;

    // parser
    world = raptor_new_world();
    rdf_parser = raptor_new_parser(world, "rdfxml");

    // seteo funcion handler para cada nodo
    raptor_parser_set_statement_handler(rdf_parser, (void*)database, save_triple);

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
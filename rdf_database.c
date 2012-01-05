#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include "utils.h"

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
    unsigned char *string;
    unsigned int string_len;
} rdf_node_value;


/*****
** Cada nodo pertenece a un tipo (blank, literal, uri).
** y contiene valor.
*****/
typedef struct {
    rdf_node_value_type type;
    rdf_node_value value;
} rdf_node;


/*****
** Edge
*****/
typedef struct {
    rdf_node *subject;
    rdf_node *object;
    rdf_node *property;
} rdf_edge;


/*****
** Toma cada uno de las tripletas del archivo y las descompone
*****/
void save_triple(void *user, raptor_statement *triple) 
{
    raptor_statement_print_as_ntriples(triple, stdout);
    fputc('\n', stdout);
}


/*****
** Lee el archivo que contiene las tripletas RDF
** y hace el llamado a la funcion para guardarlos
*****/
void rdf_parse_file(char *file)
{
    raptor_world *world = NULL;
    raptor_parser *rdf_parser = NULL;
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;

    // parser
    world = raptor_new_world();
    rdf_parser = raptor_new_parser(world, "rdfxml");

    // seteo funcion handler para cada nodo
    raptor_parser_set_statement_handler(rdf_parser, NULL, save_triple);

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


/*****
** Debug only
*****/
int main(int argc, char *argv[])
{
    if(argv[1] != 0)
    {
        rdf_parse_file(argv[1]);
    } 
    else
        printf("usage: %s rdf.xml\n", argv[0]);
    
    return 0;
}
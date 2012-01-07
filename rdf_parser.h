/***********************************************************
** rdf_parser.h.
** contiene cabeceras de todas las funciones para crear y manejar
** la base de datos de grafos RDF, contiene las estructuras.
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

/*****
** Toma cada uno de las tripletas del archivo y las descompone
** va guardando en la BD.
*****/
void save_triple(void *user, raptor_statement *triple);


/*****
** Lee el archivo que contiene las tripletas RDF
** y hace el llamado a la funcion para guardarlos
*****/
void rdf_parse_file(char *file);
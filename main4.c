#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include <time.h>

#include "rdf_graph.h"
#include "rdf_parser.h"
#include "rdf_lps.h"

int main(int argc, char **argv)
{
	double inicio;
	double final;
	int nodos;
	int i;

	if(argc != 2)
	{
		printf("usage: %s dataset.rdf\n", argv[0]);
		exit(1);
	}

	// parser file y poblo la bd.
	rdf_database DATABASE = rdf_database_new();
	rdf_database_read_file(DATABASE, argv[1]);

	// grafo a buscar de prueba
	rdf_graph Gprueba = rdf_graph_new();
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle",
		"http://dbpedia.org/ontology/deathPlace", 
		"http://dbpedia.org/resource/Chalcis");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", 
		"http://dbpedia.org/ontology/birthPlace", 
		"http://dbpedia.org/resource/Stageira");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", 
		"http://purl.org/dc/elements/1.1/description", "Greek philosopher");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", 
		"http://www.w3.org/1999/02/22-rdf-syntax-ns#type", 
		"http://xmlns.com/foaf/0.1/Person");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", 
		"http://xmlns.com/foaf/0.1/name", "Aristotle");

	double suma = 0;

	for(i=0;i<10;i++)
	{
		inicio = clock();
		nodos = buscar(DATABASE, Gprueba);
		final = clock();
		suma += (double)(final-inicio)/CLOCKS_PER_SEC;
	}

	printf("LPS secuencial\n");
	printf("Tiempo promedio de 10 consultas: %3.5f\n", suma/10);
	printf("%d grafos\n", DATABASE->n);
	printf("%d nodos\n", nodos);

	return 0;
}
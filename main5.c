#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include <time.h>

#include "rdf_graph.h"
#include "rdf_parser.h"
#include "rdf_lps.h"

#define  INIT  1        // Message dando el tamano
#define  DATA  2        // mensaje que comunica datos
#define  ANSW  3        // mensaje retornando el vector y ordenado

int parallel(int size, int loc, rdf_database db, rdf_graph G);

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("usage: %s dataset.rdf\n", argv[0]);
		exit(1);
	}

	int myRank, nProc;
	int rc;
   	int size;          // tamano de la bd a leer
   	int loc;			// locacion en la bd
   	double start;
   	double finish;

	rc = MPI_Init(&argc, &argv);
	MPI_Status status;

	if ( rc < 0 )
	{
		puts ("Fallo MPI.  Abort!");
		exit(-1);
	}

	rc = MPI_Comm_rank (MPI_COMM_WORLD, &myRank);
	rc = MPI_Comm_size (MPI_COMM_WORLD, &nProc);

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

	// levanto la BD
	rdf_database DATABASE;
	DATABASE = rdf_database_new();
	rdf_database_read_file(DATABASE, argv[1]);

	// proceso la base de datos y obtengo los términos
	//lista terms = database_get_terms(DATABASE);
	//lista_proc(terms, DATABASE);

	// todos poseen la BD lista
	MPI_Barrier(MPI_COMM_WORLD);

	// *****
	// *****
	// EMPIEZA EL PARALELO!
	// *****
	// *****
	if(myRank == 0) // proceso principal Head0
	{
		int i,j;
		double suma = 0;
		size = DATABASE->n/nProc;
		int resultado[nProc];
		
		if(DATABASE->n%2 == 0)
			loc = size;
		else
			loc = size+1;

		for(j=0;j<10;j++){
		start = MPI_Wtime(); // tomo el tiempo!
		for(i = 1; i < nProc; i++)
		{
			rc = MPI_Send(&size, 1, MPI_INT, i, INIT, MPI_COMM_WORLD);
			rc = MPI_Send(&loc, 1, MPI_INT, i, INIT, MPI_COMM_WORLD);
			loc += size;
		}

		// maestro busca
		resultado[0] = buscarn(DATABASE, Gprueba, 0, size+1);

		// recivo datos
		for(i = 1; i < nProc; i++)
		{
			rc = MPI_Recv(&resultado[i], 1, MPI_INT, i, ANSW, MPI_COMM_WORLD, &status);
		}
		finish = MPI_Wtime();
		suma += (finish-start);
		}

		for(i = 0; i < nProc; i++)
		{
			printf("Procesador %d:\n", i);
			printf("nodos: %d\n",	resultado[i]);
		}

		printf("LPS Paralelo M-E\n");
		printf("Tiempo paralelo LPS: %3.5f\n", suma/10);
		printf("%d grafos\n", DATABASE->n);
		printf("%d nodos\n", rdf_database_count_nodes(DATABASE));
	}
	else
	{
		int resultado;
		int j;
		
		for(j=0;j<10;j++){
		rc = MPI_Recv(&size, 1, MPI_INT, MPI_ANY_SOURCE, INIT, MPI_COMM_WORLD, &status);
		rc = MPI_Recv(&loc, 1, MPI_INT, MPI_ANY_SOURCE, INIT, MPI_COMM_WORLD, &status);

		// esclavo busca
		resultado = buscarn(DATABASE, Gprueba, loc, size);

		rc = MPI_Send(&resultado, 1, MPI_INT, 0, ANSW, MPI_COMM_WORLD);
		}

		MPI_Finalize();
      	return 0;
	}
}
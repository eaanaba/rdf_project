#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include <time.h>

#include "rdf_graph.h"
#include "rdf_parser.h"
#include "rdf_lps.h"

#define  INIT  1        // Message dando tamano
#define  ANSW  3        // Message retornando verificacion

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("usage: %s dataset.rdf\n", argv[0]);
		exit(1);
	}

	// MPI stuffffff
	int nprocs;
	int myrank;
	int i;
	int rc;
	MPI_Status stat;
	double start;        // Begin parallel sort
    double middle;       // Finish parallel sort
	double finish;
	double start2;

	rc = MPI_Init(&argc,&argv);
	rc = MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	rc = MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

	if (rc < 0)
	{
		puts ("Fallo MPI. Abort!");
		exit(-1);
	}

	// grafo a buscar de prueba
	rdf_graph Gprueba = rdf_graph_new();
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", "http://dbpedia.org/ontology/deathPlace", "http://dbpedia.org/resource/Chalcis");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", "http://dbpedia.org/ontology/birthPlace", "http://dbpedia.org/resource/Stageira");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", "http://purl.org/dc/elements/1.1/description", "Greek philosopher");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://xmlns.com/foaf/0.1/Person");
	rdf_graph_add_triple(Gprueba, "http://dbpedia.org/resource/Aristotle", "http://xmlns.com/foaf/0.1/name", "Aristotle");

	// DB
	rdf_database DATABASE;
	DATABASE = rdf_database_new();
	rdf_database_read_file(DATABASE, argv[1]);

	// todos poseen la BD lista
	MPI_Barrier(MPI_COMM_WORLD);

	if(myrank == 0)
	{
		// calculo porcion que cada uno revisará
		int porcion = DATABASE->n/nprocs;
		int inicio;
		int fin;
		int encontrado[nprocs];

		// valores iniciales
		inicio = 0;
		fin = inicio + porcion-1;

		// envio los indices que deben leer
		for( i = 1; i < nprocs; i++)
		{
			inicio = fin+1;
			if(i == nprocs-1)
				fin = DATABASE->n-1;
			else
				fin = inicio + porcion-1;

			// envio tamano de la lista a enviar
			MPI_Send(&inicio, 1, MPI_INT, i, INIT, MPI_COMM_WORLD);
			MPI_Send(&fin, 1, MPI_INT, i, INIT, MPI_COMM_WORLD);
		}

		// valores iniciales
		inicio = 0;
		fin = inicio + porcion-1;

		// sincronizamos que todos tengan BD lista
		MPI_Barrier(MPI_COMM_WORLD);

		// empieza a buscar el mismo
		start = MPI_Wtime();
		encontrado[0] = buscarn(DATABASE, Gprueba, inicio, fin);

		// recibo lo de los demas nodos
		for( i = 1; i < nprocs; i++)
			MPI_Recv(&encontrado[i], 1, MPI_INT, i, ANSW, MPI_COMM_WORLD, &stat);
		middle = MPI_Wtime();
	}
	else
	{
		int inicio;
		int fin;
		int encontrado;

		// recibo inicio y fin
		MPI_Recv(&inicio, 1, MPI_INT, 0, INIT, MPI_COMM_WORLD, &stat);
		MPI_Recv(&fin, 1, MPI_INT, 0, INIT, MPI_COMM_WORLD, &stat);

		// sincronizamos que todos tengan BD lista
		MPI_Barrier(MPI_COMM_WORLD);

		// empieza a buscar el mismo
		encontrado = buscarn(DATABASE, Gprueba, inicio, fin);
		
		// envio mi resultado
		MPI_Send(&inicio, 1, MPI_INT, 0, ANSW, MPI_COMM_WORLD);

		MPI_Finalize();
		return 0;
	}

	// secuential
	start2 = MPI_Wtime();
	buscar(DATABASE, Gprueba);
	finish = MPI_Wtime();

	// solo myran == 0 ejecuta aqui
	// tiempo
	printf("tiempo paralelo: %3.3f\n", (middle-start));
	printf("tiempo secuencial: %3.3f\n", (finish-start2));
	printf ("Speed-up:  %3.3f\n", (finish-start2)/(middle-start) );
	printf("%d nodos\n", rdf_database_count_nodes(DATABASE));

	MPI_Abort(MPI_COMM_WORLD, 0);
}
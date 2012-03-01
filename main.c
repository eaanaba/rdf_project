#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include "rdf_graph.h"
#include "rdf_parser.h"
#include "rdf_lps.h"

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		rdf_database database;
		database = rdf_database_new();
		
		CURRENT_GRAPH = database->G;
		
		// parser file y poblo la bd.
		rdf_database_read_file(database, argv[1]);

		//rdf_database_print(database);

		//test lps
		//rdf_graph smax;
		//decompose(database->G, smax);
	}
	else
	{
		printf("usage: %s rdf.xml\n", argv[0]);
	}

	return 0;
}
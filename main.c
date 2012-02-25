#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include "rdf_parser.h"

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		rdf_database database;
		database = rdf_database_new();
		CURRENT_GRAPH = database->G;
		rdf_database_read_file(database, argv[1]);

		rdf_database_print(database);
	}
	else
	{
		printf("usage: %s rdf.xml\n", argv[0]);
	}

	return 0;
}
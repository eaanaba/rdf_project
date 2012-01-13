#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdf_parser.h"
#include "rdf_database.h"

int int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		rdf_parse_file(argv[1]);
	}
	else
	{
		printf("usage %s rdf.xml\n", argv[0]);
	}
	
	return 0;
}
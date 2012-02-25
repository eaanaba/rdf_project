#include "rdf_db.h"

rdf_database rdf_database_new()
{
	rdf_database db;
	db = (rdf_database)malloc(sizeof(rdf_database));
	db->G = rdf_graph_new();
	db->next = NULL;
	return db;
}

int rdf_database_add_graph(rdf_database db, rdf_graph g)
{
	rdf_database aux = db;

	if(db->G == NULL)
	{
		db->G = g;
	} else {
		while(aux->next != NULL)
		{
			aux = aux->next;
		}

		rdf_database nuevo = rdf_database_new();
		nuevo->G = g;
		aux->next = nuevo;
	}
}

void rdf_database_print(rdf_database db)
{
	rdf_database aux = db;
	while(aux)
	{
		printf("grafo---\n");
		rdf_graph_print(aux->G);
		aux = aux->next;
	}
}
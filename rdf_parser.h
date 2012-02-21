#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raptor2.h>

#include "rdf_db.h"

static void save_triple(void *user, raptor_statement *triple);
void rdf_database_read_file(rdf_database database, const char *file);
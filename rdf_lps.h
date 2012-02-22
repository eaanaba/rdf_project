#include "rdf_graph.h"

//
// descompone el grafo en varios subrafos
//
void decomposing(rdf_graph G);
void decompose(rdf_graph G, rdf_graph S, rdf_node_set V);
rdf_node_set successors(rdf_graph G, rdf_node_set V);
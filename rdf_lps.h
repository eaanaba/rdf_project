//
// descompone el grafo en varios subrafos
//
void decomposing(rdf_graph G);
rdf_graph decompose(rdf_graph G, rdf_graph Smax);
rdf_node_set successors(rdf_graph G, rdf_node v1);
void print_successors(rdf_node_set V);
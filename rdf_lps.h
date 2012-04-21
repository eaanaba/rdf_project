//
// descompone el grafo en varios subrafos
//
int decomposing(rdf_graph G1, rdf_graph G2);
rdf_graph decompose(rdf_graph G);
rdf_edge_set successors(rdf_graph G, rdf_node v1);
int matching_subgraphs(rdf_graph G1, rdf_graph S1, rdf_graph G2, rdf_graph S2);
int matching_graphs(rdf_graph G1, rdf_graph G2);
int buscar(rdf_database db, rdf_graph G);
int buscarn(rdf_database db, rdf_graph G, int inicio, int fin);
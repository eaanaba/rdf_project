#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rdf_graph.h"
#include "rdf_similar.h"

lista lista_new()
{
    lista nuevo;
    nuevo = (lista)malloc(sizeof(*nuevo));
    nuevo->next = NULL;
    nuevo->string = NULL;
    nuevo->tf = 0;
    nuevo->df = 0;
    nuevo->idf = 0;
    return nuevo;
}

query_result database_query_graph_parallel(rdf_database db, rdf_graph G,
    lista l, int size, int loc)
{
    rdf_graph_set_terms(G); // seteo los terminos del grafo
    rdf_graph_proc(G, l, db->n); // obtengo los indices df e idf

    query_result resultado = rdf_graph_compare_parallel(db, G, size, loc);

    return resultado;
}

// obtengo la similaridad de un grafo con todos de la bd
query_result database_query_graph(rdf_database db, rdf_graph G, lista l)
{
    rdf_graph_set_terms(G); // seteo los terminos del grafo
    rdf_graph_proc(G, l, db->n); // obtengo los indices df e idf

    query_result resultado = rdf_graph_compare(db, G);

    return resultado;
}

// llena G->terms con los terminos del grafo
void rdf_graph_set_terms(rdf_graph G)
{
    rdf_node_set aux = G->V;
    rdf_edge_set aux2 = G->E;
    G->terms = lista_new();

    while(aux != NULL)
    {
        lista_add_string(G->terms, aux->value->value.string);
        aux = aux->next;
    }

    while(aux2 != NULL)
    {
        lista_add_string(G->terms, aux2->value->predicate.string);
        aux2 = aux2->next;
    }
}

// procesa el grafo dado obteniendo los indices, df e idf
void rdf_graph_proc(rdf_graph G, lista l, int d)
{
    lista aux = G->terms;
    lista aux2;

    while(aux != NULL)
    {
        aux2 = l;
        while(aux2 != NULL)
        {
            if(!strcmp(aux->string, aux2->string))
            {
                aux->df = aux2->df;
                if(aux2->df != 0)
                {
                    float division = ((float)d/aux2->df);
                    aux->idf = (float)log10(division);
                }
                break;
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }
}

// obtiene similaridad de un grafo con todos los grafos de la bd
query_result rdf_graph_compare(rdf_database db, rdf_graph G)
{
    //double resultado[db->n]; // numero de grafos
    //double *resultado = (double*) calloc (db->n, sizeof *resultado);
    query_result vector = (query_result)calloc(db->n, sizeof(*vector));
    //query_result vector[db->n];
    rdf_database auxdb = db;

    int i = 0;
    while(auxdb != NULL)
    {
        vector[i].idf = rdf_graph_similar(G, auxdb->G);
        vector[i].index = auxdb->G->index;
        i++;
        auxdb = auxdb->next;
    }

    return vector;
}

// obtiene similaridad de un grafo con todos los grafos de la bd paralelo
query_result rdf_graph_compare_parallel(rdf_database db, rdf_graph G,
    int size, int loc)
{
    //double resultado[size];
    //double *resultado = (double*) calloc (size, sizeof *resultado);
    query_result vector = (query_result)calloc(size, sizeof(*vector));
    rdf_database auxdb = db;

    int final = loc + size;
    
    int i = 0;
    while(auxdb != NULL)
    {
        if(auxdb->G->index >= loc && auxdb->G->index < final)
        {
            vector[i].idf = rdf_graph_similar(G, auxdb->G);
            vector[i].index = auxdb->G->index;
            i++;
        }
        auxdb = auxdb->next;
    }

    return vector;
}

// similaridad entre dos grafos y multiplica los indices
double rdf_graph_similar(rdf_graph G1, rdf_graph G2)
{
    lista aux1 = G1->terms;
    lista aux2;
    double suma = 0.0;

    while(aux1)
    {
        aux2 = G2->terms;
        while(aux2)
        {
            if(!strcmp(aux1->string, aux2->string))
                suma = suma + (aux1->idf * aux2->idf);
            aux2 = aux2->next;
        }
        aux1 = aux1->next;
    }

    return suma;
}

// obtengo los terminos de toda la bd
lista database_get_terms(rdf_database db)
{
    lista terms = lista_new();
    rdf_database aux = db;

    while(aux != NULL)
    {
        lista_add_from_graph(terms, aux->G);

        // terms de cada grafo
        aux->G->terms = lista_new();
        lista_add_from_graph(aux->G->terms, aux->G);
        
        aux = aux->next;
    }
    
    return terms;
}

void lista_add_from_graph(lista l, rdf_graph G)
{
    rdf_node_set aux = G->V;
    rdf_edge_set aux2 = G->E;

    while(aux != NULL)
    {
        lista_add_string(l, aux->value->value.string);
        aux = aux->next;
    }

    while(aux2 != NULL)
    {
        lista_add_string(l, aux2->value->predicate.string);
        aux2 = aux2->next;
    }
}

// uri completa
void lista_add_string(lista l, char *s)
{
    int slen = strlen(s);
    char *ss = (char*)calloc(slen, sizeof(char*));
    strcpy(ss, s);

    rm_substring(ss, "http://");
    rm_substring(ss, "www.");
    rm_substring(ss, ".com");
    rm_substring(ss, ".net");
    rm_substring(ss, ".org");
    space_to_slash(ss);

    char *p;
    p = strtok (ss, "/");

    while (p != NULL)
    {
        lista_add_term(l, p); // add cada termino a la lista de terminos
        p = strtok (NULL, "/");
    }

    free(ss);
}

// palabra unica
void lista_add_term(lista l, char *s)
{
    lista nuevo;
    lista aux = l;
    int flag = 0;
    int slen = strlen(s);

    if(aux->string == NULL)
    {
        aux->string = (char*)calloc(slen, sizeof(char*));
        strcpy(aux->string, s);
    }

    // busco en la lista de terminos
    while(aux->next != NULL)
    {
        if(!strcmp(aux->string, s))
        {
            flag = 1;
            aux->tf++;
            break;
        }
        aux = aux->next;
    }

    if(!strcmp(aux->string, s) && aux->next == NULL)
    {
        flag = 1;
        aux->tf++;
    }

    if(flag == 0)
    {
        nuevo = lista_new();
        nuevo->string = (char*)calloc(slen, sizeof(char*));
        strcpy(nuevo->string, s);
        nuevo->tf++;
        aux->next = nuevo;
    }
}

// proceso los terminos de cada lista de cada grafo
int lista_proc(lista l, rdf_database db)
{
    lista aux = l;
    lista aux2;
    rdf_database auxdb;
    int n = 0;

    // obtengo n y el indice df
    while(aux != NULL)
    {
        n++;
        auxdb = db;
        while(auxdb != NULL)
        {
            aux2 = auxdb->G->terms;
            while(aux2 != NULL)
            {
                if(!strcmp(aux->string, aux2->string))
                {
                    aux->df++;
                    break;
                }
                aux2 = aux2->next;
            }
            auxdb = auxdb->next;
        }
        aux = aux->next;
    }

    // recorro bd y saco idf
    auxdb = db;
    while(auxdb != NULL)
    {
        aux2 = auxdb->G->terms;
        while(aux2 != NULL)
        {
            aux = l;
            while(aux != NULL)
            {
                if(!strcmp(aux->string, aux2->string))
                {
                    // calculo idf
                    if(aux->df != 0)
                    {
                        float division = ((float)db->n/aux->df);
                        aux2->idf = (float)log10(division);
                    }
                    break;
                }
                aux = aux->next;
            }
            aux2 = aux2->next;
        }
        auxdb = auxdb->next;
    }

    return n;
}

void lista_print(lista l)
{
    lista aux = l;
    while(aux)
    {
        printf("%s -- tf: %d df: %d idf: %3.5f \n",
            aux->string, aux->tf, aux->df, aux->idf);
        aux = aux->next;
    }
}

void lista_print_db(rdf_database db)
{
    rdf_database aux = db;
    while(aux)
    {
        printf("\n\n GRAFO: \n");
        lista_print(aux->G->terms);
        aux = aux->next;
    }
}

void rm_substring(char *s, char *subs)
{
    char *p;
    if ((p=strstr(s,subs)) != NULL)
        memmove(p,p+strlen(subs), strlen(p+strlen(subs))+1);
}

void space_to_slash(char *str)
{
    while(*str != '\0') {
        if(*str == ' ' || *str == '#' || *str == '_') 
            sprintf(str, "/");
        str++;
    }
}
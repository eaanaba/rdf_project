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
            break;
        }
        aux = aux->next;
    }

    if(!strcmp(aux->string, s))
        flag = 1;

    if(flag == 0)
    {
        nuevo = lista_new();
        nuevo->string = (char*)calloc(slen, sizeof(char*));
        strcpy(nuevo->string, s);
        nuevo->tf++;
        aux->next = nuevo;
    } else
        aux->tf++;
}

// proceso los terminos de cada lista de cada grafo
void lista_proc(lista l, rdf_database db)
{
    lista aux = l;
    lista aux2;
    rdf_database auxdb;
    int n = 0;
    int flag; // indicara si termino pertenece a grafo

    // obtengo n y el indice df
    while(aux != NULL)
    {
        n++;

        auxdb = db;
        while(auxdb != NULL)
        {
            flag = 0;
            aux2 = auxdb->G->terms;
            while(aux2 != NULL)
            {
                if(!strcmp(aux->string, aux2->string))
                {
                    flag = 1;
                    break;
                }
                aux2 = aux2->next;
            }

            // resultado de si lo encuentra
            if(flag)
                aux->df++;

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
                    aux2->idf = log10((float)(db->n/aux->df));
                    break;
                }
                aux = aux->next;
            }
            
            aux2 = aux2->next;
        }

        auxdb = auxdb->next;
    }
}

void lista_print(lista l)
{
    lista aux = l;
    while(aux)
    {
        printf("%s-%3.5f\n", aux->string, aux->idf);
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
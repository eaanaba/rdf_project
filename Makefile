#
# Makefile
#

CC=mpicc
#CC=cc

# similar paralelo
#FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main.c

# similar secuencial
#FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main2.c

# lps paralelo logaritmico
#FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main3.c

# lps paralelo maestro-esclavo
FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main5.c

# lps secuencial
#FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main4.c

OBJETOS=$(FUENTES:.c=.o)

CFLAGS=-I/usr/include/raptor2
SLIBS=-lraptor2

#PROGRAMA=similars
#PROGRAMA=similarp
#PROGRAMA=lpsp
#PROGRAMA=lpss
PROGRAMA=lpsm

.KEEP_STATE:

$(PROGRAMA): $(OBJETOS)
	$(CC) -g -O3 -o $(PROGRAMA) $(OBJETOS) $(CFLAGS) $(SLIBS) -lm
	rm -f $(OBJETOS)

clean:
	rm -f $(PROGRAMA) $(OBJETOS)
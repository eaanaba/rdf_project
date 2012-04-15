#
# Makefile
#

#CC=mpicc
CC=cc

#FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main.c
FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c rdf_similar.c main2.c
OBJETOS=$(FUENTES:.c=.o)

CFLAGS=-I/usr/include/raptor2
SLIBS=-lraptor2

#PROGRAMA=main
PROGRAMA=main2

.KEEP_STATE:

$(PROGRAMA): $(OBJETOS)
	$(CC) -g -O3 -o $(PROGRAMA) $(OBJETOS) $(CFLAGS) $(SLIBS)
	rm -f $(OBJETOS)

clean:
	rm -f $(PROGRAMA) $(OBJETOS)
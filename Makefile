#
# Makefile
#

FUENTES=rdf_graph.c rdf_parser.c rdf_lps.c main.c
OBJETOS=$(FUENTES:.c=.o)
CFLAGS=-I/usr/include/raptor2
SLIBS=-lraptor2
PROGRAMA=main

.KEEP_STATE:

$(PROGRAMA): $(OBJETOS)
	cc -g -O3 -o $(PROGRAMA) $(OBJETOS) $(CFLAGS) $(SLIBS)
	rm -f $(OBJETOS)

clean:
	rm -f $(PROGRAMA) $(OBJETOS)
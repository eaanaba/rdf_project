#
# Makefile
#

FUENTES=main.c rdf_db.c rdf_graph.c rdf_parser.c
OBJETOS=$(FUENTES:.c=.o)
CFLAGS=-I/usr/include/raptor2
SLIBS=-lraptor2
PROGRAMA=main

.KEEP_STATE:

$(PROGRAMA): $(OBJETOS)
	cc -g -o $(PROGRAMA) $(OBJETOS) $(CFLAGS) $(SLIBS)

clean:
	rm -f $(PROGRAMA) $(OBJETOS)
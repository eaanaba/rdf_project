#
# Makefile
#

FUENTES=main.c rdf_database.c rdf_parser.c
OBJETOS=$(FUENTES:.c=.o)
CFLAGS=-I/usr/include/raptor2
SLIBS=-lraptor2
PROGRAMA=main

.KEEP_STATE:

$(PROGRAMA): $(OBJETOS)
	cc -o $(PROGRAMA) $(OBJETOS) $(CFLAGS) $(SLIBS)

clean:
	rm -f $(PROGRAMA) $(OBJETOS)
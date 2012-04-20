#!/usr/bin/env python2
# python 2.7.3 code

import rdflib

grafo_xml = '''
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
  <rdf:Description rdf:about="http://dbpedia.org/resource/Aristotle">
    <ns0:deathPlace xmlns:ns0="http://dbpedia.org/ontology/" rdf:resource="http://dbpedia.org/resource/Chalcis"/>
  </rdf:Description>
  <rdf:Description rdf:about="http://dbpedia.org/resource/Aristotle">
    <ns0:birthPlace xmlns:ns0="http://dbpedia.org/ontology/" rdf:resource="http://dbpedia.org/resource/Stageira"/>
  </rdf:Description>
  <rdf:Description rdf:about="http://dbpedia.org/resource/Aristotle">
    <ns0:description xmlns:ns0="http://purl.org/dc/elements/1.1/" xml:lang="en">Greek philosopher</ns0:description>
  </rdf:Description>
  <rdf:Description rdf:about="http://dbpedia.org/resource/Aristotle">
    <rdf:type rdf:resource="http://xmlns.com/foaf/0.1/Person"/>
  </rdf:Description>
  <rdf:Description rdf:about="http://dbpedia.org/resource/Aristotle">
    <ns0:name xmlns:ns0="http://xmlns.com/foaf/0.1/" xml:lang="en">Aristotle</ns0:name>
  </rdf:Description>
</rdf:RDF>
'''


def main(file):
    f = open(file, 'r')  # archivo lectura
    #o = open(file + '.out', 'w')  # archivo database modificada

    lines = 13512668  # numero de lineas del archivo, partiendo de 0
    cantidad = 1  # porcentaje que repetire el primer grafo del archivo
    porcLines = (lines * cantidad) / 100  # cantidad de lineas a copiar
    copias = porcLines / 15
    grafo = []

    for linea in f:
        print linea[:-1].strip()
        linea2 = f.next()[:-1]
        print linea2.strip()

        linea3 = f.next()[:-1]
        for j in range(14):
            grafo.append(linea3)
            linea3 = f.next()[:-1]
        grafo.append(linea3)
        break

    copie = 0
    i = 0
    total = lines - porcLines

    for line in f:
        if copie == 0:
            for j in range(copias):
                for g in grafo:
                    print g.strip()
            copie = 1

        if i < total:
            print line[:-1].strip()

        i += 1

    print '</rdf:RDF>'

    f.close()

if __name__ == '__main__':
    file = 'persondata.rdf'
    main(file)

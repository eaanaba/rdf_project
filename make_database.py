#!/usr/bin/env python2
# python 2.7.3 code


def main(file):
    f = open(file, 'r')  # archivo lectura
    o = open(file + '.out', 'w')  # archivo database modificada
    lines = 13512668  # numero de lineas del archivo, partiendo de 0
    cantidad = 20  # porcentaje que repetire el primer grafo del archivo
    porcLines = (lines * cantidad) / 100  # cantidad de lineas a copiar
    copias = porcLines / 15
    grafo = []  # guardo grafoa copiar
    i = 0

    for line in f:
        if i < 2:
            o.write(line)
        elif i > 1 and i < 17:
            grafo.append(line)
        else:
            for j in range(copias):
                for g in grafo:
                    o.write(g)
                    f.next()
            break
        i = i + 1

    print 'comienzo llenar con otro grafo'
    for line in f:
        for k in range(20):
            try:
                f.next()
            except(Exception):
                break
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<ns0:deathDate xmlns:ns0="http://dbpedia.org/ontology/" rdf:datatype="http://www.w3.org/2001/XMLSchema#date">1865-04-15</ns0:deathDate>')
        o.write('</rdf:Description>')
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<ns0:birthPlace xmlns:ns0="http://dbpedia.org/ontology/" rdf:resource="http://dbpedia.org/resource/Kentucky"/>')
        o.write('</rdf:Description>')
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<ns0:birthPlace xmlns:ns0="http://dbpedia.org/ontology/" rdf:resource="http://dbpedia.org/resource/Hardin_County,_Kentucky"/>')
        o.write('</rdf:Description>')
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<ns0:birthDate xmlns:ns0="http://dbpedia.org/ontology/" rdf:datatype="http://www.w3.org/2001/XMLSchema#date">1809-02-12</ns0:birthDate>')
        o.write('</rdf:Description>')
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<ns0:description xmlns:ns0="http://purl.org/dc/elements/1.1/" xml:lang="en">16th President of the United States</ns0:description>')
        o.write('</rdf:Description>')
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<rdf:type rdf:resource="http://xmlns.com/foaf/0.1/Person"/>')
        o.write('</rdf:Description>')
        o.write('<rdf:Description rdf:about="http://dbpedia.org/resource/Abraham_Lincoln">')
        o.write('<ns0:name xmlns:ns0="http://xmlns.com/foaf/0.1/" xml:lang="en">Abraham Lincoln</ns0:name>')
        o.write('</rdf:Description>')

    o.write('</rdf:RDF>')

    f.close()
    o.close()

if __name__ == '__main__':
    file = 'persondata.rdf'
    main(file)

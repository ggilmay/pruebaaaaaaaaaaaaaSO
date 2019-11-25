
all: invoiceYaml

CXXFLAGS=-g
LDFLAGS=-lyaml-cpp

INVOICE_OBJECTS=invoiceYaml.o automata.o

invoiceYaml: $(INVOICE_OBJECTS)
	$(CXX) -o $@ $(INVOICE_OBJECTS) $(LDFLAGS) -pthread -lpthread -lrt

invoiceYaml.o: invoiceYaml.C
	$(CXX) $(CXXFLAGS) -c $<

automata.o: automata.C automata.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.C~ Makefile~

CPPS      = $(wildcard src/*.cpp)
LIBCPPS   = $(wildcard utils/src/*.cpp)
SOURCE    = $(foreach source,$(CPPS),$(notdir $(basename $(source))))
LIBSOURCE = $(foreach source,$(LIBCPPS),$(notdir $(basename $(source))))
OS        = $(foreach source,$(SOURCE),obj/$(source).o)
LIBOS     = $(foreach source,$(LIBSOURCE),utils/obj/$(source).o)
LIB       = lib/libcs240utils.a
MAIN      = main/crawler.cpp
TSTMAIN   = main/test.cpp
MAINO     = obj/crawler.o
TSTMAINO  = obj/test.o
FLAGS     = -Wall -g

bin : bin/crawler

bin/crawler : $(OS) $(LIB) $(MAINO) 
	g++ $(FLAGS) -o $@ $^

test : bin/test
	./bin/test

bin/test : $(TSTMAINO) $(OS) $(LIB)
	g++ $(FLAGS) -o $@ $^

lib : $(LIB)

$(LIB): $(LIBOS)
	ar r $@ $^

clean :
	rm -f bin/* $(OS) $(LIBOS) $(LIB) $(MAINO) $(TSTMAINO)

depends : 
	@ rm -f depends.mk
	@ for f in $(SOURCE); do g++ $(FLAGS) -I inc/ -I utils/inc/ -MM src/$$f.cpp -MT obj/$$f.o >> depends.mk; done
	@ rm -f libdepends.mk
	@ for f in $(LIBSOURCE); do g++ $(FLAGS) -I utils/inc/ -MM utils/src/$$f.cpp -MT utils/obj/$$f.o >> libdepends.mk; done

backup :
	cp inc/*.h back/inc/.
	cp src/*.cpp back/src/.
	cp main/*.cpp back/main/.

$(MAINO) : $(MAIN)
	g++ $(FLAGS) -c -I inc/ -I utils/inc/ -o $@ $<

$(TSTMAINO) : $(TSTMAIN) inc/BST.h
	g++ $(FLAGS) -c -I inc/ -I utils/inc/ -o $@ $<

obj/%.o : src/%.cpp
	g++ $(FLAGS) -c -I inc/ -I utils/inc/ -o $@ $<

utils/obj/%.o : utils/src/%.cpp
	g++ $(FLAGS) -c -I utils/inc/ -o $@ $<

target :
	@ for f in $(LIBCPPS); do echo $$f; done
	@ for f in $(LIBOS); do echo $$f; done

include depends.mk
include libdepends.mk

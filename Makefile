###
## INFO0030: Projet 2
##
###

# Variables
CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes
LDFLAGS=
EXEC_TEST=codebarre_test
EXEC=codebarre
TAR=tar
TARNAME=3
AR=ar
RANLIB=ranlib
DOXYGEN=doxygen
MODULES=codebarre.c pnm.c seatest.c codebarre-test.c pnm-test.c
OBJECTS=codebarre.o pnm.o seatest.o codebarre-test.o pnm-test.o

all: $(EXEC)

clean:
	rm -f *.o $(EXEC) *.a *~

doc:
	$(DOXYGEN) Doc/Doxyfile

test: $(EXEC_TEST)
	$(LD) -o $(EXEC_TEST) 

lib: libpnm.a
	
archive:
	$(TAR) cvf $(TARNAME) Makefile Makefile.compilation Code/ Rapport/

$(EXEC): main.o codebarre.o
	$(LD) -o $(EXEC) main.o codebarre.o $(LDFLAGS)

$(EXEC_TEST): $(OBJECTS)
	$(LD) -o $(EXEC_TEST) $(OBJECTS) $(LDFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

codebarre.o: codebarre.c
	$(CC) -c codebarre.c -o codebarre.o $(CFLAGS)

seatest.o: seatest.c
	$(CC) -c seatest.c -o seatest.o $(CFLAGS)

codebarre-test.o: codebarre-test.c
	$(CC) -c codebarre-test.c -o codebarre-test.o $(CFLAGS)

pnm-test.o: pnm-test.c
	$(CC) -c pnm-test.c -o pnm-test.o $(CFLAGS)

libpnm.a: pnm.o
	$(AR) ruv $@ $?
	$(RANLIB) $@	
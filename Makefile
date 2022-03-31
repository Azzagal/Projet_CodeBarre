###
## INFO0030: Projet 2
##
###

# Variables
CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes
LDFLAGS=-L. -lpnm -L. -lgest
EXEC_TEST=codebarre_test
EXEC=codebarre
TAR=tar
TARNAME=3
AR=ar
RANLIB=ranlib
DOXYGEN=doxygen
MODULES=codebarre.c seatest.c codebarre-test.c pnm.c 

all: $(EXEC)

clean:
	rm -f *.o $(EXEC) $(EXEC_TEST) *.a *~

doc:
	$(DOXYGEN) Doc/Doxyfile

test:
	$(LD) -o $(EXEC_TEST) $(MODULES)

lib: libpnm.a libgest.a

$(EXEC): main.o codebarre.o
	$(LD) -o $(EXEC) main.o codebarre.o $(LDFLAGS) 

codebarre.o: codebarre.c
	$(CC) -c codebarre.c -o codebarre.o $(CFLAGS)

libpnm.a: pnm.o
	$(AR) -rc $@ $^
	$(RANLIB) $@

libgest.a: GestOpt.o
	$(AR) -rc $@ $^
	$(RANLIB) $@	
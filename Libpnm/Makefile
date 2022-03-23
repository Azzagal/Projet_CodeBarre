###
## INFO0030: Projet 2
##
###

include ../Makefile.compilation

# Files
EXEC=libpnm.a
MODULES=pnm.c
OBJECTS=pnm.o

## Rules

all: $(EXEC)

libpnm.a: $(OBJECTS)
	$(AR) ruv $@ $?
	$(RANLIB) $@

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

test:$(OBJECTS_TEST_LIB)
	$(LD) -o $(EXEC_2) $(OBJECTS_2) $(LDFLAGS)

clean:
	rm -f *.o *.a 

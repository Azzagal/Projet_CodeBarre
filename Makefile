###
## INFO0030: Projet 2
##
###
include Makefile.compilation

all:
	cd CodeBarre; make all

clean:
	cd CodeBarre; make clean
	cd Libpnm; make clean

doc:
	$(DOXYGEN) Doc/Doxyfile

test:
	cd CodeBarre; make test
	cd Libpnm; make test 

lib:
	cd Libpnm; make all

archive:
	$(TAR) cvf $(TARNAME) Makefile Makefile.compilation Code/ Rapport/
RMFLAGS=-f
RM=rm
ECHO=@echo
COMP=gcc
EDL=gcc
EXE=math
CPPFLAGS=-Wall -g
EDLFLAGS=
INCPATH=
LIBPATH=
INT=
REAL=main.c binary_tree.c
OBJ=$(REAL:.c=.o)
LIBS=-lpthread -lm
CLEAN=efface

.PHONY:$(CLEAN)
	
$(EXE): $(OBJ)
	$(ECHO) Edition des liens de $(EXE)
	$(EDL) $(EDLFLAGS) $(LIBPATH) -o $(EXE) $(OBJ) $(LIBS)

%.o: %.c
	$(ECHO) Compilation de $<
	$(COMP) $(CPPFLAGS) $(INCPATH) -c $<

main.o: main.c

$(CLEAN):
	$(ECHO) Nettoyage
	$(RM) $(RMFLAGS) $(OBJ) $(EXE)

# cd /cygdrive/c/Users/Damien/Documents/Cours/3IF/binary_tree

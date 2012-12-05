#modifier la valeur de ce paramètre pour compiler avec options debug ou optimisation
TYPE=debug
#	debug / opt
	
CC= g++ -Iinclude
CFLAGS = -W -Wall -ansi -pedantic -pipe
OPT= -O3
EXEC= bin/prog bin/generateur bin/gtk_prog
ifeq ($(TYPE),debug)
	FLAGS=$(CFLAGS) -g
else 
	ifeq ($(TYPE),opt)
		FLAGS=$(CFLAGS) $(OPT)
	else
		FLAGS=$(CFLAGS)
	endif
endif

all : $(EXEC)
bin/prog: Ligne_bdd.o Heure.o Bdd.o main.o Etape.o Comparator.o Solver.o
	$(CC) $^ -o $@ $(FLAGS)
bin/generateur: generateur.o Heure.o
	$(CC) $^ -o $@ $(FLAGS)

bin/gtk_prog: gtk_main_gui.o gtk_Fenetre.o Bdd.o Heure.o Ligne_bdd.o Solver.o Comparator.o
	$(CC) $^ -o $@ $(FLAGS) `pkg-config --libs gtkmm-3.0`

gtk_%.o: src/gtk_%.cpp
	$(CC) -c $^ $(FLAGS) `pkg-config --cflags gtkmm-3.0`
%.o : src/%.cpp
	$(CC)  -c $^ $(FLAGS)
clean:
	@ rm -f *.o
mrproper: clean
	@ rm -f bin/$(EXEC)
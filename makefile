#modifier la valeur de ce paramètre pour compiler avec options debug ou optimisation
TYPE=opt
#	debug / opt
	
CC= g++
CFLAGS = -W -Wall -ansi -pedantic -pipe
OPT= -O3
EXEC= prog
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
prog: Heure.o main.cpp
	$(CC) $^ -o $@ $(FLAGS)

Heure.o: Heure.cpp
	$(CC)  -c $^ $(FLAGS)
clean:
	@ rm -f *.o
mrproper: clean
	@ rm -f $(EXEC)
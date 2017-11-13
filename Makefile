
LIKWID_INCLUDE = /usr/local/include
LIKWID_LIB = /usr/local/lib
LDFLAGS = -fopenmp -pthread -DLIKWID_PERFMON  -I$(LIKWID_INCLUDE) -L$(LIKWID_LIB) -llikwid -lm

all: invmat

invmat: main.c functions.c
	gcc main.c functions.c -o invmat -Wall -O3 -mavx -march=native $(LDFLAGS)
testes: testes.c functions.c
	gcc -o testes testes.c functions.c $(LDFLAGS)

doc:
	doxygen

clean:
	-rm $(objs) *~ invmat

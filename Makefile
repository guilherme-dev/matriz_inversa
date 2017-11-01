
LIKWID_INCLUDE = /usr/local/include
LIKWID_LIB = /usr/local/lib
LDFLAGS = -fopenmp -pthread -DLIKWID_PERFMON  -I$(LIKWID_INCLUDE) -L$(LIKWID_LIB) -llikwid -lm

all: invmat

invmat: main.c functions.c
	gcc main.c functions.c -Wall -O3 -mavx -march=native $(LDFLAGS)

doc:
	doxygen

clean:
	-rm $(objs) *~ invmat

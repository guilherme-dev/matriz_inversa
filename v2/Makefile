CFLAGS = -Wall -O3 -mavx -march=native    # flags de compilacao
LDFLAGS = -fopenmp -pthread -DLIKWID_PERFMON  -I/usr/local/include -L/usr/local/lib -llikwid -lm

all: invmat

invmat: main.c functions.c functions.h
	gcc -o invmat main.c functions.c $(CFLAGS) $(LDFLAGS)

doc:
	doxygen

clean:
	-rm $(objs) *~ invmat

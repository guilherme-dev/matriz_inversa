CFLAGS = -Wall -lm -O3 -mavx -march=native -fstrict-aliasing -ffast-math# flags de compilacao
# -ftree-vectorizer-verbose=1

LDFLAGS = -fopenmp -pthread -DLIKWID_PERFMON  -I/usr/local/include -L/usr/local/lib -llikwid

all: invmat

invmat: main.c functions.c functions.h
	gcc -o invmat main.c functions.c $(CFLAGS) $(LDFLAGS)

doc:
	doxygen

clean:
	-rm $(objs) *~ invmat

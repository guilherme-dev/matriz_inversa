CFLAGS = -Wall -DTESTE    # flags de compilacao
LDFLAGS = -O3 -fopenmp -pthread -DLIKWID_PERFMON  -I/usr/local/include -L/usr/local/lib -llikwid -lm

objs = main.o functions.o

all: invmat

invmat: $(objs)
	gcc -o invmat $(objs) $(CFLAGS) $(LDFLAGS)

main.o: main.c functions.c functions.h
functions.o: functions.c functions.h

doc:
	doxygen

clean:
	-rm $(objs) *~ invmat

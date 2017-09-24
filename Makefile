CFLAGS = -Wall     # flags de compilacao
LDFLAGS = -lm      # flags de ligacao

objs = main.o functions.o

all: invmat

invmat: $(objs)
	gcc -o invmat $(objs) $(LDFLAGS)

main.o: main.c functions.c functions.h
functions.o: functions.c functions.h

doc:
	doxygen

clean:
	-rm $(objs) *~ invmat
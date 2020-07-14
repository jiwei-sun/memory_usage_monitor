CC	?= gcc
CFLAGS	= -c -g -Wall

OBJ	:= $(patsubst %.c,%.o,$(wildcard *.c))

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

all: memusage

memusage: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

clean:
	rm -f *.o *.so *.svg *.log
	rm -f memusage

SRCS = $(wildcard *.c)

LIBS = -lpthread

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	gcc -o $@ $< $(LIBS)

clean:
	rm -f $(PROGS)

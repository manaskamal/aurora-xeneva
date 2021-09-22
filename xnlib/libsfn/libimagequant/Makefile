CC = gcc
CFLAGS = -I. -ffast-math -O3

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(OBJS)

%: %.c
	$(CC) $(CFLAGS) $< -c $@

libimagequant.a: $(OBJS)
	@rm $@ 2>/dev/null || true
	@ar -frsv $@ $^

clean:
	@rm *.a *.o 2>/dev/null || true

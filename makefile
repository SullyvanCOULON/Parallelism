CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

SRCS = heat_seq.c heat_par.c
OBJS = $(SRCS:.c=.o)
EXEC = heat_seq heat_par

all: $(EXEC) $(OBJS)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
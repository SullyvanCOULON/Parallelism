CC = clang
CFLAGS = -Wall -Wextra -O2 -g

SRCS = heat.c
OBJS = $(SRCS:.c=.o)
EXEC = heat

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
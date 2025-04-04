UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    CC = gcc-14
else
    CC = gcc
endif

CFLAGS = -Wall -Wextra -Ofast -g -fopenmp
AR = ar rcs

# Dossiers
SRCDIR = src
OUTDIR = out
LIBDIR = image_lecture

# Fichiers sources et objets
SRCS = $(SRCDIR)/heat_seq.c $(SRCDIR)/heat_par.c $(SRCDIR)/heat_simd.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

# Librairie
LIB_SRCS = $(LIBDIR)/functions.c
LIB_OBJS = $(LIB_SRCS:$(LIBDIR)/%.c=$(OUTDIR)/%.o)
LIB_NAME = libimage.a
LIB_PATH = $(OUTDIR)/$(LIB_NAME)

# Exécutables
EXEC = $(OUTDIR)/heat_seq $(OUTDIR)/heat_par $(OUTDIR)/heat_simd

all: $(LIB_PATH) $(EXEC)

# Compilation des exécutables en utilisant la librairie
$(OUTDIR)/%: $(OUTDIR)/%.o $(LIB_PATH)
	$(CC) $(CFLAGS) -o $@ $^ -L$(OUTDIR) -limage

# Compilation de la librairie statique
$(LIB_PATH): $(LIB_OBJS)
	$(AR) $@ $^

# Compilation des fichiers objets
$(OUTDIR)/%.o: $(SRCDIR)/%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/%.o: $(LIBDIR)/%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier de sortie
$(OUTDIR):
	mkdir -p $@

clean:
	rm -f $(OBJS) $(LIB_OBJS) $(EXEC) $(LIB_PATH)

.PHONY: all clean
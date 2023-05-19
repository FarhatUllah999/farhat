IDIR =.
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=.

LIBS=-lm

_DEPS = buddy.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = buddy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

buddy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) -g

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ buddy

IDIR =../include
CC=g++
CFLAGS=-std=c++11 -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lphtread

_DEPS = RawDoubleSensorModule.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = RawDoubleSensorModule.o simplesimu.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
#$(ODIR)/RawDoubleSensorModule.o: RawDoubleSensorModule.c $(DEPS)
	#$(CC) -c -o $@ $< $(CFLAGS)

simplesimu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

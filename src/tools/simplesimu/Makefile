IDIR =.
CC=g++
CFLAGS=-std=c++11 -Wall -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lphtread


simplesimu: simplesimu.o RawDoubleSensorModule.o
	$(CC) -o $@ $^

simplesimu.o: RawDoubleSensorModule.h
	$(CC) -c simplesimu.cpp $(CFLAGS) $(LIBS)

RawDoubleSensorModule.o: RawDoubleSensorModule.h RawDoubleSensorModule.cpp
	$(CC) -c RawDoubleSensorModule.cpp $(CFLAGS) $(LIBS)

#_DEPS = RawDoubleSensorModule.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#
#_OBJ = RawDoubleSensorModule.o simplesimu.o 
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#
#
#$(ODIR)/%.o: %.c $(DEPS)
	#$(CC) -c -o $@ $< $(CFLAGS)
#$(ODIR)/RawDoubleSensorModule.o: RawDoubleSensorModule.c $(DEPS)
	#$(CC) -c -o $@ $< $(CFLAGS)
#
#simplesimu: $(OBJ)
	#$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

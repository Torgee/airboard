CC = g++
DEBUG = -g
CFLAGS = -g -Wall -std=c++11
LFLAGS = -L/usr/local/lib/

INCLUDES = -I/usr/local/ -I.

LIBS = -lzmq -lpthread

SRCS = simplesimu.cpp RawDoubleSensorModule.cpp

OBJS = $(SRCS:.cpp=.o)

EXECUTABLE = simplesimu

all: $(SRCS) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) *.o *~ $(EXECUTABLE)


CC = g++

CFLAGS =

OBJS = gridmodel.o path.o main.o link.o

flightmodel: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o flightmodel -ll

main.o: gridmodel.h link.h path.h
	$(CC) $(CFLAGS) -c main.cpp

link.o: link.h
	$(CC) $(CFLAGS) -c link.cpp

path.o: path.h
	$(CC) $(CFLAGS) -c path.cpp

gridmodel.o: gridmodel.h
	$(CC) $(CFLAGS) -c gridmodel.cpp

clean:
	rm -f flightmodel $(OBJS)

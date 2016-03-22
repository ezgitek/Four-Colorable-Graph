CC = g++
CFLAGS  = -std=c++11 -g -Wall

project3: project3.o 
	$(CC) $(CFLAGS) project3.o -o project3

project3.o: project3.cpp
	$(CC) $(CFLAGS) -c project3.cpp

clean:
	rm -f *.o
	rm -f project3

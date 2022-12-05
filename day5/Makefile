CC = g++
CFLAGS = -Wall -g -Wno-deprecated
 
day5p2: day5p2.o utils.o
	$(CC) $(CFLAGS) -o day5p2 day5p2.o utils.o
 
day5p2.o: day5p2.cpp utils.h
	$(CC) $(CFLAGS) -c day5p2.cpp
 
utils.o: utils.h

clean:
	$(RM) day5p2 *.o
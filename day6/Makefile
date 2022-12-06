CC = g++
CFLAGS = -g -Wno-deprecated
 
solve: solve.o utils.o
	$(CC) $(CFLAGS) -o solve solve.o utils.o
 
day5p2.o: solve.cpp utils.h
	$(CC) $(CFLAGS) -c solve.cpp
 
utils.o: utils.h

clean:
	$(RM) solve *.o

CXX = clang++
CC = $(CXX)

CXXFLAGS = -g -Wno-deprecated -ggdb -O0 -std=c++2a
CFLAGS = $(CXXFLAGS)
 
default: solve

solve: solve.o
	$(CC) $(CFLAGS) -o solve solve.o
 
clean:
	$(RM) solve *.o

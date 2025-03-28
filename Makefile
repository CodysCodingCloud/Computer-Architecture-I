CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2

PROG ?= main

OBJS = main.o

all: $(PROG)

mainprog: $(PROG)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) *.o *.out

rebuild: clean all

test: $(PROG)
	./$(PROG)

run: all test clean

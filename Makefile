CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2

PROG ?= main

OBJS = main.o

mainprog: $(PROG)

# .cpp.o:
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) *.o *.out

rebuild: clean mainprog

test: $(PROG)
	./$(PROG)

ct: rebuild test
	rm -f *.o
	
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o code main.cpp

clean:
	rm -f code *.o

.PHONY: all clean

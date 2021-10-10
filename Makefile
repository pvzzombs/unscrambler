CXX=g++
CXXFLAGS=-g -O3 -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused 

.PHONY: all clean

all: main

main: precompiledHeader main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

precompiledHeader: main.hpp
	$(CXX) $(CXXFLAGS) main.hpp

clean:
	rm -f *.gch *.exe *.o
# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g
# Target executable
TARGET := trees
# Source files
SRCS := Demo.cpp complex.cpp test.cpp TestCounter.cpp

# Object files main
OBJS := Demo.o complex.o test.o TestCounter.o

# Default target
all: $(TARGET) test

tree : $(TARGET)
	./$(TARGET)

# Linking
$(TARGET): Demo.o complex.o tree.hpp node.hpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling
Demo.o: Demo.cpp complex.hpp tree.hpp node.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

complex.o: complex.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

TestCounter.o: TestCounter.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: test.o TestCounter.o complex.o
	$(CXX) $(CXXFLAGS) $^ -o $@




clean:
	rm -f *.o test $(TARGET)

.PHONY: all clean test tree
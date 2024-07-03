# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra
# Target executable
TARGET := tree
# Source files
SRCS := Demo.cpp complex.cpp test.cpp TestCounter.cpp

TESTS := Test.cpp TestCounter.cpp

# Object files main
OBJS := Demo.o complex.o test.o TestCounter.o

# Default target
all: $(TARGET)

# Linking
$(TARGET): Demo.o complex.o tree.hpp node.hpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling
Demo.o: Demo.cpp complex.hpp tree.hpp node.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

complex.o: complex.cpp complex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test.o: test.cpp test.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

TestCounter.o: TestCounter.cpp TestCounter.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: test.o TestCounter.o
	$(CXX) $(CXXFLAGS) $^ -o $@




clean:
	rm -f $(OBJS) $(TARGET) test $(TESTS)

.PHONY: all clean test
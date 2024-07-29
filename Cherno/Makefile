
# Set g++ as the C++ compiler
CXX = g++

# Enforce C++ 11 as the language standard
CXXFLAGS = -std=c++11 -pedantic

# Enable all standard warnings, uninitialized variable warnings,
# and treat all warnings as errors
CXXFLAGS += -Wall -Wuninitialized -Werror

# Generate code with debugging information
# (for use with a debugger like gdb)
CXXFLAGS += -g

# Link with math library and other required libraries
LDFLAGS = -lm -lglfw -lGLEW -lGL

# Name of executable program
PROG = rooster

# Source files
SRC = main.cpp

# Default target
all: $(PROG)

# Build the target executable
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o rooster $(LDFLAGS)
	./rooster

# Clean up build files
clean:
	rm -f $(PROG)

run:
	./rooster

# Phony targets
.PHONY: all clean


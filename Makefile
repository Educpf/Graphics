
# Set gcc as the C++ compiler
CXX=g++

# Enforce C++ 2011 as the language standard
CXXFLAGS=-std=c++11 -pedantic

# Enable all standard warnings, uninitialized variable warnings, 
# and treat all warnings as errors
CXXFLAGS+= -Wall -Wuninitialized -Werror

# Generate code with debugging information
# (for use with a debugger like gdb)
CXXFLAGS+= -g

# Link with math library
CXXFLAGS+= -lm

# Enable ASan (Address Sanitizer) 
# and UBSan (Undefined Behavior Sanitizer)
#
# NOTE: comment these temporarily if 
# your development environment is failing
# due to these settings - it is important that 
# you fix your environment at some point.
CXXFLAGS+=-fsanitize=address -fsanitize=undefined

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# C++ source files to consider in compilation
CPP_FILES=
# C++ header files to consider in compilation
HEADERS=
# Name of executable program ('main' by default)
PROG=rooster
# Name of the executable




all: rooster

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o rooster

clean:
	rm -f rooster



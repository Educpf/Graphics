# Variables
CXX = g++
CXXFLAGS = -std=c++17 -pedantic
CXXFLAGS += -Wall -Wextra -Wuninitialized -Werror
CXXFLAGS += -g

INCLUDES = -Iinclude
DEPFLAGS = -MMD -MP

# Link with math library and other required libraries
LDFLAGS = -lm -lglfw -lGLEW -lGL

# Source and object files
SRC = Renderer.cpp IndexBuffer.cpp VertexBuffer.cpp VertexArray.cpp Shader.cpp
OBJS = $(SRC:.cpp=.o)
DEPS = $(OBJS:.o=.d)

# Output executable
TARGET = rooster

.PHONY: file

# Default target
all: $(file)

# Rule to link the object files into the executable
$(file): $(file).o $(OBJS)
	$(CXX) $(CXXFLAGS) -o rooster $^ $(LDFLAGS)
	rm -f $(file).o
	./rooster

$(file).o: $(file).cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
# Pattern rule to compile source files into object files with dependency generation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEPFLAGS) -c -o $@ $<

# Include the dependency files
-include $(DEPS)

# Clean rule
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)





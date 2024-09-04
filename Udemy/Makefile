# Variables
CXX = g++
CXXFLAGS = -std=c++17 -pedantic
CXXFLAGS += -Wall -Wextra -Wuninitialized 
CXXFLAGS += -g

INCLUDES = -Iinclude
DEPFLAGS = -MMD -MP

# Link with math library and other required libraries
LDFLAGS = -lm -lglfw -lGLEW -lGL

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
DEPDIR = dep
BINDIR = bin
RESIR = res

# Source and object files
SRCS = $(filter-out $(wildcard $(SRCDIR)/*.cpp), $(wildcard $(SRCDIR)/**/*.cpp))
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(OBJS))

# Resources folder
RESRC = $(wildcard $(RESIR)/**/*)

# Output executable
TARGET = $(BINDIR)/$(file)


all: $(TARGET)


# Rule to link the object files into the executable
$(TARGET): $(OBJDIR)/$(file).o $(OBJS) $(RESRC)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(OBJDIR)/$(file).o $(INCLUDES) -o $(TARGET) $(LDFLAGS)

# Pattern rule to compile source files into object files with dependency generation
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR) $(DEPDIR) $(dir $(OBJDIR)/$*) $(dir $(DEPDIR)/$*)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@mv $(OBJDIR)/$*.d $(DEPDIR)/$*.d


# Include dependency files
-include $(DEPS)

# Clean target to remove intermediate and output files
clean:
	rm -rf $(OBJDIR) $(DEPDIR) $(BINDIR)

# Phony targets
.PHONY: all clean file



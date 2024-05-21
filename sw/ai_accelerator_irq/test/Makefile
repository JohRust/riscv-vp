# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -pedantic -std=c++14

# Include directories
INCLUDES := -I/usr/include

# Library directories
LIB_DIRS := -L/usr/lib/

# Libraries to link
LIBS := -lgtest -lgtest_main

# Source files
DEP_DIR := ../src
SRCS_DEP := $(wildcard $(DEP_DIR)/*.cpp)
SRCS_DEP := $(filter-out $(DEP_DIR)/main.cpp, $(SRCS_DEP)) # Exclude main.cpp
SRCS := $(wildcard *.cpp) # Unit Test files

# Object files
#OBJS := $(BUILDDIR)/$(SRCS:.cpp=.o)
OBJS := $(SRCS:.cpp=.o)
OBJ_DEP := $(patsubst $(DEP_DIR)/%.cpp, %.o, $(SRCS_DEP))

# Executable
TARGET := test_all

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(OBJ_DEP)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_DIRS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build object files for the source files in the src directory
%.o: $(DEP_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(OBJ_DEP)

# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -pedantic -std=c++11

# Include directories
INCLUDES := -I/usr/include

# Library directories
LIB_DIRS := -L/usr/lib/

# Libraries to link
LIBS := -lgtest -lgtest_main

# Source files
SRCS := test.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable
TARGET := test

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_DIRS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

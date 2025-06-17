# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -mwindows -lgdi32 -static

# Target executable
TARGET = main.exe

# Source files
SRCS = main.cpp \
       L0/l0.cpp \
	   L1/l1.cpp \
       master/master.cpp \
	   graphics/graphics.cpp

# Default target
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)

.PHONY: all clean
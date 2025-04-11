# CXX = g++
# CXXFLAGS = -std=c++11 -I/usr/include/jsoncpp
# LDFLAGS = -ljsoncpp

# TARGET = json_reader
# SRCS = json_reader.cpp
# OBJS = $(SRCS:.cpp=.o)

# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean:
# 	rm -f $(TARGET) $(OBJS)

# .PHONY: all clean

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -mwindows -lgdi32 -static

# Target executable
TARGET = main.exe

# Source files
SRCS = main.cpp

# Default target
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)

.PHONY: all clean
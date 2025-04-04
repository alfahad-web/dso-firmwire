# Compiler and flags
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS  = -lX11

# Targets
TARGET   = main
SRC      = main.cpp
OBJ      = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
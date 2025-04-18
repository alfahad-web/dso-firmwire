# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -mwindows -lgdi32 -static

# Target executable
TARGET = main.exe

# Source files
SRCS = main.cpp \
       global/global.cpp \
       ui_layers/0_background/bg.cpp \
       ui_layers/1_graphing/graphing.cpp \
       ui_layers/2_axis/axis.cpp \
       ui_layers/3_axis_annotations/axis_annotations.cpp \
       ui_layers/4_wave_reading/wave_reading.cpp \
       ui_layers/5_annotations/annotations.cpp \
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
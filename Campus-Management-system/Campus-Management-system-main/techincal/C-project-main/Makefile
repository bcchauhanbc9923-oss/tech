# Makefile for Campus Navigation System
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LDFLAGS = -lm

SOURCES = src/Building.cpp src/CampusGraph.cpp src/NavigationServer.cpp src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = navigate

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned up object files and executable"

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.DEFAULT: all

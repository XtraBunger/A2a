CXX = g++
CXXFLAGS = -g -Wall -std=c++20

TARGET = TestBiMap
OBJECTS = TestBiMap.o QuadraticProbing.o

# Build all targets
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
TestBiMap.o: TestBiMap.cpp BiMap.h QuadraticProbing.cpp
	$(CXX) $(CXXFLAGS) -c TestBiMap.cpp

QuadraticProbing.o: QuadraticProbing.cpp BiMap.h
	$(CXX) $(CXXFLAGS) -c QuadraticProbing.cpp

# Clean up build files
clean:
	del /F /Q $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

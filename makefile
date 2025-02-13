CXX = g++
CXXFLAGS = -g -Wall -std=c++20

TARGET = TestBiMap
OBJECTS = TestBiMap.o QuadraticProbing.o

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
	rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

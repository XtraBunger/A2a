GXX = g++
CFLAGS = -g -Wall -std=c++20
TARGET = BiMapTest
OBJECTS = TestBiMap.o

# Build target
$(TARGET): $(OBJECTS)
	$(GXX) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
TestBiMap.o: TestBiMap.cpp BiMap.h QuadraticProbing.cpp
	$(GXX) $(CFLAGS) -c TestBiMap.cpp

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run:
	./$(TARGET)

# Makefile

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files and object files
SRCS = code.cpp response.cpp mastermind.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean generated files
clean:
	rm -f $(OBJS) $(TARGET)

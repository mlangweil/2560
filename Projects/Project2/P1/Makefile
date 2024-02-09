.PHONY: all clean

CC = g++
CXXFLAGS = -std=c++11 -Wall
LINKERFLAG = -lm

SRCS := Card.cpp Node.cpp Deck.cpp main.cpp
OBJS := $(SRCS:.cpp=.o)
BINS := main

all: $(BINS)

main: $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LINKERFLAG)

%.o: %.cpp
	@echo "Creating object.."
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm Card.o main.o Deck.o Node.o
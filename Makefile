# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)

OBJ := $(SOURCES:.cpp=.o)

all:game

run:game
	./game.exe

*.o: *.cpp
		g++ -c $^

game: *.o
		g++ $^ $(LIBS) -o $@ 

clean:
		rm *.o *.exe

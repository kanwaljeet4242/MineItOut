# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

LIBS = -lopengl32 -lglew32 -lfreeglut -lglu32 -lglfw3

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

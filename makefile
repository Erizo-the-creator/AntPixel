LIBS = -L lib -l SDL2main -l mingw32 -l SDL2 

FLAGS = -mwindows 

all: compile link

compile:
	g++ -I include -c *.cc $(FLAGS)
link:
	g++ main.o -o bin/AntPixel.exe $(LIBS)	
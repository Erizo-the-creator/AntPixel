LIBS = -L lib  -l SDL2main -l SDL2 

all: compile link

compile:
	g++ -I include -c *.cc 

link:
	g++ main.o -o bin/AntPixel.exe $(LIBS)	
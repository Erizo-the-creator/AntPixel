# If on windows..
ifeq ($(OS), Windows_NT)
	LIBS += -L lib
	INCLUDE += -Iinclude
	OUT = -o bin/windows/AntPixel.exe
	CLEAN = del *.o
else
	OUT = -o bin/linux/AntPixel
	CLEAN = rm *.o
endif

LIBS += -l SDL2main -l SDL2 
SRCS = -c src/*.cc
OBJS = main.o game.o

all: compile link clean

compile:
	g++ $(INCLUDE) $(SRCS)

link:
	g++ $(OUT) $(OBJS) $(LIBS)

clean:
	$(CLEAN)
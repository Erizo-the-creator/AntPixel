# If on windows..
ifeq ($(OS), Windows_NT)
	LIBS += -Llib
	INCLUDE += -Iinclude
	OUT = -o bin/windows/AntPixel.exe
	CLEAN = del *.o
else
	OUT = -o bin/linux/AntPixel
	CLEAN = rm *.o
endif

LIBS += -lSDL2main -lSDL2 
CFLAGS =
SRCS = -c src/*.cc
OBJS = main.o

all: compile link clean

compile:
	g++ $(INCLUDE) $(SRCS)

link:
	g++ $(OUT) $(LIBS) $(OBJS)

clean:
	$(CLEAN)
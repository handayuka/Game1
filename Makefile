CC=gcc -g
RM=rm
CFLAGS= -I.
HEADERS= bidlist.h event.h  movingobject.h object.h  scenario.h  vector2.h \
 gameio.h  movingobjectmanager.h screen.h walls.h enemy.h enemy36.h enemy363.h enemy34.h
OBJS= gameio.o screen.o walls.o vector2.o object.o movingobject.o
OBJSPLUS= $(OBJS) movingobjectmanager.o bidlist.o event.o scenario.o enemy.o enemy36.o enemy363.o enemy34.o

.SUFFIXES: .c .o

.PHONY: clean

.c.o: $(HEADERS)
	$(CC) -c $(CFLAGS) $<

all: game2
	./game2

game2: $(OBJSPLUS) gamemain2.o 
	$(CC) -o $@ $^ -lcurses

debug: $(OBJSPLUS) log.o gamemain2.o 
	$(CC) -o $@ $^ -lcurses

game1: game
	./game

game: $(OBJSPLUS) gamemain.o 
	$(CC) -o $@ $^ -lcurses

clean:
	$(RM) -rf *.o game game2 debug

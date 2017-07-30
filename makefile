
EXE=bots
FILE=a1.c
CC=g++
FLAGS=-lrt -pthread

make:
	$(CC) $(FLAGS) $(FILE) -o $(EXE)
clean:
	rm QUOTE.txt
	rm bots


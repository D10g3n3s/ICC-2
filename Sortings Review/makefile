CC = gcc
SOURCES = sources/sortings.c
INCLUDES = ./includes
BINARY = ./main
PROG = sources/main.c
FLAGS = -Wall -Werror -g -lm

all:
	@$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I $(INCLUDES) $(FLAGS)

run:
	@$(BINARY)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BINARY)

zip:
	zip -r Sortings.zip includes sources main makefile
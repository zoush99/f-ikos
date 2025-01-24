# Makefile for simple C project

# CC = ikos-scan-cc
CFLAGS = -I./include

SRC = main.c utils.c
OBJ = $(SRC:.c=.o)
EXEC = my_program

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)


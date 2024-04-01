CC := gcc
FLAGS := -Wall -Wextra -std=c99
SRC := src/bitmanip.c
DEST := bitmanip

all: $(DEST)

$(DEST): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(DEST)

clean:
	rm -f $(DEST)

CC=gcc
CFLAGS=-Wextra -g
OBJ=main.o author_trie.o author.o book_trie.o book.o commands.o utils.o
TARGET=tema3

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) *~

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

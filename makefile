OBJECTS = bst_tree.o tree_of_users.o movie_list_node.o main.o
CFLAGS = -Wall -Wextra -std=c11 -O2
CC = gcc

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)
	
bst_tree.o: bst_tree.c
	$(CC) $(CFLAGS) -c -o bst_tree.o bst_tree.c
	
tree_of_users.o: tree_of_users.c
	$(CC) $(CFLAGS) -c -o tree_of_users.o tree_of_users.c
	
movie_list_node.o: movie_list_node.c
	$(CC) $(CFLAGS) -c -o movie_list_node.o movie_list_node.c
	
main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	
clean:
	-rm main $(OBJECTS)
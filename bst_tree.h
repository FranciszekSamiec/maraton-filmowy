#include <stdbool.h>
#include "structures.h"

#ifndef BST_TREE_H
#define BST_TREE_H

// Funkcja tworzy drzewo binarnych poszukiwań.
extern bst_tree *create_bst_tree();

// Funkcja zwalnia całe drzewo bst którego korzeniem jest
// węzeł "tree".
extern void free_tree(bst_tree *tree);

// Funkcja wstawia do drzewa bst ocene filmu "current_movie".
// Po infixowym przejściu drzewa filmy będą wypisane w kolejności malejących
// identyfikatorów.
extern void insert_movie_rating_to_bst_tree(movie_list_node *current_movie, 
                                     bst_tree *tree);

// Funkcja tworzy listę filmów znajdujących się w drzewie bst.
// oceny filmów będą posortowane malejąco.
extern void insert_movies_to_list_from_bst_tree(movie_list_node **list, bst_tree *tree, 
                                         int highest_movie_rating, int *k, 
                                         movie_list_node **previous, 
                                         bool *delay_is_done); 

#endif /* BST_TREE_H */
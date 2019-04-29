#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "bst_tree.h"

bst_tree *create_bst_tree() {
    bst_tree *bst_root = (bst_tree*)malloc(sizeof(bst_tree));
    if (bst_root == NULL)
        exit(1);
    bst_root->left_son = NULL;
    bst_root->right_son = NULL;
    
    return bst_root;
}

void insert_movie_rating_to_bst_tree(movie_list_node *current_movie, 
                                     bst_tree *tree) {
    int movie = current_movie->movie_rating;
    if (movie > tree->value) {
        if (tree->left_son != NULL) {
            insert_movie_rating_to_bst_tree(current_movie, tree->left_son);
        } else {
            tree->left_son = (bst_tree*)malloc(sizeof(bst_tree));
            if (tree->left_son == NULL)
                exit(1);
            (tree->left_son)->value = movie;
            (tree->left_son)->right_son = NULL;
            (tree->left_son)->left_son = NULL;
        }
    } else if (movie < tree->value) {
        if (tree->right_son != NULL) {
            insert_movie_rating_to_bst_tree(current_movie, tree->right_son);
        } else {
            tree->right_son = (bst_tree*)malloc(sizeof(bst_tree));
            if (tree->right_son == NULL)
                exit(1);
            (tree->right_son)->value = movie;
            (tree->right_son)->right_son = NULL;
            (tree->right_son)->left_son = NULL;
        }
    }
}

void free_tree(bst_tree *tree) {
    if (tree != NULL) {
        free_tree(tree->left_son);
        free_tree(tree->right_son);
        free(tree);
    }
}

void insert_movies_to_list_from_bst_tree(movie_list_node **list, bst_tree *tree, 
                                         int highest_movie_rating, int *k, 
                                         movie_list_node **previous, 
                                         bool *delay_is_done) {
    if (tree != NULL) {
        insert_movies_to_list_from_bst_tree(list, tree->left_son, 
                                            highest_movie_rating, k, 
                                            previous, delay_is_done);
        if (tree->value > highest_movie_rating && (*k) > 0) {
            if ((*delay_is_done) == true) 
                (*previous) = (*previous)->next_movie;
            (*list)->movie_rating = tree->value;
            (*list)->next_movie = (movie_list_node*)malloc(sizeof(movie_list_node));
            if ((*list)->next_movie == NULL)
                exit(1);
            (*list) = (*list)->next_movie;
            (*k)--;
            (*delay_is_done) = true;
        }
        insert_movies_to_list_from_bst_tree(list, tree->right_son, 
                                            highest_movie_rating, k, 
                                            previous, delay_is_done);
    }
}
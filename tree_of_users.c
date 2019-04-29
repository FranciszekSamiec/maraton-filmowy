#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "tree_of_users.h"
#include "bst_tree.h"
#include "movie_list_node.h"

void initialize_tree() {
    this_field_is_empty =
    (tree_node*)malloc(sizeof(tree_node));
    if (this_field_is_empty == NULL)
        exit(1);
    this_field_is_empty->movie_preferences = NULL;
    
    for (int i = ROOT_USER_ID; i <= MAX_USER_ID; i++) {
        array_of_user_id[i] = this_field_is_empty;
    }
    
    tree_node *root = (tree_node*)malloc(sizeof(tree_node));
    if (root == NULL)
        exit(1);
    root->beginning_of_son_list = (list_node*)malloc(sizeof(list_node));
    if (root->beginning_of_son_list == NULL)
        exit(1);
    root->end_of_son_list = (list_node*)malloc(sizeof(list_node));
    if (root->end_of_son_list == NULL)
        exit(1);
    (root->beginning_of_son_list)->next_list_node = root->end_of_son_list;
    (root->end_of_son_list)->son = this_field_is_empty;
    root->brother_list = (list_node*)malloc(sizeof(list_node));
    if (root->brother_list == NULL)
        exit(1);
    array_of_user_id[ROOT_USER_ID] = root;
    root->movie_preferences = NULL;
}

void addUser(int parentUserId, int userId) {
    if (array_of_user_id[userId] == this_field_is_empty &&
        array_of_user_id[parentUserId] != this_field_is_empty
    ) {
        list_node *new_node = (list_node*)malloc(sizeof(list_node));
        if (new_node == NULL) 
            exit(1);
        list_node *following_node =
        (array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node;
        (array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node =
        new_node;
        new_node->previous_list_node = array_of_user_id[parentUserId]->beginning_of_son_list;
        new_node->next_list_node = following_node;
        following_node->previous_list_node = new_node;
        ((array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node)->son = 
        (tree_node*)malloc(sizeof(tree_node));
        if (((array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node)->son == NULL)
            exit(1);
        (((array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node)->son)->brother_list = 
        (array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node;
        array_of_user_id[userId] = 
        ((array_of_user_id[parentUserId]->beginning_of_son_list)->next_list_node)->son;
        array_of_user_id[userId]->beginning_of_son_list =
        (list_node*)malloc(sizeof(list_node));
        if (array_of_user_id[userId]->beginning_of_son_list == NULL)
            exit(1);
        array_of_user_id[userId]->end_of_son_list = (list_node*)malloc(sizeof(list_node));
        if (array_of_user_id[userId]->end_of_son_list == NULL)
            exit(1);
        (array_of_user_id[userId]->beginning_of_son_list)->next_list_node = 
        array_of_user_id[userId]->end_of_son_list;
        (array_of_user_id[userId]->end_of_son_list)->son = this_field_is_empty;
        array_of_user_id[userId]->movie_preferences = NULL;
        
        printf("ok\n");
    } else {
        printf("ERROR\n");
    }
}

void free_son_node(tree_node *son) {
    free(son->beginning_of_son_list);
    free(son->brother_list);
    free(son->end_of_son_list);
    free(son);
}

void delUser(int userId) {
    if (userId != ROOT_USER_ID && array_of_user_id[userId] != this_field_is_empty) {
        if (array_of_user_id[userId]->movie_preferences != NULL) {
            movie_list_node *previous = array_of_user_id[userId]->movie_preferences; 
            movie_list_node *current = 
            (array_of_user_id[userId]->movie_preferences)->next_movie;
            
            while (current != NULL) {
                free(previous);
                previous = current;
                current = current->next_movie;
            }
            free(previous);
        }

        if ((array_of_user_id[userId]->beginning_of_son_list)->next_list_node != 
            array_of_user_id[userId]->end_of_son_list) {
            list_node *following_list_node = 
            (array_of_user_id[userId]->brother_list)->next_list_node;
            ((array_of_user_id[userId]->brother_list)->previous_list_node)->next_list_node =
            (array_of_user_id[userId]->beginning_of_son_list)->next_list_node;
            ((array_of_user_id[userId]->beginning_of_son_list)->next_list_node)->previous_list_node = 
            (array_of_user_id[userId]->brother_list)->previous_list_node;
            ((array_of_user_id[userId]->end_of_son_list)->previous_list_node)->next_list_node = 
            following_list_node;
            following_list_node->previous_list_node =
            (array_of_user_id[userId]->end_of_son_list)->previous_list_node;
            
            free_son_node(array_of_user_id[userId]);
            array_of_user_id[userId] = this_field_is_empty;
        } else {
            ((array_of_user_id[userId]->brother_list)->previous_list_node)->next_list_node =
            (array_of_user_id[userId]->brother_list)->next_list_node;
            ((array_of_user_id[userId]->brother_list)->next_list_node)->previous_list_node =
            (array_of_user_id[userId]->brother_list)->previous_list_node;
            
            free_son_node(array_of_user_id[userId]);
            array_of_user_id[userId] = this_field_is_empty;
        }
        
        printf("ok\n");
    } else {
        printf("ERROR\n");
    }
}

movie_list_node *find_k_best_movies_to_marathon(list_of_movie_lists *movie_lists, 
                                                movie_list_node 
                                                *movie_preferences_of_current_node, 
                                                int k) {
    list_of_movie_lists *current_list = movie_lists;
    movie_list_node *current_movie;
    bool is_at_least_one_movie_rating = false;
    bst_tree *bst_root = create_bst_tree();
    
    while (current_list != NULL) {
        current_movie = current_list->movie_list;
        
        while (current_movie != NULL) {
            if(!is_at_least_one_movie_rating)
                bst_root->value = (current_list->movie_list)->movie_rating;
            is_at_least_one_movie_rating = true;
            insert_movie_rating_to_bst_tree(current_movie, bst_root);
            current_movie = current_movie->next_movie;
        }
        
        current_list = current_list->next_movie_list;
    }
    
    movie_list_node *new_list = 
    (movie_list_node*)malloc(sizeof(movie_list_node));
    if (new_list == NULL)
        exit(1);
    movie_list_node *beginning_of_new_list = new_list;
    movie_list_node *previous_movie = new_list;
    bool delay_is_done = false;
    
    if (is_at_least_one_movie_rating) {
        int highest_movie_rating;
        
        if (movie_preferences_of_current_node != NULL) {
            highest_movie_rating = 
            movie_preferences_of_current_node->movie_rating;
        } else { 
            highest_movie_rating = 0;
        }

        insert_movies_to_list_from_bst_tree(&new_list, bst_root, highest_movie_rating,
                                            &k, &previous_movie, &delay_is_done);

        if (delay_is_done) {
            free(new_list);
            previous_movie->next_movie = NULL;
        }
        new_list = previous_movie;
    }
            
    free_tree(bst_root);
    
    if (k > 0 && movie_preferences_of_current_node != NULL) {
        current_movie = movie_preferences_of_current_node;
        if (!is_at_least_one_movie_rating) {
            new_list->movie_rating = current_movie->movie_rating;
            current_movie = current_movie->next_movie;
            k--;
            while (current_movie != NULL && k > 0) {
            new_list->next_movie = (movie_list_node*)malloc(sizeof(movie_list_node));
            if (new_list->next_movie == NULL)
                exit(1);
            new_list = new_list->next_movie;
            new_list->movie_rating = current_movie->movie_rating;
            current_movie = current_movie->next_movie;;
            k--;
            }
            new_list->next_movie = NULL;
        } else {
            while (k > 0 && current_movie != NULL) {
                if (delay_is_done) {
                new_list->next_movie = (movie_list_node*)malloc(sizeof(movie_list_node));
                if (new_list->next_movie == NULL)
                    exit(1);
                new_list = new_list->next_movie;
                new_list->movie_rating = current_movie->movie_rating;
                
                current_movie = current_movie->next_movie;
                k--;
                } else {
                    new_list->movie_rating = current_movie->movie_rating;
                    current_movie = current_movie->next_movie;
                    delay_is_done = true;
                }
            }
            new_list->next_movie = NULL;
        }
    }
    
    if (is_at_least_one_movie_rating == false &&
        movie_preferences_of_current_node == NULL) {
        free(new_list);
        return NULL;
    } else {
        return beginning_of_new_list;
    }
}

void marathon_recursion(tree_node *user, int k, 
                        movie_list_node **list_of_movies_given_by_parent) {
    list_node *current_son = (user->beginning_of_son_list)->next_list_node;
    list_of_movie_lists *current_list_of_movies = 
    (list_of_movie_lists*)malloc(sizeof(list_of_movie_lists));
    if (current_list_of_movies == NULL)
        exit(1);
    list_of_movie_lists *beginning_of_list_of_movie_lists =
    current_list_of_movies;
    
    while (current_son->son != this_field_is_empty) {
        marathon_recursion(current_son->son, k, &current_list_of_movies->movie_list);
        
        current_son = current_son->next_list_node;
        if (current_son->son != this_field_is_empty) {
            current_list_of_movies->next_movie_list = 
            (list_of_movie_lists*)malloc(sizeof(list_of_movie_lists));
            if (current_list_of_movies->next_movie_list == NULL)
                exit(1);
            current_list_of_movies = current_list_of_movies->next_movie_list;
        }
        
    }
    current_list_of_movies->next_movie_list = NULL;
    
    if ((user->beginning_of_son_list)->next_list_node == user->end_of_son_list) {
        beginning_of_list_of_movie_lists->movie_list = NULL;
        if (user->movie_preferences != NULL && (user->movie_preferences)->next_movie != NULL) {
            movie_list_node *current_movie_list_node = (user->movie_preferences)->next_movie;
            movie_list_node *new_list = (movie_list_node*)malloc(sizeof(movie_list_node));
            if (new_list == NULL)
                exit(1);
            (*list_of_movies_given_by_parent) = new_list;
            new_list->movie_rating = current_movie_list_node->movie_rating;
            current_movie_list_node = current_movie_list_node->next_movie;
            k--;
            while (k > 0 && current_movie_list_node != NULL) {
                new_list->next_movie = (movie_list_node*)malloc(sizeof(movie_list_node));
                if (new_list->next_movie == NULL)
                    exit(1);
                new_list = new_list->next_movie;
                new_list->movie_rating = current_movie_list_node->movie_rating;
                current_movie_list_node = current_movie_list_node->next_movie;
                k--;
            }
            new_list->next_movie = NULL;
        } else {
            (*list_of_movies_given_by_parent) = NULL;
        }
    } else {
        if (user->movie_preferences != NULL) {
        (*list_of_movies_given_by_parent) =
        find_k_best_movies_to_marathon(beginning_of_list_of_movie_lists, 
                                       (user->movie_preferences)->next_movie, k);
        } else {
            (*list_of_movies_given_by_parent) =
            find_k_best_movies_to_marathon(beginning_of_list_of_movie_lists, 
                                           user->movie_preferences, k);
        }
    }
    
    free_list_of_movie_lists(beginning_of_list_of_movie_lists);
}

void free_list_of_movie_lists(list_of_movie_lists *current_list) {
    list_of_movie_lists *previous_list = current_list;
    movie_list_node *current_movie;
    movie_list_node *previous_movie;
    
    while (current_list != NULL) {
        current_movie = current_list->movie_list;
        previous_movie = current_movie;
        while (current_movie != NULL) {
            current_movie = current_movie->next_movie;
            free(previous_movie);
            previous_movie = current_movie;
        }
        current_list = current_list->next_movie_list;
        free(previous_list);
        previous_list = current_list;
    }

}

void free_tree_of_users(tree_node *user) {
    list_node *current_son = (user->beginning_of_son_list)->next_list_node;
    list_node *previous_son;
    
    while (current_son->son != this_field_is_empty) {
        previous_son = current_son;
        current_son = current_son->next_list_node;
        free_tree_of_users(previous_son->son);
    }
    
    free_list_of_movies(user->movie_preferences);
    free_son_node(user);
}

void marathon(int userId, int k) {
    if (array_of_user_id[userId] != this_field_is_empty) {
        if (k > 0) {
            movie_list_node *list_of_movies_returned_by_marathon;
            marathon_recursion(array_of_user_id[userId], k,
                            &list_of_movies_returned_by_marathon);
            show_list(list_of_movies_returned_by_marathon);
            free_list_of_movies(list_of_movies_returned_by_marathon);
        } else {
            printf("NONE\n");
        }
    } else {
        printf("ERROR\n");
    }
}
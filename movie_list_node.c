#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

void create_list_of_movies(int userId) {
    array_of_user_id[userId]->movie_preferences = 
    (movie_list_node*)malloc(sizeof(movie_list_node));
    if (array_of_user_id[userId]->movie_preferences == NULL)
        exit(1);
    (array_of_user_id[userId]->movie_preferences)->next_movie = NULL;
    (array_of_user_id[userId]->movie_preferences)->movie_rating = -1;
}

void show_list(movie_list_node *beginning) {
    if (beginning != NULL) {
        movie_list_node *akt = beginning;
        while (akt != NULL) {
            printf("%d", akt->movie_rating);
            akt = akt->next_movie;
            if (akt != NULL)
                printf(" ");
        }
        printf("\n");
    } else {
        printf("NONE\n");
    }
}

void free_list_of_movies(movie_list_node *current_movie) {
    movie_list_node *previous_movie = current_movie;
    
    while (current_movie != NULL) {
        current_movie = current_movie->next_movie;
        free(previous_movie);
        previous_movie = current_movie;
    }
}

void addMovie(int userId, int movieRating) {
    if (array_of_user_id[userId] != this_field_is_empty) {
        if (array_of_user_id[userId]->movie_preferences == NULL) 
            create_list_of_movies(userId);
        
        
        movie_list_node *current_movie = 
        (array_of_user_id[userId]->movie_preferences)->next_movie;
        movie_list_node *previous_movie = 
        array_of_user_id[userId]->movie_preferences;
        
        while (current_movie != NULL && current_movie->movie_rating > movieRating) {
            current_movie = current_movie->next_movie;
            previous_movie = previous_movie->next_movie;
        }
        if (current_movie != NULL && current_movie->movie_rating == movieRating) {
            printf("ERROR\n");
        } else {
            
            movie_list_node *new_movie = 
            (movie_list_node*)malloc(sizeof(movie_list_node));
            if (new_movie == NULL)
                exit(1);
            previous_movie->next_movie = new_movie;
            new_movie->next_movie = current_movie;
            new_movie->movie_rating = movieRating;
            
            printf("ok\n");
        }
    } else {
        printf("ERROR\n");
    }
}
    
void delMovie(int userId, int movieRating) {
    if (array_of_user_id[userId]->movie_preferences == NULL) {
        printf("ERROR\n");
    } else {
        movie_list_node *previous = array_of_user_id[userId]->movie_preferences;
        movie_list_node *current = 
        (array_of_user_id[userId]->movie_preferences)->next_movie;

        while (current != NULL && current->movie_rating != movieRating) {
            current = current->next_movie;
            previous = previous->next_movie;
        }
                
        if (current == NULL) {
            printf("ERROR\n");    
        } else {
            previous->next_movie = current->next_movie;
            free(current);
            printf("ok\n");
        }
    }
}
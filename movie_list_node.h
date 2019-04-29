#include "structures.h"

#ifndef MOVIE_LIST_NODE_H
#define MOVIE_LIST_NODE_H

// Funkcja tworzy pierwszy węzeł listy, będący atrapą.
extern void create_list_of_movies(int userId);

// Funkcja zwalnia całą liste filmów poczynając od węzłą 
// "current_movie".
extern void free_list_of_movies(movie_list_node *current_movie);

// Funkcja show_list wypisuje listę filmów poczynając od węzła
// "beginning". Procedura ta wywoływana jest jedynie w operacji "marathon".
extern void show_list(movie_list_node *beginning);

// Funkcja dodaje film z oceną movieRating do preferencji 
// użytkownika userId.
extern void addMovie(int userId, int movieRating);

// Funkcja usuwa film z oceną movieRating z preferencji 
// użytkownika userId.
extern void delMovie(int userId, int movieRating);

#endif /* MOVIE_LIST_NODE_H */

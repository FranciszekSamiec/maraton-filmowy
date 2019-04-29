#include "structures.h"

#ifndef TREE_OF_USERS_H
#define TREE_OF_USERS_H

// Funkcja inicjuje drzewo użytkowników oraz przygotowywuje tablice
// "array_of_user_id, tworzony jest korzeń, czyli węzeł użytkownika 
// o identyfikatorze 0.
extern void initialize_tree();

// Funkcja dodaje użytkownika do drzewa jako syna użytkownika o
// identyfikatorze parentUserId.
extern void addUser(int parentUserId, int userId);

// Funkcja usuwa węzeł użytkownika "son" bez jego listy filmów.
extern void free_son_node(tree_node *son);

// Funkcja usuwa użytkownika userId z drzewa.
extern void delUser(int userId);

// Funkcja odpowiada za znalezienie k odpowiednich
// identyfikatorów filmów w operacji marathon. Argumentami są 
// lista list filmów synów danego użytkownika oraz lista filmów
// danego użytkownika. Funkcja wyznacza odpowiednie filmy na podstawie 
// tych dwóch struktur.
extern movie_list_node *find_k_best_movies_to_marathon(list_of_movie_lists *movie_lists, 
                                                movie_list_node 
                                                *movie_preferences_of_current_node, 
                                                int k);

// Funkcja rekurencyjnie wywołująca operacje marathon
// na odpowiednich węzlach drzewa użytkowników.
// Funkcja przekazuje "od dołu" liste filmów będącą wynikiem
// jej działania.
extern void marathon_recursion(tree_node *user, int k, 
                        movie_list_node **list_of_movies_given_by_parent);

// Funkcja sprawdzająca poprawność parametrów komendy i
// wywołująca rekurencje.
extern void marathon(int userId, int k);


// Funkcja zwalnia listę list filmów, która jest używana w funkcji
// "find_k_best_movies_to_marathon".
extern void free_list_of_movie_lists(list_of_movie_lists *current_list);

// Funkcja zwalnia całe drzewo użytkowników wraz z korzeniem.
extern void free_tree_of_users(tree_node *user);

#endif /* TREE_OF_USERS_H */
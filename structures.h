#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_USER_ID 65535
#define ROOT_USER_ID 0

// Struktura list_of_movies jest listą przechowującą 
// oceny filmów, pierwszy węzeł jest atrapą, ułatwia to operacje
// na liście.
typedef struct list_of_movies {
    struct list_of_movies *next_movie;
    int movie_rating;
} movie_list_node;

// Jest to struktura będąca listą początków list filmów
// "movie_list_node" ta sktruktura bedzie wykorzystywana w funkcji
// marathon.
typedef struct list_of_movie_lists {
    struct list_of_movie_lists *next_movie_list;
    movie_list_node *movie_list;
} list_of_movie_lists;

struct list;

// Struktura "tree_node" składa się z węzłów które 
// pokazują na początek i koniec listy dowiązań do synów.
// Każdy węzeł pokazuje również na liste braci oraz listę 
// filmów jakie ma dany użytkownik w preferencjach.
typedef struct tree {
    struct list *beginning_of_son_list; 
    struct list *end_of_son_list;
    struct list *brother_list;
    struct list_of_movies *movie_preferences;
} tree_node;

// Struktura "list_node" to lista wskaźników na węzły drzewa.
// Pierwszy i ostatni element listy wskaźników na synów są atrapami. 
// Ostatni element listy będzie pokazywał na pole "this_field_is_empty"
// dla zaznaczenia iż jest to koniec listy.
typedef struct list {
    struct tree *son;
    struct list *next_list_node;
    struct list *previous_list_node;
} list_node;

// Strukutra bst_tree jest drzewem binarnych poszukiwań,
// będzie ona służyć do sortowania identyfikatorów filmów w funkcji
// "marathon".
typedef struct bst_tree {
    struct bst_tree *left_son;
    struct bst_tree *right_son;
    int value;
} bst_tree;


// Poniższa tablica zawiera wskaźniki do węzłów drzewa.
// Każdemu węzłowi odpowiada pewien użytkownik.
// Rozmiar to MAX_USER_ID + 1 gdyż uwzględniamy identyfikator 0.
// Początkowo tablica będzie zainicjalizowana na pole 
// "this_field_is_empty" aby rozpoznawać którzy użytkownicy 
// są dodani do struktury.
tree_node *array_of_user_id[MAX_USER_ID + 1];

// Węzeł "this_field_is_empty" jest sztuczny, jeżeli 
// element tablicy pokazuje na to pole to znaczy że jest
// on niezainicjowany. Na ten węzeł będą również pokazywać
// ostatnie węzły list dowiązań do synów w strukturze "tree_node". 
tree_node *this_field_is_empty;

#endif /* STRUCTURES_H */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "movie_list_node.h"
#include "bst_tree.h"
#include "tree_of_users.h"

#define MAX_LENGTH_OF_ARRAY 25
// Maksymalna długość wiersza może wynosić 25 znaków,
// nie licząc znaku nowej lini.
#define COMMAND_ADDUSER "addUser"
#define COMMAND_DELUSER "delUser"
#define COMMAND_ADDMOVIE "addMovie"
#define COMMAND_DELMOVIE "delMovie"
#define COMMAND_MARATHON "marathon"
#define LENGTH_OF_COMMAND_ADDUSER 7
#define LENGTH_OF_COMMAND_ADDMOVIE 8
// Definiuje długości jedynie dwóch komend,
// gdyż pozostałe komendy mają długości należące
// do tego dwu_elementowego zbioru. 
#define NUMBER_OF_COMMANDS 5
#define ADDUSER 0
#define DELUSER 1
#define ADDMOVIE 2
#define DELMOVIE 3
#define MARATHON 4
#define WRONG_COMMAND -1
// Przypisanie liczb komendom jest potrzebne w funkcji 
// "which_command_is_it" aby sprawnie odnosic sie do 
// danych zapisanych w tablicy "how_many_common_characters".
#define MIN_USER_ID 0
#define MAX_MOVIE_RATING 2147483647
#define MIN_MOVIE_RATING 0
#define MAX_NUMBER_OF_DIGITS 10

typedef struct {
    char *array;
    int length;
} Array;

char space = ' ';

char end_of_line = '\n';

char hashtag = '#';

// Funkcja czyta jeden wiersz wejścia i zapisuje go w tablicy 
// "input_array. Funkcja zwraca również informacje o wystąpieniu
// EOF lub znaków "#" i "\n" poprzez argument.
Array *read_line_to_input_array(bool *is_EOF, bool *ignore_line) {
    Array *input_array = (Array*)malloc(sizeof(Array));
    if (input_array == NULL)
        exit(1);
    input_array->array = (char*)malloc(sizeof(char));
    if (input_array->array == NULL)
        exit(1);
    int counter = 0;
    char c;
    
    while ((c = getchar()) != end_of_line && c != EOF) {
        if (counter == 0 && c == hashtag)
            (*ignore_line) = true;
        
        if (counter <= MAX_LENGTH_OF_ARRAY) {
            char *error_case_variable =
            (char*)realloc(input_array->array, sizeof(char) * (counter + 1));
            if (error_case_variable == NULL) {
                free(error_case_variable);
                exit(1);
            } else {
                input_array->array = error_case_variable; 
            }
            (input_array->array)[counter] = c;
        }
        
        counter++;
    }
    
    if (c == EOF && counter > 0) {
        printf("ERROR\n");
        (*is_EOF) = true;
        (*ignore_line) = true;
    }
    
    if (counter <= MAX_LENGTH_OF_ARRAY) {
    input_array->length = counter;
    
    if (c == EOF) {
        (*is_EOF) = true;
        (*ignore_line) = true;
    }
    
    if (c == '\n' && counter == 0)
        (*ignore_line) = true;
    } else {
        if ((*ignore_line) == false) 
            printf("ERROR\n");
        (*ignore_line) = true;
    }
    
    return input_array;
}

void free_allocated_Array(Array *A) {
    free(A->array);
    free(A);
}

// Funkcja sprawdza czy "początkowe" znaki znaki w tablicy wejścia
// tworzą którąś z komend.
int which_command_is_it(Array *A) {
    int how_many_common_characters[NUMBER_OF_COMMANDS] = {0};
    int i;

    for (i = 0; i < LENGTH_OF_COMMAND_ADDUSER; i++) {
        if (i < A->length) {
            if ((A->array)[i] == COMMAND_ADDUSER[i])
                how_many_common_characters[ADDUSER]++;
            if ((A->array)[i] == COMMAND_DELUSER[i]) 
                how_many_common_characters[DELUSER]++;
            if ((A->array)[i] == COMMAND_ADDMOVIE[i])
                how_many_common_characters[ADDMOVIE]++;
            if ((A->array)[i] == COMMAND_DELMOVIE[i])
                how_many_common_characters[DELMOVIE]++;
            if ((A->array)[i] == COMMAND_MARATHON[i])
                how_many_common_characters[MARATHON]++;
        }
    }
    
    if (i < A->length) {
        if ((A->array)[i] == COMMAND_ADDMOVIE[i])
            how_many_common_characters[ADDMOVIE]++;
        if ((A->array)[i] == COMMAND_DELMOVIE[i])
            how_many_common_characters[DELMOVIE]++;
        if ((A->array)[i] == COMMAND_MARATHON[i])
            how_many_common_characters[MARATHON]++;
    }
    
    for (i = 0; i < NUMBER_OF_COMMANDS; i++) {
        if (how_many_common_characters[i] == LENGTH_OF_COMMAND_ADDUSER && i <= DELUSER) {
            return i;
        } else if (how_many_common_characters[i] == LENGTH_OF_COMMAND_ADDMOVIE && i > DELUSER) {
            return i;
        }
    }
            return WRONG_COMMAND;
}

// Funkcja zamienia ciąg cyfr na liczbę. Aktualizowana jest również 
// zmienna "current_character".
int string_to_integer_converter(Array *A, int *current_character) {
    // Zmienna base jest podstawą systemu dziesiętnego.
    int base = 10;
    int number = 0;
    while ((*current_character) < A->length && isdigit((A->array)[*current_character])) {
        number *= base;
        number += (A->array)[*current_character] - '0';
        (*current_character)++;
    }
    
    return number;
}

// Funkcja wywołuje odpowiednią komende w zależności od wartości
// argumentu "which_command".
void function_activator(int which_command, int first_number, int second_number) {
    
    switch(which_command) {

    case ADDUSER  :
        if (second_number >= MIN_USER_ID && second_number <= MAX_USER_ID)
            addUser(first_number, second_number);
        else 
            printf("ERROR\n");
        break;
            
    case DELUSER  :
        delUser(first_number);
        break;
    
    case ADDMOVIE  :
        if (second_number >= MIN_MOVIE_RATING && second_number <= MAX_MOVIE_RATING)
            addMovie(first_number, second_number);
        else 
            printf("ERROR\n");
        break;
    
    case DELMOVIE  :
        if (second_number >= MIN_MOVIE_RATING && second_number <= MAX_MOVIE_RATING)
            delMovie(first_number, second_number);
        else 
            printf("ERROR\n");
        break;
    
    case MARATHON  :
        if (second_number >= MIN_MOVIE_RATING && second_number <= MAX_MOVIE_RATING)
            marathon(first_number, second_number);
        else 
            printf("ERROR\n");
        break;
        
    }
}

// Funkcja sprawdza dalszą poprawnośc wiersza po wstępnym
// przetworzeniu wiersza wejścia przez funkcję "which_command_is_it".
void is_line_correct(Array *A, int which_command) {
    int current_character;
    if (WRONG_COMMAND != which_command) {
        if (which_command <= DELUSER)
            current_character = LENGTH_OF_COMMAND_ADDUSER;
        if (which_command >= ADDMOVIE) 
            current_character = LENGTH_OF_COMMAND_ADDMOVIE;
        
        if (current_character < A->length && (A->array)[current_character] == space) {
            current_character++;
            int first_number = string_to_integer_converter(A, &current_character);
            if (first_number < MIN_USER_ID || first_number > MAX_USER_ID) {
                printf("ERROR\n");
            } else {
                if (which_command == DELUSER && A->length == current_character) {
                    function_activator(which_command, first_number, first_number);
                } else if (current_character < A->length && which_command != DELUSER &&
                    (A->array)[current_character] == space) {
                    current_character++;
                    int second_number = string_to_integer_converter(A, &current_character);
                    if (A->length == current_character) {
                        function_activator(which_command, first_number, second_number);
                    } else {
                        printf("ERROR\n");
                    }
                } else {
                    printf("ERROR\n");
                }
            }
        } else {
            printf("ERROR\n");
        }
    } else {
        printf("ERROR\n");
    }
}
    
// Funkcja uruchamia pętle w której bedzie wykonywany program
// aż do napotlania znaku "EOF".
void run_program() {
    bool is_EOF = false;
    bool ignore_line;
    
    while (!is_EOF) {
        ignore_line = false;

        Array *in_array = read_line_to_input_array(&is_EOF, &ignore_line);
        if (!ignore_line) {
            int command_number = which_command_is_it(in_array);
            is_line_correct(in_array, command_number);
        }

        free_allocated_Array(in_array);
    }
}

int main() {
    initialize_tree();
    run_program();
    free_tree_of_users(array_of_user_id[ROOT_USER_ID]);
    free(this_field_is_empty);
    return 0;
}

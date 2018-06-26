/**
 * Function to check whether it is a valid wildcard
 *
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 22 May 2018

*/

#include "headers.h"

int compare_wildcards(char *first, char *second){

    //Sizes of each strings.
    int first_size = 0;
    int second_size = 0;

    //Checks whether its a valid wildcard.
    int valid_wildcard = 0;

    //Array to store the items
    char *first_check_items[256];
    char *second_check_items[256];

    //Splits up the string "."
    char *first_check = strtok(first,".");

    if(strncmp(first_check,"*",1)== 0){
        valid_wildcard = 1;
    }

    //If it does not start with a "*", its not a wild card. Return
    if(!valid_wildcard){
        printf("Invalid wildcard\n");
        return 0;
    }

    //Stores each part into an array for first and second string.
    while(first_check != NULL){
        first_check_items[first_size++] = first_check;
        first_check = strtok(NULL,".");
    }

    char *second_check = strtok(second,".");

    while(second_check != NULL){
        second_check_items[second_size++] = second_check;
        second_check = strtok(NULL,".");
    }

    //If there are different sizes, its invalid.
    if(first_size != second_size){
        printf("Invalid, different sizes\n");
        return 0;
    }

    //If it is valid. check whether each part of the strings match.
    for(int i = 1; i < first_size; i++){

        if(strncasecmp(first_check_items[i],second_check_items[i],256) != 0){
            printf("Invalid, strings dont match\n");
            return 0;
        }
    }

    //Passes all tests, its a valid string.
    return 1;
}

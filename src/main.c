#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "street.h"

// size of line buffer when reading file
#define LINE_BUF_SIZE 2048

// linked list data structure to store street list
struct street_list_struct {
  StreetData data;
  struct street_list_struct *next;
};
typedef struct street_list_struct StreetList;


int read_streets(FILE *fp, StreetList **list);
void print_streets(StreetList *list);
int translate(StreetList *list, char *town, char *street);
void free_list(StreetList *list);


/**
 * @brief Main function, takes file as argument or reads from stdin
 * @param argc number of command line arguments
 * @param argv command line arguments, 1st argument can be csv input file
 * @return 0 if searched address was found, 1 otherwise
 **/
int main(int argc, char const *argv[])
{
    // set file pointer to input file
    FILE *fp = stdin;
    // if an argument is given, use it as input file
    if (argc > 1) {
        printf("%s\n", argv[1]);
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }

    // read csv file and store entries in linked list
    StreetList *list;
    int result = read_streets(fp, &list);

    // close file after reading
    if (argc > 1)
      fclose(fp);

    // if file has not been read correctly, exit
    if (result)
      exit(1);

    // print all streets in list
    //print_streets(list);

    // ask the user for the town to search
    printf("Enter the Italian town name:\n");
    char searched_town[50];
    scanf("%49[^\n]", searched_town);
    
    // consume newline character before getting next input
    char temp;
    scanf("%c", &temp);
    
    // ask the user for the street name to search for
    printf("Enter the Italian street name:\n");
    char searched_street[50];
    scanf("%49[^\n]", searched_street);

    // search in list for translation
    int not_found = translate(list, searched_town, searched_street);

    // free StreetList
    free_list(list);

    // return 0 if searched street was found
    exit(not_found);
}


/**
 * @brief This function takes a file pointer to a csv file of streets and sets
 *        *list to the head of a linked list containing all streets
 * @param fp file pointer
 * @param list that is filled
 * @return 0 if reading succeeded and 1 otherwise
 **/
int read_streets(FILE *fp, StreetList **list) {
    // buffer to hold line
    static char line_buf[LINE_BUF_SIZE];
    char *line = NULL;
    size_t len = 0;

    // skip first line (headers)
    if (getline(&line, &len, fp) == -1) {
        free(line);
        return EXIT_FAILURE;
    }

    StreetData street;
    // head will point to the first element of the list
    StreetList *head = NULL;
    // prev is used to remember the last element inserted into the list
    StreetList *prev = NULL;
    while (getline(&line, &len, fp) != -1) {
        // copy line into line buffer
        strncpy(line_buf, line, sizeof(line_buf));
        // remove trailing newline
        line_buf[sizeof(line_buf) - 1] = 0;
        // parse line as csv
        // note that the function was modified to trim all entries of the csv,
        // i.e., to cutoff leading and trailing spaces
        if (csv_row_to_street(line_buf, &street)) {
            // could print parsed street data record
            //show_street(&street);

            // allocate memory for next list element
            StreetList *current = malloc(sizeof(StreetList));
            //copy data into next list element 
            current->data = street;
            // if head is NULL, the current element is the first, so set head.
            // otherwise, set current element as next of previous one 
            if (head == NULL) {
                head = current;
            } else {
                prev->next = current;
            }
            prev = current;
        } else {
            fprintf(stderr, "Cannot parse: %s\n", line);
        }
    }

    free(line);
    // set head of list to the dedicated parameter to "return" it
    *list = head;

    return EXIT_SUCCESS;
}

/**
 * @brief This function takes a linked list of streets, and prints it
 * @param list StreetList to print
 **/
void print_streets(StreetList *list){
    StreetList *current = list;
    // walk the list and print all elements
    while(current){
        show_street(&(current->data));
        current = current->next;
    }
}

/**
 * @brief This function takes a linked list of streets, and the Italian name of
 *        a town and street that the user wants to translate
 * @param list the head of the StreetList
 * @param town Italian name of town that user wants to find 
 * @param street Italian name of street that user wants to find
 * @return 0 if names are found, 1 otherwise
 **/
int translate(StreetList *list, char *town, char *street) {
    StreetList *current = list;
    // walk through the list until last element reached; if the element was 
    // found, the loop will be exited directly
    while(current){
        StreetData data = current->data;
        // check whether both twon and street match
        if (strcmp(data.municipality_it, town) == 0 && 
          strcmp(data.name_it, street) == 0) {
          printf("The German name is %s, %s\n", data.municipality_de, data.name_de);
          return 0;
        }
        current = current->next;
    }
    // if this point is reached, the sought element was not found
    printf("No town and street with these names (%s, %s) were found.\n",
      town, street);
    return 1;
}

/**
 * @brief This function frees the memory of a StreetList.
 * @param list the head of the StreetList
 **/
void free_list(StreetList *list){
    StreetList *current = list;
    while(current){
        StreetList *next = current->next;
        free(current);
        current = next;
    }
}

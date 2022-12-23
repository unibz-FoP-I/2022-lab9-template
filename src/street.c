#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "street.h"

#define MIN(x,y) (x < y ? x : y)

static char *get_next_token(char* current, char sep) {
    // find position of next separator in string
    char *next = strchr(current, sep);
    if (next) {
        // replace it by string terminal character
        next[0] = 0;
        // return position where next token starts
        return next + 1;
    }
    return 0;
}

/**
 * @brief This function takes a pointer to a string and modifies it to remove
 *        spaces in the front and in the back.
 * @param str pointer to string, modified by this function
 **/
void trim(char **str){
    // trim left: while space found, advance pointer
    while (str != NULL && *str != NULL && (*str)[0] == ' ') {
      *str = (*str)+1;
    }
    // trim right: replace spaces by terminating 0 character
    size_t i = strlen(*str) - 1;
    while (i>0 && ((*str)[i] == ' ')){
      (*str)[i] = 0;
      i--;
    }
}

/**
 * @brief This function parses a csv line into a StreetData record.
 * @param line to be parsed
 * @param street StreetDataRecord to be filled
 **/
int csv_row_to_street(char *line, StreetData *street) {
    if (street) {
        // clear memory of StreetData record
        memset(street, 0, sizeof(StreetData));
        char *token = line;
        // find next separator, replace it by 0 and return its position
        char *next_token = get_next_token(line, CSV_SEP);

        // set German municipality name
        if (!token) return 0;
        // remove spaces from token and copy it to street data record.
        // copy at most STR_SIZE-1 characters to keep terminating 0
        // (the 0 is then there because of the memset above)
        trim(&token);
        strncpy(street->municipality_de, token, MIN(strlen(token), STR_SIZE-1));
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set Italian municipality name
        if (!token) return 0;
        trim(&token);
        strncpy(street->municipality_it, token, MIN(strlen(token), STR_SIZE-1));
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set street code
        if (!token) return 0;
        // convert next token to integer
        char *endptr;
        street->code = strtod(token, &endptr);
        // if conversion failed, endptr is set to token: return 0
        if (endptr == token) return 0;
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set German street name
        if (!token) return 0;
        trim(&token);
        strncpy(street->name_de, token, MIN(strlen(token), STR_SIZE-1));
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set Italian street name
        if (!token) return 0;
        trim(&token);
        strncpy(street->name_it, token, MIN(strlen(token), STR_SIZE-1));
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);
    }
    return 1;
}

void show_street(StreetData *street) {
    printf("IT: %20s: %s\n", street->municipality_it, street->name_it);
    printf("DE: %20s: %s\n", street->municipality_de, street->name_de);
    printf("code: %d\n", street->code);
}


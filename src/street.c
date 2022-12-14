#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "street.h"

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

int csv_row_to_street(char *line, StreetData *street) {
    if (street) {
        // clear StreetData record
        memset(street, 0, sizeof(StreetData));
        char *token = line;
        // find next separator, replace it by 0 and returns its position
        char *next_token = get_next_token(line, CSV_SEP);

        // set German municipality name
        if (!token) return 0;
        // copy (at most STR_SIZE-1) characters from token to street data record
        // (-1 to leave trailing 0)
        strncpy(street->municipality_de, token, STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set Italian municipality name
        if (!token) return 0;
        strncpy(street->municipality_it, token, STR_SIZE - 1);
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
        strncpy(street->name_de, token, STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set Italian street name
        if (!token) return 0;
        strncpy(street->name_it, token, STR_SIZE - 1);
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

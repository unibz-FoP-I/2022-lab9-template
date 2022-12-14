#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "street.h"

static char *get_next_token(char* current, char sep) {
    char *next = strchr(current, sep);
    if (next) {
        next[0] = 0;
        return next + 1;
    }
    return 0;
}

int csv_row_to_street(char *line, StreetData *street) {
    if (street)
    {
        memset(street, 0, sizeof(StreetData));
        char *token = line;
        char *next_token = get_next_token(line, CSV_SEP);

        // set German municipality name
        if (!token) return 0;
        strncpy(street->gemeinde, token, STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set Italian municipality name
        if (!token) return 0;
        strncpy(street->comune, token, STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set street code
        if (!token) return 0;
        if (!(street->code = strtod(token, NULL))) return 0;
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set German street name
        if (!token) return 0;
        strncpy(street->strasse, token, STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);

        // set Italian street name
        if (!token) return 0;
        strncpy(street->via, token, STR_SIZE - 1);
        token = next_token;
        next_token = get_next_token(token, CSV_SEP);
    }

    return 1;
}

void show_street(StreetData *street) {
    printf("IT: %20s: %s\n", street->comune, street->via);
    printf("DE: %20s: %s\n", street->gemeinde, street->strasse);
    // optionally, also the code could be shown
}

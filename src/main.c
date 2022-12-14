#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "street.h"

#define LINE_BUF_SIZE 2048

int read_streets(FILE *fp);

int main(int argc, char const *argv[])
{
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

    // read data from file
    int result = read_streets(fp);

    if (argc > 1)
        fclose(fp);

    exit(result);
}

int read_streets(FILE *fp) {
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
    while (getline(&line, &len, fp) != -1) {
        // copy line into line buffer
        strncpy(line_buf, line, sizeof(line_buf));
        // remove trailing newline
        line_buf[sizeof(line_buf) - 1] = 0;
        // parse line as csv
        if (csv_row_to_street(line_buf, &street)) {
            puts("------------------------------");
            // print parsed street data record
            show_street(&street);

            // TODO: insert the data in street into a list
        
        } else {
            fprintf(stderr, "Cannot parse: %s\n", line);
        }
    }

    free(line);
    return EXIT_SUCCESS;
}
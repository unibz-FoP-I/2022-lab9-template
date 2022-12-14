// set include guard to avoid repeated definitions
#ifndef name_H
#define name_H 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// maximal length of strings
#define STR_SIZE 100
// separator in csv format
#define CSV_SEP ';'

// represent street data record as taken from
// http://daten.buergernetz.bz.it/dataset/streetnames-from-addresspoints
typedef struct
{
    char municipality_it[STR_SIZE];  // municipality name in Italian
    char municipality_de[STR_SIZE];  // municipality name in German
    int code;                        // code of street (unique in municipality)
    char name_it[STR_SIZE];          // street name in Italian
    char name_de[STR_SIZE];          // street name in German
} StreetData;


// function prototypes

// parse a StreetData record from a csv string representatiuon
int csv_row_to_street(char *line, StreetData *street);
// output the street data
void show_street(StreetData *street);

#endif

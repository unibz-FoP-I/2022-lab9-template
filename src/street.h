#ifndef STREET_H
#define STREET_H 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define STR_SIZE 100
#define CSV_SEP ';'

// represent street data record as taken from
// http://daten.buergernetz.bz.it/dataset/streetnames-from-addresspoints
typedef struct
{
    char comune[STR_SIZE];    // municipality name in Italian
    char gemeinde[STR_SIZE];  // municipality name in German
    int code;                 // code of street (unique in municipality)
    char via[STR_SIZE];       // street name in Italian
    char strasse[STR_SIZE];   // street name in German
} StreetData;


// Function prototypes

// parse a StreetData record from a csv string representatiuon
int csv_row_to_street(char *line, StreetData *street);
// output the street data
void show_street(StreetData *street);

#endif
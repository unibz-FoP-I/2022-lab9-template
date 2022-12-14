# 2022-Lab9: Bilingual Street Directory

The file `data/streets.csv` contains all street names in municipalities in South Tyrol, in Italian and German, in `csv` format (the data is taken from [this official site](http://daten.buergernetz.bz.it/dataset/streetnames-from-addresspoints)).
The given program in the `src` directory reads such a file and prints all entries.
It can be compiled and executed as follows:  
`$ make`  
`$ ./main data/streets.csv`  

The aim is to implement a bilingual street directory, where the user enters an Italian or German name of a municipality and a street, and the program outputs its translation.

At the moment, the program simply reads every line, stores it temporarily as a `StreetData` record (defined in `street.h`), prints it, and moves on to the next line. Thus, in order to implement a directory, the following is needed:  

1. **Store the data:** Define a datatype for a linked list with street data records, and store all street data records in such a list.  
  
2. **Search the data:** Let the user input a municipality and street name in one language, and search in the list for its translation. (You can fix one direction of translation, Italian to German or the other way around.)

3. *Bonus exercise*: The search for the right street data record would be more efficient if one would maintain a list of municipalities, and for each municipality a list of its streets. For the translation, one could then first search the right municipality, and afterwards the streets in this municipality, rather than always searching through all streets in all towns.  
Define a data structure that maintains the data in this format, and use it to store the data and search the list.  

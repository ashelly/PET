// PET adaptor for the Paul Senzee's 7 hand evaluator
// http://www.paulsenzee.com/2006/06/some-perfect-hash.html
//
// table builder: (c) James Devlin 
// http://www.codingthewheel.com/archives/poker-hand-evaluator-roundup
// 
// adaptor (c) 2015 Adam Shelly (github.com/ashelly)


#include <stdlib.h>
#define SNZ_NOTABLES
#include "SNZ_eval.h"

#define LOOKUP_TABLE_SIZE 133784560

EquivClass* snzTable;

EquivClass* load_table(const char* fname){
  printf("Allocating memory for 133,784,560 entries...\n");
  EquivClass* snzTable = malloc(sizeof(EquivClass)*LOOKUP_TABLE_SIZE);
  if (snzTable){
	 // Load the DAT file and map it into the HR array
	 printf("Attempting to load %s lookup table...\n", fname);
	 FILE * fin = fopen(fname, "rb");
	 if (fin)	 {
		size_t bytesread = fread(snzTable, sizeof(EquivClass), LOOKUP_TABLE_SIZE, fin);
		fclose(fin);
		printf("Successfully loaded %ld byes!\n", bytesread);
	 }
	 else {
		printf("Could not load table\n");
		free(snzTable);
		snzTable = NULL;
	 }
  }
  return snzTable;
}

/*******************************************************************/ 
/*  
 *  Eva Dokladalova, 2019
 */

#ifndef FUNCTIONS_H_ 
#define FUNCTIONS_H_

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

// types definitions
typedef unsigned char uint8;

// buffer size for input image reading
#define BSIZE 1000

// function declarations
float * readimg(char *, int *, int *, int *);
void writeimg(char *, float *, int , int, int);

#endif


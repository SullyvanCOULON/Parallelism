/*******************************************************************/ 
/*  HPC(3) : TP parallélisation 
 *  
 *  Eva Dokladalova, 2020
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "functions.h"

//-----------------------------------------------------------
// MAIN FUNCTION
//-----------------------------------------------------------
int main (int argc, char *argv[])
{
 
  // noms des fichiers d'entrée et de sortie
  char *filename=argv[1];
  char *file_out=argv[2];

  // exemples des pointeurs vers les matrices représentant les images
  float *T;
  float *Grad;

  // dimension de matrice, valeur maximale
  int v;  // max  value in matrix
  int rw; // row size
  int cl; // column size

  // vérification des arguments d'entrée
  if (argc != 3)
    {  fprintf(stderr,"Input parameters missing:\n./program_name <inpout.pgm> <output.pgm>\n");
      return(0);
    }

  
  //-------------------------------------------------------------
  // OPEN DATA FILE AND ALLOCATE INPUT IMAGE MEMORY (float precision)
  //-------------------------------------------------------------
  T = readimg(filename, &rw, &cl, &v);
  Grad = (float *) calloc (rw*cl,sizeof(float));
 
  //-------------------------------------------------------------
  // PUT HERE THE SOLUTION OF YOUR OPERATORS
  // complete variables necessary for the computing
  //-------------------------------------------------------------
  
  
  // A COMPLETER :-)
  // exemple d'un traitement de base  
  for (int j = 1; j < cl-1; j++)
	for (int i = 1; i< rw-1; i++)
	{
	     int n = T[i + (j-1)*rw];
	     int s = T[i + (j+1)*rw];

	     Grad[i + j*rw] = abs(n-s);

	}

     
    
  //-------------------------------------------------------------
  // WRITE RESULT IN A PGN IMAGE 
  //-------------------------------------------------------------
   writeimg(file_out, Grad, rw, cl, v);
   free(Grad);
   free(T);
   return(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "../image_lecture/functions.h"

// #define SIDE 500 - old version
// #define filename "images/papoch.pgm" - old version
// #define file_out "images/image_out_seq.pgm" - old version

typedef enum {
    DIM_1D = 1,
    DIM_2D = 2
} Dimension;

/**
 * @brief Convolution function for heat equation in 1D or 2D and print the result
 * @param dimension: 1D or 2D
 * @return time of execution
 */
int convolution(Dimension dimension, char *filename, char *file_out) {
    // matrix allocation - old version
    // float * mat = (float *) calloc (SIDE*SIDE,sizeof(float));
    // float * mat_dt = (float *) calloc (SIDE*SIDE,sizeof(float));

    // exemples des pointeurs vers les matrices représentant les images
    float *T;
    float *mat;

    // dimension de matrice, valeur maximale
    int v;  // max  value in matrix
    int rw; // row size
    int cl; // column size

    T = readimg(filename, &rw, &cl, &v);
    if (T == 0) {
        printf("Error: Image reading failed\n");
        return (EXIT_FAILURE);
    }
    mat = (float *) calloc (rw*cl,sizeof(float));

    float nn,sn,en,wn, cp;
    float d2x, d2y = 0.0f;
    float h = 1;
    float dt = 0.0001;
    float t = 1;
    float F;

    // Heating point
    T[rw/2 + cl/2*rw] = 255;

    int N = (int) (t/dt); // here we compute the number of iterations

    // Convolution
    double start_time = omp_get_wtime();
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < cl; i++) { 
            for (int j = 0; j < rw; j++) {

                // Neighborhoods
                nn = (i == 0)      ? T[j + i * rw] : T[j + (i - 1) * rw]; // Nord
                sn = (i == (rw-1)) ? T[j + i * rw] : T[j + (i + 1) * rw]; // Sud
                wn = (j == 0)      ? T[j + i * rw] : T[(j - 1) + i * rw]; // Ouest
                en = (j == (cl-1)) ? T[j + i * rw] : T[(j + 1) + i * rw]; // Est

                cp = T[j + i * rw];  // Correction ici aussi
            
                // Partial derivatives second order
                d2x = (en - 2 * cp + wn) / (h * h); 
                if (dimension == DIM_2D) {
                    d2y = (nn - 2 * cp + sn) / (h * h);
                }

                // Heat equation
                F = (dimension == DIM_1D) ? d2x : d2x + d2y;

                mat[j + i * rw] = T[j + i * rw] + dt * F; // Correction ici aussi
            }
        }
        memcpy(T, mat, sizeof(float) * rw * cl); // Correction ici aussi
    }
    double end_time = omp_get_wtime();

    // DEBUG
    // Print test for some values - only for small images
    /**for (int i = 0; i < SIDE ; i++) { 
        for (int j = 0; j < SIDE ; j++)
        printf("%.2f ", mat[j + i*SIDE]);
        printf("\n"); 
    }*/

    writeimg(file_out, mat, rw, cl, v);
    free(mat);
    free(T);

    printf("One sequential execution finished.\tExecution time: %f\n", (end_time - start_time)); 
    return (end_time - start_time);
}

int main(int argc, char* argv[]) {
    char *arg_4 = malloc(10);
    Dimension dim;
    double exec_time;
    double moy_time = 0;

    // If image not specified
    if (argc < 3) {
        printf("Error: Missing arguments.\nUse: %s <image> <output> [dimension]\n", argv[0]);
        printf("Example: %s images/papoch.pgm images/image_out_seq.pgm 1D\n", argv[0]);
        return (EXIT_FAILURE);
    } // If not specified, ask for dimension
    else if (argc != 4) {
        printf("Dimension: (1D or 2D)\n");
        scanf("%s", arg_4);
    } else strcpy(arg_4,argv[3]);

    // Dimension format verification
    if (strcmp(arg_4, "1D") == 0) {
        dim = DIM_1D;
    } else if (strcmp(arg_4, "2D") == 0) {
        dim = DIM_2D;
    } else {
        printf("Error: Dimension not recognized, please select between '1D' or '2D'\n");
        return (EXIT_FAILURE);
    }
    free(arg_4);

    
    // Convolution according to dimension
    for (int i = 0; i < 10; i++) {
        exec_time = convolution(dim, argv[1], argv[2]);
        moy_time += exec_time;
    }
    moy_time /= 10;
    printf("Average execution time: %f\n", moy_time);
    
    return (EXIT_SUCCESS);
}

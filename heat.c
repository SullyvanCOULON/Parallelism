#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIDE 10

typedef enum {
    DIM_1D = 1,
    DIM_2D = 2
} Dimension;

// This program relizes the computation of linear diffusion by heating equation
// we compute the diffusion from one heating point, could be replaced by a natural image.

int convolution(Dimension dimension) {
    // matrix allocation
    float * mat = (float *) calloc (SIDE*SIDE,sizeof(float));
    float * mat_dt = (float *) calloc (SIDE*SIDE,sizeof(float));
    float nn,sn,en,wn, cp;
    float d2x, d2y;
    float h = 1;
    float dt = 0.0001;
    float t = 1;
    float F;

    // Heating point
    mat[SIDE/2 + SIDE/2*SIDE] = 255;

    int N = (int) (t/dt); // here we compute the number of iterations
    for (int k = 0; k<N; k++) {
        for (int i = 0; i < SIDE ; i++) { 
	        for (int j = 0; j < SIDE ; j++) {

            // Neightborhoods
            nn = (i == 0)        ? mat[j + i*SIDE] : mat[j + (i-1)*SIDE];
            sn = (i == (SIDE-1)) ? mat[j + i*SIDE] : mat[j + (i+1)*SIDE];
            wn = (j == 0)        ? mat[j + i*SIDE] : mat[(j-1) + i*SIDE];
            en = (j == (SIDE-1)) ? mat[j + i*SIDE] : mat[(j+1) + i*SIDE];
            
            cp = mat [j + i*SIDE];
        
            // Partial derivatives second order
            d2x = (en - 2*cp + wn)/(h*h); 
            if (dimension == DIM_2D) {
                d2y = (nn - 2*cp + sn)/(h*h);
            }

            // Heat equation
            F = (dimension == DIM_1D) ? d2x : d2x + d2y;

            mat_dt[j + i*SIDE] = mat [j + i*SIDE] + dt*F;
            }
	    }
    memcpy (mat, mat_dt, sizeof(float)*SIDE*SIDE);
    }

    // Print test for some values - only for small images
    for (int i = 0; i < SIDE ; i++) { 
        for (int j = 0; j < SIDE ; j++)
        printf("%.2f ", mat[j + i*SIDE]);
        printf("\n"); 
    }
    
    return (0);
}

int main(int argc, char* argv[]) {
    char *arg_2 = malloc(10);
    Dimension dim;

    // If not specified, ask for dimension
    if (argc == 1) {
        printf("Dimension: (1D or 2D)\n");
        scanf("%s", arg_2);
    } else strcpy(arg_2,argv[1]);

    // Dimension format verification
    if (strcmp(arg_2, "1D") == 0) {
        dim = DIM_1D;
    } else if (strcmp(arg_2, "2D") == 0) {
        dim = DIM_2D;
    } else {
        printf("Error: Dimension not recognized, please select between '1D' or '2D'\n");
        return (EXIT_FAILURE);
    }
    free(arg_2);

    // Convolution according to dimension
    convolution(dim);
    return (EXIT_SUCCESS);
}

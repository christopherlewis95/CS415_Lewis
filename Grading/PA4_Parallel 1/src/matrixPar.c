#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include "matrix.h"

double *Matrix2to1(matrix_struct *m) {
    double *matrix = malloc( (m->rows * m->cols) * sizeof(double) );
    for (int i = 0; i < m->rows; i++) {
        memcpy( matrix + (i * m->cols), m->matrixData[i], m->cols * sizeof(double) );
    }
    return matrix;
}

int main(int argc, char *argv[]) {
    int matrix_properties[4];
    int startTime, endTime = 0;
    double duration = 0;
    double *workerMatA = NULL;
    double *workerMatB = NULL;
    double *masterMatrix = NULL;
    int sizeA, sizeB, sizeR, startRow, endRow, number_of_rows;

    int nunWorkers, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nunWorkers);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) 
    {
        //gets matrices from commandline
        matrix_struct *fileMatA = get_matrix_struct(argv[1]);
        matrix_struct *fileMatB = get_matrix_struct(argv[2]);

        matrix_properties[0] = fileMatA->rows;
        matrix_properties[1] = fileMatA->cols;

        matrix_properties[2] = fileMatB->rows;
        matrix_properties[3] = fileMatB->cols;
        
        workerMatA = Matrix2to1(fileMatA);
        workerMatB = Matrix2to1(fileMatB);
    }
    //startTime = MPI_Wtime();
    //sends number of rows/col to workers
    MPI_Bcast(&matrix_properties, 4, MPI_INT, 0, MPI_COMM_WORLD);

    //calc the eize of one dim arrays
    sizeA   = matrix_properties[0] * matrix_properties[1];
    sizeB   = matrix_properties[2] * matrix_properties[3];
    sizeR = matrix_properties[0] * matrix_properties[3];

    //master defines result matrix while workers do the 2 matrices
    if(rank == 0) 
    {
        masterMatrix = malloc( sizeR * sizeof(double) );
    } 
    else 
    {
        workerMatA = malloc( sizeA * sizeof(double) );
        workerMatB = malloc( sizeB * sizeof(double) );
    }
    startTime = MPI_Wtime();

    // send 1D matrices to workers
    MPI_Bcast(workerMatA, sizeA , MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(workerMatB, sizeB , MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    // calculate the data range for the workers
    startRow = rank * ( matrix_properties[0] / nunWorkers);
    endRow = ((rank + 1) * ( matrix_properties[0] / nunWorkers)) -1;
    
    
    number_of_rows = sizeR / nunWorkers;
    double *result_matrix = calloc(number_of_rows, sizeof(double));

    int position = 0;

    for (int i = startRow; i <= endRow; i++) 
    {
        for (int j = 0; j < matrix_properties[3]; j++) 
        {
            for (int k = 0; k < matrix_properties[2]; k++) 
            {
                //matrix multiplication
                result_matrix[position] += workerMatA[(i * matrix_properties[1] + k)] * workerMatB[(k * matrix_properties[3] + j)];
            }
            position++;
        }
    }
    endTime = MPI_Wtime();
    MPI_Gather(result_matrix, number_of_rows, MPI_DOUBLE, masterMatrix, number_of_rows,  MPI_DOUBLE, 0, MPI_COMM_WORLD);
    //gather collects worker data to put in result matrix
    //endTime = MPI_Wtime();
    duration = endTime - startTime;
    printf("%lf\n", duration);//calculates the time it took to run eahc process

   //printf("%s\n","TEST");
    MPI_Finalize();
    exit(EXIT_SUCCESS);
}

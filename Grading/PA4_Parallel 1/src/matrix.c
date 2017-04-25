#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include "matrix.h"

matrix_struct *get_matrix_struct(char matrix[]) 
{
    int x,y,i;
    char ch = 0;

    matrix_struct *m = malloc(sizeof(matrix_struct));
    m->rows = 0;
    m->cols = 0;
    FILE* myfile = fopen(matrix, "r");
    
    //assumed the matrix is square
    do {
        ch = fgetc(myfile);
        //gen creates 2 dim array with elements seperated by tabs
        if(m->rows == 0 && ch == '\t')
            m->cols++;
        if(ch == '\n')//new line of numbers
            m->rows++;
    } while (ch != EOF);//counts number of rows and columns until end of file
//	printf("%d",m->rows);
//printf("%d",m->cols);
    m->matrixData = calloc(m->rows, sizeof(double*)); 
    
    for(i=0; i < m->rows; ++i)
        m->matrixData[i]=calloc(m->cols, sizeof(double));
    rewind(myfile);
    
    for(x = 0; x < m->rows; x++) 
    {
        for(y = 0; y < m->cols; y++) 
        {
            if (!fscanf(myfile, "%lf", &m->matrixData[x][y])) 
                break;
        }
    }
    fclose(myfile);

    return m;
}

void print_matrix(matrix_struct *matrix_to_print)
{
    int i,j;
    for(i = 0; i < matrix_to_print->rows; i++) 
    {
        for(j = 0; j < matrix_to_print->cols; j++) 
        {
            printf("%lf\t",matrix_to_print->matrixData[i][j]);
        }
        printf("\n");
    }
}//outputs te matrix, pretty much just used for debugging with 10x10


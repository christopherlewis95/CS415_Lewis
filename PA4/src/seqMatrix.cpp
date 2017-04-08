#include <math.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;

void genNumbers( int **arrayA, int **arrayB, int size );

 

int main(int argc, char** argv)
    {
        int sizeN = atoi(argv[1]);
        int **arrayA = new int *[sizeN];
        int **arrayB = new int *[sizeN];
        int **arrayC = new int *[sizeN];  

        for(int i = 0; i < sizeN; i++)
        {
        arrayA[i] = new int[sizeN];  
        arrayB[i] = new int[sizeN];  
        arrayC[i] = new int[sizeN];      
        }

    genNumbers( arrayA, arrayB, sizeN );

    int x, y, i, j, m, n;

    // x denotes number rows in matrix A
    // y denotes number columns in matrix A
    cout << "\n\nMatrix A :\n\n";
    for (i = 0; i < sizeN; i++)
    {
        for (j = 0; j < sizeN; j++)
        {
            cout << "\t" << arrayA[i][j];
        }
        cout << "\n\n";
    }
    cout << "\n-----------------------------------------------------------\n";
    // m denotes number rows in matrix B
    // n denotes number columns in matrix B
 
    cout << "\n\nMatrix B :\n\n";
    for (i = 0; i < sizeN; i++)
    {
        for (j = 0; j < sizeN; j++)
        {
            cout << "\t" << arrayB[i][j];
        }
        cout << "\n\n";
    }


        for (i = 0; i < sizeN; i++)
        {
            for (j = 0; j < sizeN; j++)
            {
                arrayC[i][j] = 0;
                for (int k = 0; k < sizeN; k++)
                {
                    arrayC[i][j] = arrayC[i][j] + arrayA[i][k] * arrayB[k][j];
                }
            }
        }
        cout
                << "\n-----------------------------------------------------------\n";
        cout << "\n\nMultiplication of Matrix A and Matrix B :\n\n";
        for (i = 0; i < sizeN; i++)
        {
            for (j = 0; j < sizeN; j++)
            {
                cout << "\t" << arrayC[i][j];
            }
            cout << "\n\n";
        }
        delete[] arrayA;
        delete[] arrayB;
        delete[] arrayC;

        arrayA = NULL;
        arrayB = NULL;
        arrayC = NULL;

    return 0;

    }


void genNumbers( int **arrayA, int **arrayB, int size )
    {
    int generatedNum;

    for( int i = 0; i < size; i++ )
        {
            //srand(time(NULL));
            for( int j = 0; j < size; j++ )
                {
                //srand(time(NULL));
                 arrayA[i][j] = rand()%100;
                 //srand(time(NULL));
                 arrayB[i][j] = rand()%100;
                 
                }
        }

    }
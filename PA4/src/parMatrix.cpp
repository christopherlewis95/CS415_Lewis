#include <iostream>
#include <mpi.h>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <algorithm>
#include <math>

using namespace std;


// tags and const that are important to the project 
#define TERMINATE_TAG 0
#define DATA_TAG 1
#define RESULT_TAG 2
#define MY_MPI_DATA_TAG 3
#define MASTER 0
#define MAX_NUM 100000
#define M_A_DATA 100
#define M_B_DATA 101

// complex struct

// function prototype for calculation
void master(char **argv);
void slave( int taskId );
void shiftLeft( int **mat1, int **mat2, int myProcessor, int numProcessors );
void shiftRight( int **mat1, int **mat2, int myProcessor, int numProcessors );

int getIdLeft( int myProcessor, int numProcessors );
int getIdUp( int myProcessor, int numProcessors );

void genNumbers( int *arrayA, int *arrayB, int *arrayC, int sizeN );

// main function
int main( int argc, char **argv ) {

    int rank;
    int numProcessors;
    MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );


    //genNumbers( arrayA, arrayB, arrayC, sizeN );

    //int numProcessors;
    int *arr;
    int i, j;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string fileName = "data.txt";
    int index = 0;
    int size, num;
    double start, finished, dt;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if( rank == 0 ) // Master
    { 
        master(argv);
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else { // Slave
        slave(rank);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MPI_Finalize();
	return 0;
}

/////////////// THIS IS FOR THE INCLUDED FUNCTION ////////////

void master(char **argv )
    {
    int myRank, numProcessors;
	MPI_Comm_rank( MPI_COMM_WORLD, &myRank );
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );

    int sizeN = atoi(argv[1]);
    int sumMatrixDimension = sizeN/sqrt(numProcessors);
    int fullMatrixDimension = sizeN;
    int blockRowOriginPoint;
    int blockColOriginPoint;
    int processNum;

    // Init Size and populate array with rand Numbers
    FILE *fp;
        fp = fopen(argv[2], "a+");

        int *arrayA = new int [sizeN];
        int *arrayB = new int [sizeN];
        int *arrayC = new int [sizeN];

        int *m_ar = new int [sumMatrixDimension*sumMatrixDimension];
        int *m_br = new int [sumMatrixDimension*sumMatrixDimension];

        int *m_a = new int [sumMatrixDimension*sumMatrixDimension];
        int *m_b = new int [sumMatrixDimension*sumMatrixDimension];

    genNumbers( arrayA, arrayB, arrayC, sizeN);

/**************************
	 Distribution of Matrices
	***************************/
	
	//iterates over the row origins of submatrix blocks of numbers we will send
	for(int yoffset = 0 ; yoffset < sqrt(numProcessors); yoffset++){
		
		//iterates over the column origins of submatrix blocks of numbers we will send
		for(int xoffset = 0; xoffset < sqrt(numProcessors); xoffset++){
			
			//within a given block of numbers iterates over that block's rows
			for(int row = 0; row < sumMatrixDimension; row++){
				
				//within a given block of numbers iterates over that block's cols
				for(int col = 0; col < sumMatrixDimension; col++){
					
					blockRowOriginPoint = ((yoffset * sumMatrixDimension) * fullMatrixDimension);
					blockColOriginPoint = (xoffset*sumMatrixDimension);
					
					//load sub array by iterating over submatrices as located from thier origin in our supermatrix
					m_ar[row*sumMatrixDimension + col] = arrayA[(blockRowOriginPoint + (row*fullMatrixDimension)) + (blockColOriginPoint + col)];
					m_br[row*sumMatrixDimension + col] = arrayB[(blockRowOriginPoint + (row*fullMatrixDimension)) + (blockColOriginPoint + col)];
					
				}
			}
			
			//dustribute our data into processes
			// this formula gives us every process in order
			// with the 2d strcuture of our outer loops
			processNum = yoffset*sqrt(numProcessors) + xoffset;
			
			//if master just copy into local
			// matrices
			if(processNum == MASTER){
				for(int i = 0; i < sumMatrixDimension * sumMatrixDimension; i++){
					m_a[i] = m_ar[i];
					m_b[i] = m_br[i];
				}
			}
			
			//actually send to other processes
			else{
				MPI_Send(m_ar, sumMatrixDimension * sumMatrixDimension, MPI_INT, processNum, M_A_DATA, MPI_COMM_WORLD);
				MPI_Send(m_br, sumMatrixDimension * sumMatrixDimension, MPI_INT, processNum, M_B_DATA, MPI_COMM_WORLD);
			}
			
		}
	}

    }

void slave( int taskId )
    {
    int numProcessors;
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );




    }

void shiftLeft( int **mat1, int **mat2, int myProcessor, int numProcessors )
    {




    }

void shiftUp( int **mat1, int **mat2, int myProcessor, int numProcessors )
    {






    }



int getIdLeft( int myProcessor, int numProcessors )
    {
    int idToMyLeft;

    if(( myProcessor % sqrt(numProcessors)) == 0 )
        {
            idToMyLeft = myProcessor + (sqrt(numProcessors) - 1);
        }

    else{

        idToMyLeft = myProcessor - 1;

        }

    return idToMyLeft;
    }

int getIdUp( int myProcessor, int numProcessors )
    {
    int idAboveMe;

    if(( myProcessor < sqrt(numProcessors))
        {
            idAboveMe = myProcessor + (numProcessors - sqrt(numProcessors));
        }

    else{

        idAboveMe = myProcessor - sqrt(numProcessors);
    }

    return idAboveMe;
    }




void genNumbers( int *arrayA, int *arrayB, int *arrayC, int sizeN )
    {
    for( int index = 0; index < sizeN; index++ )
        {
            //srand(time(NULL));
                //srand(time(NULL));
                 arrayA[index] = rand()%100;
                 
                 //srand(time(NULL));
                 arrayB[index] = rand()%100;
                 
                 // Set array C to 0 (For proper calculations)
                 arrayC[index] = 0;
        }

    }

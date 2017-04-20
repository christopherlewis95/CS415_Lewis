#include <iostream>
#include <mpi.h>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <algorithm>
#include <math.h>

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
void shiftLeft( int *matA, int size, int myProcessor, int numProcessors );
void shiftRight( int *matB, int size, int myProcessor, int numProcessors );

int getIdLeft( int myProcessor, int numProcessors );
int getIdUp( int myProcessor, int numProcessors );

int getIdRight( int myProcessor, int numProcessors );
int getIdDown( int myProcessor, int numProcessors );

void genNumbers( int *arrayA, int *arrayB, int *arrayC, int sizeN );
void genZeroes( int **arrayC, int sizeN )

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

        int *arrayA = new int [sizeN*sizeN];
        int *arrayB = new int [sizeN*sizeN];
        int *arrayC = new int [sizeN*sizeN];

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
    int shiftAmnt = taskId;
    int shifts;
    int subMatrixSize;
    MPI_Status status;

    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );

    MPI_Probe(MASTER, M_A_DATA, MPI_COMM_WORLD, &status );

    MPI_Get_count( &status, MPI_INT, &subMatrixSize );

    int *arrayA = new int [subMatrixSize];

    MPI_Probe(MASTER, M_B_DATA, MPI_COMM_WORLD, &status );

    MPI_Get_count( &status, MPI_INT, &subMatrixSize );

    int *arrayB = new int [subMatrixSize];


    /* ///////////////

    INIT 2D ARAYS

    */ ///////////////

    int **myA = new int *[subMatrixSize/sqrt(numProcessors)];
    int **myB = new int *[subMatrixSize/sqrt(numProcessors)];
    int **myC = new int *[subMatrixSize/sqrt(numProcessors)];

    for( int i = 0; i < subMatrixSize; i++ )
    {
    myA[i] = new int [subMatrixSize/sqrt(numProcessors)];
    myB[i] = new int [subMatrixSize/sqrt(numProcessors)];
    myC[i] = new int [subMatrixSize/sqrt(numProcessors)];
    }

    genZeroes(myC, subMatrixSize/sqrt(numProcessors) );

//////////////////////////////////////////////////////////////////////////////////////////////
    // Initial shift (Shift Amount is made by task id % sqrtNumP)
    for( shifts = 0; shifts < shiftAmnt % sqrt(numProcessors); shifts++ )
        {
        shiftLeft( arrayA, subMatrixSize, taskId, numProcessors );
        shiftUp( arrayB, subMatrixSize, taskId, numProcessors );
        }
//////////////////////////////////////////////////////////////////////////////////////////////

    /* ///////////////

    CONVERT 2D ARAYS

    */ ///////////////

    for( int i = 0; i < subMatrixSize/sqrt(numProcessors); i++)
    {
        for( int j = 0; j < subMatrixSize/sqrt(numProcessors); j++)
            {

                myA[i][j] = arrayA[ (j * (subMatrixSize/sqrt(numProcessors))) + i];
                myB[i][j] = arrayB[ (j * (subMatrixSize/sqrt(numProcessors))) + i];

            }
    }


    // Optimize Vars Later
    /* MULTIPLY THE NUMBERS */
    for (int i = 0; i < sizeN; i++)
    {
        for (int j = 0; j < (subMatrixSize/sqrt(numProcessors); j++)
        {
            for (int k = 0; k < (subMatrixSize/sqrt(numProcessors); k++)
            {
                myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j];
            }
        }
    }



    
    }

void shiftLeft( int *matA, int size, int myProcessor, int numProcessors )
    {
    int destProcessor;
    MPI_Status status;


    destProcessor = getIdLeft( myProcessor, numProcessors );

    int MPI_Sendrecv_replace(matA, size, MPI_INT, destProcessor, M_A_DATA, MPI_ANY_SOURCE, M_A_DATA,
                       MPI_COMM_WORLD, status);

    }

void shiftUp( int *matB, int size, int myProcessor, int numProcessors )
    {

    int destProcessor;

    destProcessor = getIdUp( myProcessor, numProcessors );

    int MPI_Sendrecv_replace(matB, size, MPI_INT, destProcessor, M_B_DATA, MPI_ANY_SOURCE, M_B_DATA,
                       MPI_COMM_WORLD, status);


    }



int getIdLeft( int myProcessor, int numProcessors )
    {
    int idToMyLeft;

    if(( myProcessor % (int)sqrt(numProcessors)) == 0 )
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

    if(( myProcessor < sqrt(numProcessors)))
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
    for( int index = 0; index < (sizeN * sizeN); index++ )
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

void genZeroes( int **arrayC, int sizeN )
    {
    for( int index = 0; index < sizeN; index++ )
        {
            for( int j = 0; j < sizeN; j++ )
                 arrayC[index][j] = 0;
        }

    }

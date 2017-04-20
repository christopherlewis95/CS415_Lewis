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

/*
Function to do all computations for master
*/
void master(char **argv);

/*
Function that takes all data from master thats been sent and does its own calculations
*/
void slave( int taskId );

/*
Makes a whole shift left using a send replace functions and uses position to find it out
*/
void shiftLeft( int *matA, int size, int myProcessor, int numProcessors );

/*
Makes a whole shift up using a send replace functions and uses position to find it out
*/
void shiftUp( int *matB, int size, int myProcessor, int numProcessors );

/*
Finds the id of the processor that is to the left of the current processor (myProcessor)
*/
int getIdLeft( int myProcessor, int numProcessors );

/*
Finds the id of the processor that is above the current processor (myProcessor)
*/
int getIdUp( int myProcessor, int numProcessors );

/*
Finds the id of the processor that is to the right of the current processor (myProcessor)
*/
int getIdRight( int myProcessor, int numProcessors );

/*
Finds the id of the processor that is below the current processor (myProcessor)
*/
int getIdDown( int myProcessor, int numProcessors );

/*
Generates random numbers for arrays A and B. Sets C to 0
*/
void genNumbers( int *arrayA, int *arrayB, int *arrayC, int sizeN );

/*
Generates zeroes for C (Needed for Slave)
*/
void genZeroes( int **arrayC, int sizeN );

// main function
int main( int argc, char **argv ) {

    int rank;
    int numProcessors;
    MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );

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

    // Initialize Variables
    int sizeN = atoi(argv[1]);
    int sumMatrixDimension = sizeN/sqrt(numProcessors);
    int fullMatrixDimension = sizeN;
    int rowOriginForSubMatrix;
    int colOriginForSubMatrix;
    int processNum;
    int subMatrixSize = sumMatrixDimension*sumMatrixDimension;
    int shiftAmnt = MASTER; // For Initial Shift
    int shifts;


    // Init Size and populate array with rand Numbers

        int *arrayA = new int [sizeN*sizeN];
        int *arrayB = new int [sizeN*sizeN];

        int *sendArrayA = new int [subMatrixSize];
        int *sendArrayB = new int [subMatrixSize];

        int *myArrayA = new int [subMatrixSize];
        int *myArrayB = new int [subMatrixSize];

    genNumbers( arrayA, arrayB, arrayC, sizeN);

	
	// go though the rows with offset
	for(int verticalOffset = 0 ; verticalOffset < sqrt(numProcessors); verticalOffset++)
        {
		
		// go thorugh the columns using the offset
		for(int horizontalOffset = 0; horizontalOffset < sqrt(numProcessors); horizontalOffset++)
            {
			
			//go trhough the rows of submatrix
			for(int row = 0; row < sumMatrixDimension; row++)
                {
				
				// go throguh the cols of submatrix
				for(int col = 0; col < sumMatrixDimension; col++)
                    {
					
                    // get location in the submatrix
					rowOriginForSubMatrix = ((verticalOffset * sumMatrixDimension) * fullMatrixDimension);
					colOriginForSubMatrix = (horizontalOffset*sumMatrixDimension);
					
					//load sub array by going through the submatrix by its location found
					sendArrayA[row*sumMatrixDimension + col] = arrayA[(rowOriginForSubMatrix + (row*fullMatrixDimension)) + (colOriginForSubMatrix + col)];
					sendArrayB[row*sumMatrixDimension + col] = arrayB[(rowOriginForSubMatrix + (row*fullMatrixDimension)) + (colOriginForSubMatrix + col)];
					
				    }
			    }
			
			// send dtata to processes
			processNum = verticalOffset*sqrt(numProcessors) + horizontalOffset;
			
			//if the process num is MASTER put data in myArray<A or B>
			if(processNum == MASTER)
            {
				for(int i = 0; i < subMatrixSize; i++)
                {
					myArrayA[i] = sendArrayA[i];
					myArrayB[i] = sendArrayB[i];
				}
			}
			
			//actually send to other processes
			else{
				MPI_Send(sendArrayA, subMatrixSize, MPI_INT, processNum, M_A_DATA, MPI_COMM_WORLD);
				MPI_Send(sendArrayB, subMatrixSize, MPI_INT, processNum, m_B_DATA, MPI_COMM_WORLD);
			}
			
		}
	}

/*/////////////////////////////////////////////////////

                START THE MATRIX MATH HERE

////////////////////////////////////////////////////*/

 /* ///////////////

    INIT MY 2D ARAYS

    */ ///////////////

    int **myA = new int *[(int)(subMatrixSize/sqrt(numProcessors))];
    int **myB = new int *[(int)(subMatrixSize/sqrt(numProcessors))];
    int **myC = new int *[(int)(subMatrixSize/sqrt(numProcessors))];

    for( int i = 0; i < subMatrixSize; i++ )
    {
    myA[i] = new int [(int)(subMatrixSize/sqrt(numProcessors))];
    myB[i] = new int [(int)(subMatrixSize/sqrt(numProcessors))];
    myC[i] = new int [(int)(subMatrixSize/sqrt(numProcessors))];
    }

    genZeroes(myC, (int)(subMatrixSize/sqrt(numProcessors)) );

//////////////////////////////////////////////////////////////////////////////////////////////
    // Initial shift (Shift Amount is made by task id % sqrtNumP)
    for( shifts = 0; shifts < shiftAmnt % (int)sqrt(numProcessors); shifts++ )
        {
        shiftLeft( myArrayA, sumMatrixDimension * sumMatrixDimension, MASTER, numProcessors );
        shiftUp( myArrayB, sumMatrixDimension * sumMatrixDimension, MASTER, numProcessors );
        }
//////////////////////////////////////////////////////////////////////////////////////////////

    /* ///////////////

    CONVERT 2D ARAYS

    */ ///////////////

    for( int i = 0; i < subMatrixSize/sqrt(numProcessors); i++)
    {
        for( int j = 0; j < subMatrixSize/sqrt(numProcessors); j++)
            {

                myA[i][j] = arrayA[ (j * (int)(subMatrixSize/sqrt(numProcessors))) + i];
                myB[i][j] = arrayB[ (j * (int)(subMatrixSize/sqrt(numProcessors))) + i];

            }
    }


    // Optimize Vars Later
    /* MULTIPLY THE NUMBERS */
    for (int i = 0; i < (int)(subMatrixSize/sqrt(numProcessors)); i++)
    {
        for (int j = 0; j < (int)(subMatrixSize/sqrt(numProcessors)); j++)
        {
            for (int k = 0; k < (int)(subMatrixSize/sqrt(numProcessors)); k++)
            {
                myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j];
            }
        }
    }

    }

void slave( int taskId )
    {
    int numProcessors;
    int shiftAmnt = taskId; // For Initial Shift
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

    int **myA = new int *[(int)(subMatrixSize/sqrt(numProcessors))];
    int **myB = new int *[(int)(subMatrixSize/sqrt(numProcessors))];
    int **myC = new int *[(int)(subMatrixSize/sqrt(numProcessors))];

    for( int i = 0; i < subMatrixSize; i++ )
    {
    myA[i] = new int [(int)(subMatrixSize/sqrt(numProcessors))];
    myB[i] = new int [(int)(subMatrixSize/sqrt(numProcessors))];
    myC[i] = new int [(int)(subMatrixSize/sqrt(numProcessors))];
    }

    genZeroes(myC, (int)(subMatrixSize/sqrt(numProcessors)) );

//////////////////////////////////////////////////////////////////////////////////////////////
    // Initial shift (Shift Amount is made by task id % sqrtNumP)
    for( shifts = 0; shifts < shiftAmnt % (int)sqrt(numProcessors); shifts++ )
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

                myA[i][j] = arrayA[ (j * (int)(subMatrixSize/sqrt(numProcessors))) + i];
                myB[i][j] = arrayB[ (j * (int)(subMatrixSize/sqrt(numProcessors))) + i];

            }
    }


    // Optimize Vars Later
    /* MULTIPLY THE NUMBERS */
    for (int i = 0; i < (int)(subMatrixSize/sqrt(numProcessors)); i++)
    {
        for (int j = 0; j < (int)(subMatrixSize/sqrt(numProcessors)); j++)
        {
            for (int k = 0; k < (int)(subMatrixSize/sqrt(numProcessors)); k++)
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

    int MPI_Sendrecv_replace(matA, size, MPI_INT, destProcessor, M_A_DATA, MPI_ANY_SOURCE, M_A_DATA, MPI_COMM_WORLD, &status);

    }

void shiftUp( int *matB, int size, int myProcessor, int numProcessors )
    {

    int destProcessor;
    MPI_Status status;

    destProcessor = getIdUp( myProcessor, numProcessors );

    int MPI_Sendrecv_replace(matB, size, MPI_INT, destProcessor, M_B_DATA, MPI_ANY_SOURCE, M_B_DATA, MPI_COMM_WORLD, &status);


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

/*
int getIdRight( int myProcessor, int numProcessors )
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


int getIdDown( int myProcessor, int numProcessors )
    {
    int idBelowMe;

    if(( myProcessor > (numProcessors - sqrt(numProcessors)))
        {
            idBelowMe = myProcessor + (numProcessors - sqrt(numProcessors));
        }

    else{

        idBelowMe = myProcessor - sqrt(numProcessors);
    }

    return idBelowMe;
    }
*/


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

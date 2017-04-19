#include <iostream>
#include <mpi.h>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <algorithm>

using namespace std;


// tags and const that are important to the project 
#define TERMINATE_TAG 0
#define DATA_TAG 1
#define RESULT_TAG 2
#define MY_MPI_DATA_TAG 3
#define MASTER 0
#define MAX_NUM 100000

// complex struct

// function prototype for calculation
void master(char **argv);
void slave( int taskId );
void genNumbers( int **arrayA, int **arrayB, int **arrayC, int sizeN );

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
    // Init Size and populate array with rand Numbers
        int sizeN = atoi(argv[1]);
        fp = fopen(argv[2], "a+");

        int **arrayA = new int *[sizeN];
        int **arrayB = new int *[sizeN];
        int **arrayC = new int *[sizeN];  

        for(int i = 0; i < sizeN; i++)
        {
        arrayA[i] = new int[sizeN];  
        arrayB[i] = new int[sizeN];  
        arrayC[i] = new int[sizeN];      
        }
    genNumbers( arrayA, arrayB, arrayC, sizeN)
    


    }

void slave( int taskId )
    {


    }

void genNumbers( int **arrayA, int **arrayB, int **arrayC, int sizeN )
    {
    for( int rowIndex = 0; rowIndex < sizeN; rowIndex++ )
        {
            //srand(time(NULL));
            for( int columnIndex = 0; columnIndex < sizeN; columnIndex++ )
                {
                //srand(time(NULL));
                 arrayA[rowIndex][columnIndex] = rand()%100;
                 
                 //srand(time(NULL));
                 arrayB[rowIndex][columnIndex] = rand()%100;
                 
                 // Set array C to 0 (For proper calculations)
                 arrayC[rowIndex][columnIndex] = 0;
                }
        }

    }

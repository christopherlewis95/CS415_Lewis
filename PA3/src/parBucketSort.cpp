#include <iostream>
#include <mpi.h>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;


// tags and const that are important to the project 
#define TERMINATE_TAG 0
#define DATA_TAG 1
#define RESULT_TAG 2
#define MY_MPI_DATA_TAG 3

// complex struct

// function prototype for calculation
void slave();
void master();

// main function
int main( int argc, char **argv ) {
    int rank;
    int numProcessors;
    MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );
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

    ifstream fin;
    fin.open( fileName.c_str() );
    fin >> size;

    MPI_Bcast( size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    cout << size << endl;
    arr = new int [size/numProcessors];
    MPI_Status status;
    for( i = 1; i < numProcessors; i++) // 'I' is processor
        {
        for( j = 0; j < size/numProcessors; j++ )
            {
            fin >> num;
            arr[j] = num;
            // cout << arr[j] << endl;
            }
        MPI_Send(arr, size/numProcessors, MPI_INT, i, DATA_TAG, MPI_COMM_WORLD); // Make size/numProcessors a better variable
        }
    fin.close();
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else { 
        //int size;
        //MPI_Bcast( &size, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cout << size;
        MPI_Status status;
        MPI_Recv( arr, size/numProcessors, MPI_INT, 0, MY_MPI_DATA_TAG, MPI_COMM_WORLD, &status ); // '0' needs to be master variable
        cout << arr[0] << endl;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MPI_Finalize();
	return 0;
}

/////////////// THIS IS FOR THE INCLUDED FUNCTION ////////////


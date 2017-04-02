#include <iostream>
#include <mpi.h>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;


// tags and const that are important to the project 
#define TERMINATE_TAG 0
#define DATA_TAG 1
#define RESULT_TAG 2

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
    double start, finished, dt;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if( rank == 0 ) // Master
    { 
    int size, num;
    ifstream fin;
    fin.open( fileName.c_str() );
    cout << "This is it: \n";
    fin >> size; 
    cout << size << endl;
    arr = new int [size/numProcessors];
    MPI_Status status;
    for( i = 1; i < numProcessors; i++)
        {

        for( j = 0; j < size/numProcessors; j++ )
            {
            fin >> num;
            arr[j] = num;

            }
        MPI_Send(&arr, 1, MPI_INT, i, DATA_TAG, MPI_COMM_WORLD);
        }
    fin.close();
	}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else { 
        MPI_Status status;	
        MPI_Recv( &arr, 10000/numProcessors, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
        cout << arr[0] << endl;

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MPI_Finalize();
	return 0;
}

/////////////// THIS IS FOR THE INCLUDED FUNCTION ////////////


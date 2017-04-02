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
    ifstream fin;
    int size, num;
    int index = 0;
    double start, finished, dt;

    fin.open( fileName.c_str() );
    fin >> size; 
    cout << size << endl;
    arr = new int [size/numProcessors];
   // int input_ar[size];

    // Get slaves work... GOOTA work
    /*


    */
    /*
    while( !fin.eof() )
        {
           // for( i = 0; i < size/numProcessors; i++)
            fin >> num;
            input_ar[index] = num;
            // cout << input_ar[index] << endl;
            index++;
        }
   // cout << *arr << endl;
   */


  //int n = sizeof (input_ar) / sizeof (input_ar[0]);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // initialize variables
	// get rank to distinguish processors 


	if( rank == 0 ) // Master
    { 
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

	}
 
	else { 
        MPI_Status status;	
        MPI_Recv( &arr, size/numProcessors, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
        cout << arr[0] << endl;

    }

    fin.close();
	MPI_Finalize();
	return 0;
}

/////////////// THIS IS FOR THE INCLUDED FUNCTION ////////////


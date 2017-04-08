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
#define MASTER 0

// complex struct

// function prototype for calculation
void master(char **argv);
void slave( int taskId );
void genNumbers( int *genArray, int size );

// main function
int main( int argc, char **argv ) {
    int rank;
    int numProcessors;
    MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

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
    int i;
    int numProcessors;
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );
    MPI_Status status;
    int capacity = atoi(argv[1]);
    int counter = 0;
    int split = capacity/numProcessors;
    int *masterArray = new int[split];
    int index = 0;
    /*
    for( i = 1; i < numProcessors; i++ )
        MPI_Send(size, 1, MPI_INT, i, DATA_TAG, MPI_COMM_WORLD); 
    */
   // cout << size << endl;
    int *arr = new int [capacity];
    genNumbers( arr, capacity );

    cout << "Entering the send" << endl;
    for( i = 1; i < numProcessors; i++) // 'I' is processor
        {
        cout << "Sending to processor: " << i << " " << endl;
        MPI_Send(&arr[counter], split, MPI_INT, i, MY_MPI_DATA_TAG, MPI_COMM_WORLD); // Make size/numProcessors a better variable
        counter += split;
        cout << "Sent message to processor: " << i << " " << endl;
        cout << "counter is: " << counter << " " << endl;
        }
        
        MPI_Barrier(MPI_COMM_WORLD ); //// STOPPPED AT MPI_Barrier

    while( counter < capacity )
        {  
        masterArray[index] = arr[counter];
        counter++;
        index++;
        }
    
    // Free Memory
    delete arr;
    arr = NULL;


    //fin.close();
    }

void slave( int taskId )
    {
    cout << "Entering the send" << endl;
    int capacity;
    MPI_Request req;
    MPI_Status status;

    cout << "Probing " << endl;
    MPI_Probe(MASTER, MY_MPI_DATA_TAG, MPI_COMM_WORLD, &status );
    cout << "Done Probing " << endl;

    MPI_Get_count( &status, MPI_INT, &capacity );
    cout << "Got Capacity of: " << capacity << endl;

    int *arr = new int [capacity];

    cout << capacity << endl;

    MPI_Recv( arr, capacity, MPI_INT, 0, MY_MPI_DATA_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE ); // '0' needs to be master variable

    MPI_Barrier(MPI_COMM_WORLD); // Stopped at MPI Barrier
    cout << arr[0] << endl;
    }

void genNumbers( int *genArray, int size )
    {
    int generatedNum;

    for( int i = 0; i < size; i++ )
        {
            srand(1000); // Use a seed value
            genArray[i] = rand()%100000;
        }

    }

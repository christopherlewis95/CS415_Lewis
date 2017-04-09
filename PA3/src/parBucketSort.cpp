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
    FILE *fpMaster;
    fpMaster = fopen( argv[2], "a+" );

    double t0, deltaTime, end;

    int i;
    int numProcessors;
    int index = 0;
    int index2, index3;
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );
  // cout << "Number of processors is: " << numProcessors << endl;
    MPI_Status status;
    int capacity = atoi(argv[1]);
    int counter = 0;
    int split = capacity/numProcessors;
    int partition = MAX_NUM / numProcessors;
    int *masterArray = new int[split];
    int delta;
    int bucketPlacement;
    vector <int> myInts[numProcessors];
    vector <int> myBigBucket;
    vector <int> myRecievedBucket;
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
        MPI_Send(&arr[counter], split, MPI_INT, i, MY_MPI_DATA_TAG, MPI_COMM_WORLD); // Make size/numProcessors a better variable
        counter += split;
        }
        
        MPI_Barrier(MPI_COMM_WORLD ); // STOPPED AT MPI_Barrier
      t0 = MPI_Wtime();
        
    cout << "Masters numbers is: " << endl;
    delta = capacity - counter;
    while( counter < capacity )
        {  
        masterArray[index] = arr[counter];
        counter++;
        index++;
        }
        

    for( index = 0; index < delta; index++ )
        {
        //fprintf( fpMaster,  "Master Placement is:  %d \n", masterArray[index]/partition );
       // cout << "Master placement is: " << masterArray[index]/partition << endl;
        bucketPlacement = masterArray[index]/partition;
        myInts[bucketPlacement].push_back(masterArray[index]);
        }
        
        /* PLACE MY NUMBERS INSIDE BIG BUCKET */
        


    ////////////////////////////////////////////////////////////////////////////////////////

                    /* SENDING AND RECIEVING SMALL BUCKETS */

    /////////////////////////////////////////////////////////////////////////////////////////


   // cout << "Masters small buckets: " << endl;

    for( index = 0; index < numProcessors; index++ )
        {
            if( index == MASTER )
                {
                   for( index2 = 0; index2 < numProcessors; index2++ )
                        {
                            if( index2 != MASTER )
                                {
                                    myRecievedBucket.clear();
                                    //myRecievedBucket.resize(0);
                                 //   fprintf( fpMaster,  "Probe \n" );
                                    MPI_Probe(index2, MY_MPI_DATA_TAG, MPI_COMM_WORLD, &status );

                                    MPI_Get_count( &status, MPI_INT, &capacity );

                                    myRecievedBucket.resize(capacity);
                                 //   fprintf( fpMaster,  "MASTER RECV\n" );
                                  //  cout << "Master Recv" << endl;
                                    MPI_Recv( &myRecievedBucket[0], capacity, MPI_INT, index2, MY_MPI_DATA_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE ); // '0' needs to be master variable

                                  //  fprintf( fpMaster,  "MASTER RECVIED\n" );
                                        for( index3 = 0; index3 < capacity; index3++ )
                                            {
                                                if( !myRecievedBucket.empty())
                                                myBigBucket.push_back(myRecievedBucket[index3]);
                                            }
                                  //  fprintf( fpMaster,  "MASTER DONATED TO BUCKET\n" );
                                        
                                   // MPI_Barrier(MPI_COMM_WORLD); // Stopped at MPI Barrier
                                }


                        }



                }

            else{

                MPI_Send(&myInts[index][0], myInts[index].size(), MPI_INT, index, MY_MPI_DATA_TAG, MPI_COMM_WORLD); // Make size/numProcessors a better variable

            }


        }

        /*
    for( index = 0; index < myInts[0].size(); index++ )
        {
        myBigBucket.push_back(myInts[0].size())
        }
        */

        sort(myBigBucket.begin(), myBigBucket.end());

       // for( int test = 0; test < myBigBucket.size(); test++)
          //  fprintf( fpMaster, "Master sorted bucket: %d \n", myBigBucket[test]);

        MPI_Barrier(MPI_COMM_WORLD); // Stopped at MPI Barrier

        end = MPI_Wtime();


        fprintf(fpMaster, "%d, %f\n", atoi(argv[1]), end - t0 );

    // Free Memory
    delete arr;
    arr = NULL;

   // delete masterArray;
   // masterArray = NULL;
    //fin.close();
  //  fclose(fpMaster);
    }

void slave( int taskId )
    {
   // FILE *fpSlave;
   // fpSlave = fopen( "slaveStuff.txt", "w" );

    int numProcessors;
    int index, index2, index3;
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );


  //  fprintf( fpSlave, "Entering the recieve with rank: %d \n", taskId );
  //  cout << "Entering the recieve with rank: " << taskId << " " << endl;
    int capacity;
    MPI_Request req;
    MPI_Status status;
    vector <int> myInts[numProcessors];
    int partition = MAX_NUM / numProcessors;
    int small_bucket_index;
    int bucketPlacement;
    vector <int> myBigBucket;
    vector <int> myRecievedBucket;


  //  cout << "Probing " << endl;
    MPI_Probe(MASTER, MY_MPI_DATA_TAG, MPI_COMM_WORLD, &status );

    MPI_Get_count( &status, MPI_INT, &capacity );

    int *arr = new int [capacity];

    //cout << capacity << endl;
    MPI_Recv( arr, capacity, MPI_INT, 0, MY_MPI_DATA_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE ); // '0' needs to be master variable

    MPI_Barrier(MPI_COMM_WORLD); // Stopped at MPI Barrier

    for( index = 0; index < capacity; index++ )
        {
          //  fprintf( fpSlave,  "Placement is:  %d \n", arr[index]/partition );
          //  cout << "Placement is: " << arr[index]/partition << endl;
            bucketPlacement = arr[index]/partition;
            myInts[bucketPlacement].push_back(arr[index]);
        }



    ////////////////////////////////////////////////////////////////////////////////////////

                    /* SENDING AND RECIEVING SMALL BUCKETS */

    /////////////////////////////////////////////////////////////////////////////////////////

    // Better variable names will suffice

  //  cout << "Slaved small buckets: " << endl;

    for( index = 0; index < numProcessors; index++ )
        {
            if( index == taskId )
                {
                    for( index2 = 0; index2 < numProcessors; index2++ )
                        {
                            if( index2 != taskId )
                                {

                                    MPI_Probe(index2, MY_MPI_DATA_TAG, MPI_COMM_WORLD, &status );

                                    MPI_Get_count( &status, MPI_INT, &capacity );

                                    myRecievedBucket.resize(capacity);
                                 //   cout << "Slaved Recv" << endl;
                                    MPI_Recv( &myRecievedBucket[0], capacity, MPI_INT, index2, MY_MPI_DATA_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE ); // '0' needs to be master variable

                                        for( index3 = 0; index3 < capacity; index3++ )
                                            {
                                                if( !myRecievedBucket.empty())
                                                myBigBucket.push_back( myRecievedBucket[index3] );
                                            }
                                  //  MPI_Barrier(MPI_COMM_WORLD); // Stopped at MPI Barrier

                                }


                        }


                }

            else{

                MPI_Send(&myInts[index][0], myInts[index].size(), MPI_INT, index, MY_MPI_DATA_TAG, MPI_COMM_WORLD); // Make size/numProcessors a better variable

            }



        }
        sort(myBigBucket.begin(), myBigBucket.end());
        MPI_Barrier(MPI_COMM_WORLD); // Stopped at MPI Barrier



     //   fclose(fpSlave);

    }

void genNumbers( int *genArray, int size )
    {
    int generatedNum;

    for( int i = 0; i < size; i++ )
        {
            //srand(1000); // Use a seed value
            genArray[i] = rand()%100001;
        }

    }

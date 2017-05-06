/*
Project 4: Matrix Multiplication
Name: ##################
Due: April 20th, 2017 
*/

// Header files
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
#define M_A_DATA 10
#define M_B_DATA 11

// function prototype for calculation

/*
Function to do all computations for master
*/
void master( char **argv, int argc );

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
void genNumbers( int *arrayA, int *arrayB, int *arrayC, int sizeN, int argc, char **argv );

/*
Generates zeroes for C (Needed for Slave)
*/
void genZeroes( int **arrayC, int sizeN );



void initShift(int myrank, int numCores, int left, int up, int right, int down, int size, int root, int* dataA, int* dataB);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// main function
int main( int argc, char **argv ) {
    /*
    */
// /
    int rank;
    int numProcessors;
    MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );
    
    FILE *masterFp;
    masterFp = fopen("main.txt", "a+");
  


   

    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if( rank == 0 ) // Master
    { 
        master(argv, argc);
	}
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else 
    { 
        // Slave I plulled down this curly cause that might have cause issues... you never know with todays society

        slave(rank);
    }
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MPI_Finalize();
    
	return 0;
}

/////////////// THIS IS FOR THE INCLUDED FUNCTION ////////////

void master(char **argv, int argc )
    {
    
    FILE *masterFp;
    masterFp = fopen("master.txt", "a+");
    int myRank, numProcessors;
	MPI_Comm_rank( MPI_COMM_WORLD, &myRank );
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );

    
    

    // Initialize Variables
    int sizeN = atoi(argv[1]);
    int sumMatrixDimension = sizeN/(int)sqrt(numProcessors);
    int fullMatrixDimension = sizeN;
    int rowOriginForSubMatrix;
    int colOriginForSubMatrix;
    int processNum;
    int subMatrixSize = sumMatrixDimension*sumMatrixDimension;
    int shiftAmnt = MASTER; // For Initial Shift
    int shifts;
    int loopAmnt;


    // Init Size and populate array with rand Numbers


        int *arrayA = new int [sizeN*sizeN];
        int *arrayB = new int [sizeN*sizeN];
        int *arrayC = new int [sizeN*sizeN];

        int *sendArrayA = new int [subMatrixSize];
        int *sendArrayB = new int [subMatrixSize];

        int *myArrayA = new int [subMatrixSize];
        int *myArrayB = new int [subMatrixSize];


    genNumbers( arrayA, arrayB, arrayC, sizeN, argc, argv);
	


	// go though the rows with offset
	for(int verticalOffset = 0 ; verticalOffset < (int)sqrt(numProcessors); verticalOffset++)
        {
		
		// go thorugh the columns using the offset
		for(int horizontalOffset = 0; horizontalOffset < (int)sqrt(numProcessors); horizontalOffset++)
            {
			
			//go trhough the rows of submatrix
			for(int row = 0; row < sumMatrixDimension; row++)
                {
                    ////
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
			processNum = verticalOffset*(int)sqrt(numProcessors) + horizontalOffset;
			
            


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
			else if(processNum > MASTER){
                
            
            
                // MPI_Send(&arr[counter], split, MPI_INT, i, MY_MPI_DATA_TAG, MPI_COMM_WORLD); 

            
                for( int i = 0; i < subMatrixSize; i++ )
                    {

                    

                    }
                

				MPI_Send(sendArrayA, subMatrixSize, MPI_INT, processNum, M_A_DATA, MPI_COMM_WORLD);
                // MPI_Barrier(MPI_COMM_WORLD);

            
                for( int i = 0; i < subMatrixSize; i++ )
                    {

                    

                    }
                


				MPI_Send(sendArrayB, subMatrixSize, MPI_INT, processNum, M_B_DATA, MPI_COMM_WORLD);
            
               // MPI_Barrier(MPI_COMM_WORLD);
            
                
			}
            
			
		}
       // MPI_Barrier(MPI_COMM_WORLD);
    
	}


// ADD A BARRIER 



/////////////////////////////////////////////////////

               // START THE MATRIX MATH HERE

////////////////////////////////////////////////////

    int twoDimSplit = (int)(subMatrixSize/(int)sqrt(subMatrixSize));




    int **myA = new int *[twoDimSplit];
    int **myB = new int *[twoDimSplit];
    int **myC = new int *[twoDimSplit];

    for( int i = 0; i < twoDimSplit; i++ )
    {
    myA[i] = new int [twoDimSplit];
    myB[i] = new int [twoDimSplit];
    myC[i] = new int [twoDimSplit];
    }




    genZeroes(myC, (int)(subMatrixSize/(int)sqrt(subMatrixSize)) );


    MPI_Barrier(MPI_COMM_WORLD);





     for(int i = 0; i < subMatrixSize; i++){

    

     }
    


     for(int i = 0; i < subMatrixSize; i++){

    


     }
    


////////////////////////
for( loopAmnt = 0; loopAmnt < (int)sqrt(numProcessors); loopAmnt++ )
    {

 ///////////////

 ///   CONVERT 2D ARAYS

///////


int offset = subMatrixSize/(int)sqrt(subMatrixSize);
int offsetTimesJ;


    for( int i = 0; i < subMatrixSize/(int)sqrt(subMatrixSize); i++)
    {
        for( int j = 0; j < subMatrixSize/(int)sqrt(subMatrixSize); j++)
            {
                offsetTimesJ = j * offset;

                //Add offset * y to the lenggth
                myA[i][j] = arrayA[ offsetTimesJ + i]; ////////// May need to sway I and J
              



                myB[i][j] = arrayB[ offsetTimesJ + i]; //////////

              
            }
    }

    // Optimize Vars Later
    // MULT NUMBER
    int loopLength = (int)sqrt(subMatrixSize);



    for (int i = 0; i < loopLength; i++)
    {
        for (int j = 0; j < loopLength; j++)
        {
            for (int k = 0; k < loopLength; k++)
            {
                myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j];
            }
        }
    }
    


    // Put into 1D array for passing
    for( int i = 0; i < subMatrixSize/(int)sqrt(subMatrixSize); i++)
    {
        for( int j = 0; j < subMatrixSize/(int)sqrt(subMatrixSize); j++)
            {
                for( int k = 0; k < subMatrixSize; k++ )
                    {
                        arrayA[k] = myA[i][j];
                        arrayB[k] = myB[i][j];
                    }
            }
    }



//////////////////////////////////////////////////////////////////////////////////////////////
    // Do final shift (Shift Amount is made by task id % sqrtNumP)
        shiftLeft( arrayA, subMatrixSize, myRank, numProcessors );
        shiftUp( arrayB, subMatrixSize, myRank, numProcessors );
        MPI_Barrier(MPI_COMM_WORLD);
//////////////////////////////////////////////////////////////////////////////////////////////
    }



MPI_Barrier(MPI_COMM_WORLD);

    FILE *outMaster;




    outMaster = fopen("DataResults.txt","a+");


    for( int count = 0; count < numProcessors; count++ )
    {

    	if( count == myRank )
    	{

   		 for( int i = 0; i < (int)sqrt(subMatrixSize); i++)
        	{
            for( int j = 0; j < (int)sqrt(subMatrixSize); j++)
                {
                  
                }
          
       		}
    	}
	MPI_Barrier(MPI_COMM_WORLD);
    }
    
    

///////////////
    // DELETE THESE SAVAGE BEASTS

        
        delete arrayA;
      delete arrayB;
        delete arrayC;

        delete sendArrayA;
        delete sendArrayB;

        delete myArrayA;
        delete myArrayB;
        
        arrayA = NULL;
       arrayB = NULL;
       arrayC = NULL;

       sendArrayA = NULL;
       sendArrayB = NULL;

       myArrayA = NULL;
       myArrayB = NULL;
        

    }

void slave( int taskId )
    {

    
    FILE *fp;
    fp = fopen("slave.txt", "a+");
    
    int myRank;

    MPI_Comm_rank( MPI_COMM_WORLD, &myRank );

    
//////////////////////////////
    
    int numProcessors;
   // int shiftAmnt = taskId; // For Initial Shift
    int shiftAmnt = myRank;
    int shifts;
    int subMatrixSize;
    MPI_Status status;
    int loopAmnt;

      
    MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );

    MPI_Probe(MASTER, M_A_DATA, MPI_COMM_WORLD, &status );

    MPI_Get_count( &status, MPI_INT, &subMatrixSize );

    int *arrayA = new int [subMatrixSize];


     MPI_Recv( arrayA, subMatrixSize, MPI_INT, 0, M_A_DATA, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
   
    

    

    MPI_Probe(MASTER, M_B_DATA, MPI_COMM_WORLD, &status );
 
    MPI_Get_count( &status, MPI_INT, &subMatrixSize );


    int *arrayB = new int [subMatrixSize];


   
    
     MPI_Recv( arrayB, subMatrixSize, MPI_INT, MASTER, M_B_DATA, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
    // MPI_Barrier(MPI_COMM_WORLD);

    
    

     for(int i = 0; i < subMatrixSize; i++){

    

     }
    


     for(int i = 0; i < subMatrixSize; i++){

    


     }
    
     
    //    INIT 2D ARAYS




    int SmallBoxDimension = ((int)sqrt(subMatrixSize));

    int **myA = new int *[SmallBoxDimension];
    int **myB = new int *[SmallBoxDimension];
    int **myC = new int *[SmallBoxDimension];
    



    for( int i = 0; i < SmallBoxDimension; i++ )
    {
    myA[i] = new int [SmallBoxDimension];
    myB[i] = new int [SmallBoxDimension];
    myC[i] = new int [SmallBoxDimension];
    }



    

    genZeroes(myC, (int)sqrt(subMatrixSize) );



//
    
    int left = getIdLeft(myRank, numProcessors);
    int right = getIdLeft(myRank, numProcessors);
    int down = getIdDown(myRank, numProcessors);
    int up = getIdUp(myRank, numProcessors);

//////////////////////////////////////////////////////////////////////////////////////////////
    // Initial shift (Shift Amount is made by task id % sqrtNumP)

MPI_Barrier(MPI_COMM_WORLD);


initShift( myRank, numProcessors, left, up, right, down, subMatrixSize, (int)sqrt(numProcessors), arrayA, arrayB);

//////////////////////////////////////////////////////////////////////////////////////////////

//    Loop for the rest of the multiplication


for( loopAmnt = 0; loopAmnt < (int)sqrt(numProcessors); loopAmnt++ )
    {
        

//    CONVERT 2D ARAYS
    int offset = (int)sqrt(subMatrixSize);
    int offsetTimesY; 
    

    for( int i = 0; i < (int)sqrt(subMatrixSize); i++)
    {
        for( int j = 0; j < (int)sqrt(subMatrixSize); j++)
            {
                offsetTimesY = j * offset;

		


                //Add offset * y to the lenggth
                myA[i][j] = arrayA[ offsetTimesY + i];
                myB[i][j] = arrayB[ offsetTimesY + i];

            }
    }
    
    

    for( int i = 0; i < (int)sqrt(subMatrixSize); i++ )
        {
            for( int j = 0; j < (int)sqrt(subMatrixSize); j++ )
            {
        
            }
    
        }


    for( int i = 0; i < (int)sqrt(subMatrixSize); i++ )
        {
            for( int j = 0; j < (int)sqrt(subMatrixSize); j++ )
            {
        
            }
    
        }
    // Optimize Vars Later
    // MULTIPLY THE NUMBERS

    int loopLength = (int)sqrt(subMatrixSize);



    
    for (int i = 0; i < loopLength; i++)
    {
        for (int j = 0; j < loopLength; j++)
        {
            for (int k = 0; k < loopLength; k++)
            {
                myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j];
               /
            }
        }
        
    }
    

    

    // Put into 1D array for passing
    for( int i = 0; i < subMatrixSize/(int)sqrt(subMatrixSize); i++)
    {
        for( int j = 0; j < subMatrixSize/(int)sqrt(subMatrixSize); j++)
            {
                for( int k = 0; k < subMatrixSize; k++ )
                    {
                        arrayA[k] = myA[i][j];
                        arrayB[k] = myB[i][j];
                    }
            }
    }


    
//////////////////////////////////////////////////////////////////////////////////////////////
    // Do final shift (Shift Amount is made by task id % sqrtNumP)
        shiftLeft( arrayA, subMatrixSize, taskId, numProcessors );
        shiftUp( arrayB, subMatrixSize, taskId, numProcessors );

        MPI_Barrier(MPI_COMM_WORLD);
//////////////////////////////////////////////////////////////////////////////////////////////

    }



MPI_Barrier(MPI_COMM_WORLD);

    FILE *outSlave;




    outSlave = fopen("Output.txt","a+");


    for( int count = 0; count < numProcessors; count++ )
    {
	
    	if( count == myRank )
    	{


   		 for( int i = 0; i < (int)sqrt(subMatrixSize); i++)
        	{
            for( int j = 0; j < (int)sqrt(subMatrixSize); j++)
                {
                  
                }
          
       		}
    	}
	MPI_Barrier(MPI_COMM_WORLD);
    }

    
    }

void initShift(int myrank, int numCores, int left, int up, int right, int down, int size, int root, int* dataA, int* dataB)
{

    int indexCol = (myrank % root);
    int indexRow = (myrank/root);
    int count;

    for(count = 0; count < indexRow; count++)
    {
        shiftLeft( dataA, size, myrank, numCores );
    }

    for(count = 0; count < indexCol; count++)
    {
        shiftUp( dataB, size, myrank, numCores );
    }
}

void shiftLeft( int *matA, int size, int myProcessor, int numProcessors )
    {
    int destProcessor;
    int recvProcessor;
    MPI_Status status;


    destProcessor = getIdLeft( myProcessor, numProcessors );
    recvProcessor = getIdRight( myProcessor, numProcessors );


    
    MPI_Sendrecv_replace(matA, size, MPI_INT, destProcessor, M_A_DATA, recvProcessor, M_A_DATA, MPI_COMM_WORLD, &status);
    
    }

void shiftUp( int *matB, int size, int myProcessor, int numProcessors )
    {
    int destProcessor;
    int recvProcessor;
    MPI_Status status;

    destProcessor = getIdUp( myProcessor, numProcessors );
    recvProcessor = getIdDown( myProcessor, numProcessors );



    
    MPI_Sendrecv_replace(matB, size, MPI_INT, destProcessor, M_B_DATA, recvProcessor, M_B_DATA, MPI_COMM_WORLD, &status);
    
    }

int getIdUp( int myProcessor, int numProcessors )
    {
    int idAboveMe;

    if(( myProcessor < (int)sqrt(numProcessors)))
        {
            idAboveMe = myProcessor + (numProcessors - (int)sqrt(numProcessors));
        }

    else{

        idAboveMe = myProcessor - (int)sqrt(numProcessors);
    }

    return idAboveMe;
    }


int getIdDown( int myProcessor, int numProcessors )
    {
    int idBelowMe;

    if( myProcessor < ( numProcessors - (int)sqrt(numProcessors)) )
        {
            idBelowMe = myProcessor + (int)sqrt(numProcessors);


        }
    else{

        idBelowMe = myProcessor % (int)sqrt(numProcessors);
    }

    return idBelowMe;
    }

int getIdLeft( int myProcessor, int numProcessors )
    {
    int idToMyLeft;

    if(( myProcessor % (int)sqrt(numProcessors)) == 0 )
        {
            idToMyLeft = myProcessor + ((int)sqrt(numProcessors) - 1);
        }

    else{

        idToMyLeft = myProcessor - 1;

        }

    return idToMyLeft;
    }

int getIdRight( int myProcessor, int numProcessors )
    {
    int idToMyRight;

    if( (myProcessor % (int)sqrt(numProcessors)) >= ((int)sqrt(numProcessors) - 1) )
        {
            idToMyRight = myProcessor - ( (int)sqrt(numProcessors) - 1 );
        }

    else{
        idToMyRight = myProcessor + 1;
        
    }
    return idToMyRight;
    }

void genNumbers( int *arrayA, int *arrayB, int *arrayC, int sizeN, int argc, char **argv )
    {

	ifstream fin;
	


	if( argc < 3 )
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
	else{
	
	fin.clear();
	fin.open(argv[2]);
	int number;

    for( int index = 0; index < (sizeN * sizeN); index++ )
        {
		fin >> number;
            //srand(time(NULL));
                //srand(time(NULL));
                 arrayA[index] = number;
                 // Set array C to 0 (For proper calculations)
                 arrayC[index] = 0;
        }
	fin.close();

	// Open second file though this is very unoptimized... NOT RECOMMENDED FOR EVERY DAY USE

	fin.clear();
	fin.open(argv[3]);

    for( int index = 0; index < (sizeN * sizeN); index++ )
        {
		fin >> number;
            //srand(time(NULL));
                //srand(time(NULL));
                 arrayB[index] = number;
                 // Set array C to 0 (For proper calculations)
        }
	fin.close();

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



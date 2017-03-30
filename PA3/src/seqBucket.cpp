#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <mpi.h>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#define master = 0;

/* Constants */

/* Com Tags*/
const int DATA_TAG = 1;
const int DATA_FINISHED_TAG = 2;
const int FINISHED_TAG = 3;

/*Vars*/


/* Function Prototypes */

/*
 * Name: bucketSort
 * In: Array to be sorted(int*), Size of array (int)
 * Out: Sorted Array, No Return value
 * Function: Sorts an array using bucket sort algorithm
 * Notes: None 
 */
void bucketSort(int* array, int size);


/*
 * Name: main
 * In: size of image (WidthXHeight)
 * Out: returns 0
 * Function: inits MPI and gives Master and the slaves their code to execute
 * Notes: None 
 */
int main(int argc, char* argv[])
{	
    int size = 0;
    int index = 0;
    int* array;
    char comma;
    double start, finished, dt;
    string filename;
    ifstream fin;
    ofstream fout;

    if(argc == 1)
    {
         filename = "nums.txt";
    }
    else
    {
         filename = argv[1];
    }

    fout.clear();
    fout.open("../TestData/SerialTimingData", ios::out | ios::app);
    fin.clear();
    fin.open(filename.c_str());
    if(fin.good())
    {
        fin >> size;
        array = new int[size];
        if(array == NULL)
        {
            cout << endl <<  "Array Failed To Init." << endl;
            return 1;
        }
        while(!fin.eof() && index < size)
        {
            fin >> comma;
            fin >> array[index];
            index++;
        }
        cout << endl << "config file loaded" << endl << endl;

        // start MPI (For Timer)
    	MPI_Init( &argc, &argv );
        // start timer
        start = MPI_Wtime();
        
        // sort array        
        bucketSort (array, size);

        // stop timer
        finished = MPI_Wtime();

        //get dt;
        dt = (finished - start);
        //output dt
        fout <<"Time: " << dt << "\tSize: " << size << endl;
        cout << "Time: " << dt << "\tSize: " << size << endl;
        
        // output array to screen
        cout << endl << "Sorted Array: ";	
        for (index = 0; index < size; index++)
        {
            cout << array[index] << " ";	
        }
        cout << endl << endl;
    	// finialize mpi stuff
	    MPI_Finalize();
    }
    else
    {
        cout << endl << "Could Not Load File" << endl;
    }
return 0;
}


/*
 * Name: bucketSort
 * In: Array to be sorted(int*), Size of array (int)
 * Out: Sorted Array, No Return value
 * Function: Sorts an array using bucket sort algorithm
 * Notes: None 
 */
void bucketSort(int array[], int size)
{
    // set range for 0 to 100
    int range = 101;
    int index, bucketNum;
    //Create empty buckets equal to size of range
    int buckets[range];

    //Init. all buckets to 0
    for (index = 0; index < range; index++)
    {
        buckets[index] = 0;
    } 

    //count occurrence of each number found in array
    for (index = 0; index < size; index++)
    {
        buckets[array[index]]++;
    }

    //Sort using insertion sort and concatenate 
    
    for (index = 0, bucketNum = 0; bucketNum < range; bucketNum++)
    {
        for (int count = buckets[bucketNum]; count > 0; count--)
        {     
            array[index++] = bucketNum;
        }
    }
}



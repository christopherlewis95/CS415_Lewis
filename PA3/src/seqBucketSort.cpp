// C++ program to sort an array using bucket sort
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <mpi.h>
#include <time.h> 


#include <iostream>

using namespace std;
 
//void bucketSort(int arr[], int n);
void bucketSort(int *array, int size,int a, int b, char **argv);
void readIn( string fileName, int *arr );
void genNumbers( int *genArray, int size );

/* Driver program to test above funtion */
//This is a C++ Program to Sort an Array using Bucket Sort
 
//Bucket Sort
#define NOBUCKETS 10
#define BIGGEST 100000

 
 
//Driver function to test above function
int main(int argc, char** argv)
{	
      int rank;
    int numProcessors;
    MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );
    clock_t clockTicks;
    clock_t t0;

    cout << "Before the gen" << endl;
    cout << "After the Gen" << endl;
    int i;  
    vector<int> vec;
    //////////////////////////////////////////////////////////////
    int *arr;
    string fileName = "data.txt";
    ifstream fin;
    int size, num;
    int index = 0;
    double start, finished, dt;
    int amount = atoi(argv[1]);

//    arr = new int [size];

      int *input_ar = new int[amount];
      genNumbers( input_ar, amount );

   // cout << *arr << endl;

  int n = sizeof (input_ar) / sizeof (input_ar[0]);

  //cout << "ENTERING" << endl;
  bucketSort(input_ar, size, 0, BIGGEST, argv);

  //clockTicks = clock() - t0;
 //cout << "EXITING" << endl;
 //for( i = 0; i < size; i++)

  //dt = (finished - start);

  
  ///////////////////////////////////////////////////////////////////////////////////////




  ///////////////////////////////////////////////////////////////////////////////////////



  //cout << "Sorted Array : " << endl;	
 // for (int i = 0; i < n; ++i)
//    cout << input_ar[i] << " ";	
 
  //  cout << endl << endl;

	// MPI_Finalize();
  return 0;
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

/*
// Function to sort arr[] of size n using bucket sort
//Bucket Sort
void bucketSort(int arr[], int n)
{
  //Here range is [1,100]
  int m = 1001;
 
  //Create m empty buckets
  int buckets[m];
 
  //Intialize all buckets to 0
  for (int i = 0; i < m; ++i)
    buckets[i] = 0;
 
  //Increment the number of times each element is present in the input
  //array. Insert them in the buckets
  for (int i = 0; i < n; ++i)
    ++buckets[arr[i]];
 
  //Sort using insertion sort and concatenate 
  for (int i = 0, j = 0; j < m; ++j)
    for (int k = buckets[j]; k > 0; --k)
      arr[i++] = j;
}
*/
void bucketSort(int *array, int size,int a, int b, char **argv){
    clock_t clockTicks;
    clock_t t0;
	//--Declare variables
	vector<int> buckets[NOBUCKETS];
	int bi;
	double generationTime, sortTime;
	  t0 = clock();
//	generateArray(array, size, a, b);
	generationTime = clock() - t0;

	//printArray(array, size);

	t0 = clock();
	int range = (b - a) / NOBUCKETS;

	//--Put array elements in different buckets
	for (int i = 0; i < size; i++){
		bi = (array[i] - a) / (range + 1); // Index in bucket
		buckets[bi].push_back(array[i]);
	}

	//--Sort individual buckets
	for (int i = 0; i < NOBUCKETS; i++)
	   sort(buckets[i].begin(), buckets[i].end());

	//--Concatenate all buckets into arr[]
	int index = 0;
	for (int i = 0; i < NOBUCKETS; i++)
		for (int j = 0; j < buckets[i].size(); j++)
		  array[index++] = buckets[i][j];
	sortTime = clock() - t0;
	//printArray(array, size);


  FILE *fp;

  fp = fopen(argv[2],"a+");
  fprintf(fp, "%d, %f\n", atoi(argv[1]), (float)sortTime/CLOCKS_PER_SEC);

  fclose(fp);

}

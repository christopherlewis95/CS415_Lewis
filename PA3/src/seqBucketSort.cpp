// C++ program to sort an array using bucket sort
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <mpi.h>
#include <time.h> 

using namespace std;
 
void bucketSort(int *arr, int n);
void readIn( string fileName, int *arr );
void genNumbers( int numbers );

/* Driver program to test above funtion */
//This is a C++ Program to Sort an Array using Bucket Sort
#include <iostream>
using namespace std;
 
//Bucket Sort

 
 
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
    genNumbers( atoi(argv[1]) );
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

    fin.open( fileName.c_str() );

    fin >> size; 
    cout << size << endl;
//    arr = new int [size];
      int *input_ar = new int[size];


    while( !fin.eof() )
        {
            fin >> num;
            input_ar[index] = num;
           cout << input_ar[index] << endl;
            index++;
        }
   // cout << *arr << endl;
    fin.close();

  int n = sizeof (input_ar) / sizeof (input_ar[0]);
  t0 = clock();
  //cout << "ENTERING" << endl;
  bucketSort (input_ar, 10);

  clockTicks = clock() - t0;
 //cout << "EXITING" << endl;
 //for( i = 0; i < size; i++)

  //dt = (finished - start);

  
  ///////////////////////////////////////////////////////////////////////////////////////


  FILE *fp;

  fp = fopen(argv[2],"a+");
  fprintf(fp, "%d, %f\n", atoi(argv[1]), (float)clockTicks/CLOCKS_PER_SEC);

  fclose(fp);


  ///////////////////////////////////////////////////////////////////////////////////////



  //cout << "Sorted Array : " << endl;	
 // for (int i = 0; i < n; ++i)
//    cout << input_ar[i] << " ";	
 
  //  cout << endl << endl;

	// MPI_Finalize();
  return 0;
}

void genNumbers( int numbers )
{
    FILE *fp;
    int num = 0;
    int size = numbers;

    fp = fopen("data.txt", "w");

    fprintf(fp, "%d\n", size );
    for(int i = 0; i < size; i++)
    {
        num = rand() % 1000;
        fprintf(fp, "%d\n", num );
    }
    fclose(fp);
}

// Function to sort arr[] of size n using bucket sort
void bucketSort(int *arr, int n)
{
    // 1) Create n empty buckets
    vector<float> b[n];
    
    // 2) Put array elements in different buckets
    for (int i=0; i<n; i++)
    {
       int bi = n*arr[i]; // Index in bucket
       b[bi].push_back(arr[i]);
    }
 
    // 3) Sort individual buckets
    for (int i=0; i<n; i++)
       sort(b[i].begin(), b[i].end());
 
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
          arr[index++] = b[i][j];
}
}
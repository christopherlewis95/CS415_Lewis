// C++ program to sort an array using bucket sort
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
//#include <mpi.h>
#include <time.h> 

using namespace std;
 
void bucket_sort (int *arr, int n);
void readIn( string fileName, int *arr );


/* Driver program to test above funtion */
//This is a C++ Program to Sort an Array using Bucket Sort
#include <iostream>
using namespace std;
 
//Bucket Sort

 
 
//Driver function to test above function
int main(int argc, char** argv)
{	
    clock_t clockTicks;
    clock_t t0;

    


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
      int *input_ar = new int [size];


    while( !fin.eof() )
        {
            fin >> num;
            input_ar[index] = num;
           // cout << input_ar[index] << endl;
            index++;
        }
   // cout << *arr << endl;
    fin.close();

  int n = sizeof (input_ar) / sizeof (input_ar[0]);

  t0 = clock();
  //cout << "ENTERING" << endl;
  bucket_sort (input_ar, n);

  clockTicks = clock() - t0;
 //cout << "EXITING" << endl;

  //dt = (finished - start);

  
  ///////////////////////////////////////////////////////////////////////////////////////


  FILE *fp;

  fp = fopen("bucketSrtData.txt","a+");
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

void bucket_sort (int *arr, int n)
{
  //Here range is [1,500]
  int m = 501;
 
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
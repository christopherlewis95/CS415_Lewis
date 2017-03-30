// C++ program to sort an array using bucket sort
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
 
void bucket_sort (int arr[], int n);
void readIn( string fileName, int *arr );


/* Driver program to test above funtion */
//This is a C++ Program to Sort an Array using Bucket Sort
#include <iostream>
using namespace std;
 
//Bucket Sort

 
 
//Driver function to test above function
int main(int argc, char** argv)
{	
   // MPI_Init( &argc, &argv );

    int i;  
    vector<int> vec;
    //////////////////////////////////////////////////////////////
    int *arr;
    string fileName = "nums.txt";
    ifstream fin;
    int size, num;
    int index = 0;
    double start, finished, dt;

    fin.open( fileName );

    fin >> size; 
    cout << size << endl;
//    arr = new int [size];
      int input_ar[size];


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

  start = MPI_Wtime();
  //cout << "ENTERING" << endl;
  bucket_sort (input_ar, n);

  finished = MPI_Wtime();
 //cout << "EXITING" << endl;

  dt = (finished - start);

  
  ///////////////////////////////////////////////////////////////////////////////////////


  FILE *fp;

  fp = fopen("bucketSrtData.txt","a+");
  fprintf(fp, "%f\n", dt);

  fclose(fp);


  ///////////////////////////////////////////////////////////////////////////////////////



  //cout << "Sorted Array : " << endl;	
 // for (int i = 0; i < n; ++i)
//    cout << input_ar[i] << " ";	
 
  //  cout << endl << endl;

	  //  MPI_Finalize();
  return 0;
}

void bucket_sort (int arr[], int n)
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
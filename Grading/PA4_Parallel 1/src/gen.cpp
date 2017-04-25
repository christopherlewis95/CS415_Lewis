#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;
//generates random matrices, specify how big with first commmandline argument and the name of the output file with the second

int main(int argc, char* argv[])
{
    char tab = '\t';
    ofstream file;
    char* filename = argv[2];
    file.open(filename);

    int test = atoi(argv[1]);
    //dynamically allocate the array
    int** array = new int*[test];
    for(int i = 0; i < test; i++)
        array[i] = new int[test];


    int rows,columns;
    int t,j;
    srand(time(NULL));
    //file<<tab;
    //filling the matrix with random values, I keep them in the range of te size of the matrix just to keep variety in the numbers, but also keep them  close
    for(rows=0;rows<test;rows++) 
    {

        for(columns=0;columns<test;columns++)
        {
            array[rows][columns] = rand() % atoi(argv[1]);
            file<<array[rows][columns]<<tab;
        }
        file<<endl;
    }
    return 0;
}

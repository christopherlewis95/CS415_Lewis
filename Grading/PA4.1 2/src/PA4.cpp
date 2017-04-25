/*I know that this project is incompleate. I have been sick the last three days and have not been able to sit for more than an hour without throwing up.
I wanted to turn this in so that I could get points in the future.*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "mpi.h"
#include <string>
#include <time.h>
#include <math.h>


using namespace std;
//global vars
int **bigA, **bigB, *A, *B, **C, bigSize, size, numTasks, taskID, loc[2], sqrtNumTasks, passLeftTo, recvFromRight, passUpTo, recvFromDown;
MPI_Status status;
//a function that generates matricies
void generateMatrix(int **matrix, int seed){
	int index, innerIndex;
	srand(seed);
	for(index = 0; index < size; index++){
		for(innerIndex = 0; innerIndex < size; innerIndex++){
			matrix[index][innerIndex] = rand() % 21 + (-10);
		}
	}
}
//a function that will read from a file and populate a matrix
void populateMatrix(int **mat, char *filename){

}
//matrix multiplication
void multiplyMatricies(){
	int index, columnIndex, rowIndex;
	for(index =0; index < size; index++){
		for(columnIndex = 0; columnIndex < size; columnIndex++){
			for(rowIndex = 0; rowIndex < size; rowIndex++){
				C[index][columnIndex] += A[index * size + rowIndex] * B[rowIndex + (size * columnIndex)];
			}
		}
	} 
}
//print matrix to file
void displayMatrix(int **matrix, int size, ofstream &fout){
	int index, innerIndex;
	for(index = 0; index < size; index++){
		for(innerIndex = 0; innerIndex < size; innerIndex++){
			fout << matrix[index][innerIndex] << "\t";
		}
		fout << endl;
	}
}
//pass sub matrix left and recv from right.
void passLeft(){
	
	if(loc[1]%2 == 0){
		MPI_Send(A, (size*size), MPI_INT, passleftTo, 2, MPI_COMM_WORLD);
		MPI_Recv(A, (size*size), MPI_INT, recvFromRight, 2, MPI_COMM_WORLD);

	}
	else{
		MPI_Recv(A, (size*size), MPI_INT, recvFromRight, 2, MPI_COMM_WORLD);
		MPI_Send(A, (size*size), MPI_INT, passleftTo, 2, MPI_COMM_WORLD);
	}
}
//pass sub matrix up routine
void passUp(){

}
//calculate row neighbors.
void calculateLeft(){
	if(loc[1] == 0){
		passLeftTo = (loc[0] * sqrtNumTasks)+(numTasks-1)%numTasks;
	}
	else{
		passLeftTo = (loc[0] * sqrtNumTasks) + loc[1] - 1;
	}
	if(loc[1] + 1 > (numTasks-1)%numTasks){
		recvFrom = (loc[0] * sqrtNumTasks);
	}
	else{
		recvFrom = (loc[0] * sqrtNumTasks)+loc[1] + 1;
	}
}
//calculate column neighbors
void calculateUp(){
	if(loc[0] == 0){
		passUpTo = (loc[1] * sqrtNumTasks)+(numTasks-1)/numTasks;
	}
	else{
		passUpTo = 
	}
}
//send matrix to slave.
void assignMatrix(){
	int dataA[size * size], dataB[size * size], index, rowIndex, columnIndex;
	if(taskID == 0){
		for(index = 0; index < numTasks-1; index++){
			for(rowIndex = (bigSize/sqrtNumTasks)*(index/sqrtNumTasks); rowIndex < (bigSize/sqrtNumTasks)*((index+1)/sqrtNumTasks); rowIndex++){
				for(columnIndex = (bigSize/sqrtNumTasks)*(index%sqrtNumTasks); columnIndex < (bigSize/sqrtNumTasks)*((index+1)%sqrtNumTasks); columnIndex++){
					if(index == 0){
						A[(rowIndex*size)+columnIndex] = bigA[rowIndex][columnIndex];
						B[(rowIndex*size)+columnIndex] = bigB[rowIndex][columnIndex];
					}
					else{
						dataA[(rowIndex*size)+columnIndex] = bigA[rowIndex][columnIndex];
						dataB[(rowIndex*size)+columnIndex] = bigB[rowIndex][columnIndex];
					}
				}
			}
			if(index != 0){
				MPI_Send(dataA, (size*size), MPI_INT, index, 1, MPI_COMM_WORLD);
				MPI_Send(dataB, (size*size), MPI_INT, index, 1, MPI_COMM_WORLD);	
			}			
		}
	}
	else{
		MPI_Recv(A, (size*size), MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(B, (size*size), MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
	}
}
//initilize cannons algorithm.
void matItit(){
	int index;
	for(index = 0; index < loc[0]; index++){
		passLeft();
	}
	for (index = 0; index < loc[1]; index++)
	{
		passUp();
	}
}
//main.
int main(int argc, char *argv[]){
	MPI_Init(&argc,&argv);
	int  index, innerIndex, seed =0, print;
	string input, outputFile;
	double startTime, endTime;
	ofstream fout;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&numTasks);
	MPI_Comm_rank(MPI_COMM_WORLD,&taskID);
	if(taskID == 0){
		input = argv[1];
		outputFile = "../bin/";
		outputFile += argv[1];
		bigSize = stol(input);
		outputFile += "x";
		outputFile += to_string(numTasks);
		input = argv[2];
		print = stoi(input);
		if(print)
			outputFile += "-WithPrint";
		outputFile += ".out";
		
		bigA = new int*[bigSize];
		bigB = new int*[bigSize];
		for(index = 0; index < size; index++){
			bigA[index] = new int[bigSize];
			bigB[index] = new int[bigSize];
		}
		generateMatrix(bigA, seed);
		generateMatrix(bigB, seed+100);
		size = bigSize/numTasks;
	}
	sqrtNumTasks = sqrt(numTasks);
	loc[0] = taskID / sqrtNumTasks;
	loc[1] = taskID % sqrtNumTasks;
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	A = new int[size * size];
	B = new int[size * size];
	C = new int*[size];
	for(index = 0; index < size; index++){
		C[index] = new int[size];
		for(innerIndex = 0; innerIndex < size; innerIndex++){
			C[index][innerIndex] = 0;	
		}
	}
	assignMatrix();
	if(taskID == 0)
		startTime = MPI_Wtime();
	matItit();
	for(index = 0; index < sqrtNumTasks; index++){
		passLeft();
		passUp();
		multiplyMatricies();
	}
	//multiplyMatricies(A,B,C,size);
	endTime = MPI_Wtime();
	/*if(taskID == 0){
		if(print)
			fout.open(outputFile.c_str());
		else
			fout.open(outputFile.c_str(),ofstream::out | ofstream::app);
		fout.precision(17);
		fout << "Time: " << (endTime - startTime) << endl;
		if(print){
			displayMatrix(A,size,fout);
			fout << "\n\n" << endl;
			displayMatrix(B,size,fout);
			fout << "\n\n" << endl;
			displayMatrix(C,size,fout);
		}
		fout.close();
	}*/
	

	MPI_Finalize();
}

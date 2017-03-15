#include <iostream>
#include <mpi.h>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;


// tags and const that are important to the project 
#define TERMINATE_TAG 0
#define DATA_TAG 1
#define RESULT_TAG 2

// complex struct
struct complex {
	float real;
	float imag;
};

// function prototype for calculation
int cal_pixel( complex );


// main function
int main( int argc, char **argv ) {
    // initialize variables
	int rank;
	int display_width = atoi(argv[1]);
    int display_height = atoi(argv[2]);
    int **coords = new int *[display_height];	
    
    for( int i = 0; i < display_height; i++ )
    {
        coords[i] = new int[display_width];
    }
    
    int real_min = -2;
    int real_max = 2;
    int imag_min = -2;
    int imag_max = 2;
    int terminate_var = 0;
	int numProcessors;
	float scale_real = (float) ( real_max - real_min ) / display_width;
	float scale_imag = (float) ( imag_max - imag_min ) / display_height;
     clock_t clockTicks;
    clockTicks = clock();
    clock_t t0;
    clockTicks = clock() - clockTicks; // Time elapsed since I did the last initial clock



    FILE *fp;

    fp = fopen("TimesDynamic.txt", "a+");



	// get rank to distinguish processors 
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &numProcessors );
    cout << display_height << " and " << display_width << " WITH " << numProcessors << endl;

	if( rank == 0 ) // Master
    { 
	    MPI_Status status;
	    int row = 0;
	
	    int row_colors[display_width + 1];	

	    // output image is placed into this file
	    ofstream fout;
	    fout.open( "dynImage.ppm" );

        t0 = clock();
	    // send row number to all available processors without sending to the master BAD
	    for( int i = 1; i < numProcessors; i++ ) 
            {
		    MPI_Send( &row, 1, MPI_INT, i, DATA_TAG, MPI_COMM_WORLD );	
		    row++;
	        }
	
	    int rowsAnalyzed = 0;

        // Send work to keep things going
	    while( rowsAnalyzed < display_height ) 
            {
			MPI_Recv( &row_colors, display_width + 1, MPI_INT, MPI_ANY_SOURCE, RESULT_TAG, MPI_COMM_WORLD, &status );
            int pingPongSend = status.MPI_SOURCE;
			int receivedRow = row_colors[0];
				
			for( int col = 0; col < display_width; col++ ) 
                {
				coords[receivedRow][col] = row_colors[col+1];
				}
				
			rowsAnalyzed++;
			if( row < display_height ) 
                {
				MPI_Send( &row, 1, MPI_INT, pingPongSend, DATA_TAG, MPI_COMM_WORLD );
				row++;
				}

			}
 
		for( int i = 1; i < numProcessors; i++ ) {
			MPI_Send( 0, 0, MPI_INT, i, TERMINATE_TAG, MPI_COMM_WORLD );
			}
		
		// get elapsed time and print to file
        clockTicks = clock() - t0;
        fprintf(fp, "%f\n", (float)clockTicks/CLOCKS_PER_SEC);

		// print mandelbrot set to the file using fout (Mainly cause its easier)
		for( int x = 0; x < display_width; x++ ) 
            {
			for( int y = 0; y < display_height; y++ ) 
            {
				fout << coords[x][y] << " ";
			}
			fout << endl;		
		}

		fout.close();
	}

	else { 	
        MPI_Status status;
        // Init more vars
	    complex c;
	    int colorD[display_width + 1];
	    int row = 0; 

	    int slaveNum;

	    MPI_Comm_rank( MPI_COMM_WORLD, &slaveNum );

	    MPI_Recv( &row, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status );

	    while( status.MPI_TAG == DATA_TAG )	
        {

		// check for terminate tag to exit process
		if( status.MPI_TAG == TERMINATE_TAG ) {
			exit(0);				
		}	
		
		colorD[0] = row;
		c.imag = imag_min + ( (float) row * scale_imag );
		for( int x = 0; x < display_width; x++ ) 
			{
				// do column calculation using cal pixel
				c.real = real_min + ( (float) x * scale_real );
				colorD[x+1] = cal_pixel( c );		
			}
	
		// now that a row is computed, send the colors and the row back to master
		MPI_Send( colorD, display_width + 1, MPI_INT, 0, RESULT_TAG, MPI_COMM_WORLD );
		MPI_Recv( &row, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status );

	    }
	}
    fclose(fp);

    // Delete pointers and set to NULL
    delete coords;
    coords = NULL;

    // ALWAYS MPI FINALIZE
	MPI_Finalize();
	return 0;
}

/////////////// THIS IS FOR THE INCLUDED FUNCTION ////////////

int cal_pixel( complex c) {

	int count, max_iter;
   complex z;
	float temp, lengthsq;
	max_iter = 256;
	z.real = 0.0;
	z.imag = 0.0;
 	count = 0;
	do {
			temp = z.real * z.real - z.imag * z.imag + c.real;
      	z.imag = 2 * z.real * z.imag + c.imag;
		   z.real = temp;
			lengthsq = z.real * z.real + z.imag * z.imag;
			count++;
	} while( ( lengthsq < 4.0 ) && ( count < max_iter ) );


	return count;
}

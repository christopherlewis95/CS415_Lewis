/******************************************************************************
* FILE: mpi_hello.c
* DESCRIPTION:
*   MPI tutorial example code: Simple hello world program
* AUTHOR: Blaise Barney
* LAST REVISED: 03/05/10
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0

int main (int argc, char *argv[])
{
int   numtasks, taskid, len;
char hostname[MPI_MAX_PROCESSOR_NAME];

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Get_processor_name(hostname, &len);
printf ("Hello from task %d on %s!\n", taskid, hostname);

    // Initialize complex number struct
    complex c;
    c.real = 0;
    c.imag = 0;
    double start, finish, writeout, delta;
    int x, y;
    FILE *fp;
    clock_t clockTicks;
    clockTicks = clock();
    clock_t t0;
    clockTicks = clock() - clockTicks; // Time elapsed since I did the last initial clock
    int i, row;


    bool good;
    char fileName[] = "imageStatic.ppm";

   
    double scale_real, scale_imag, real_max, real_min, imag_max, imag_min;
    //unsigned char ** pix = new unsigned char *[display_height];
    unsigned char **r;
    unsigned char **g;
    unsigned char **b;


    int display_width = atoi(argv[1]);
    int display_height = atoi(argv[2]);

    fp = fopen("staticAssManData.txt","a+");

    r = new unsigned char *[display_height];
    g = new unsigned char *[display_height];
    b = new unsigned char *[display_height];

    for( int i = 0; i < display_height; i++ )
    {
        r[i] = new unsigned char[display_width];
        g[i] = new unsigned char[display_width];
        b[i] = new unsigned char[display_width];

    }


    real_min = -2;
    real_max = 1;
    
    imag_min = -1.2;
    imag_max = imag_min + (real_max-real_min)*display_height/display_width;
    
    // Set scale;
    scale_real = (real_max - real_min)/display_width;
    scale_imag = (imag_max - imag_min)/display_height;

if (taskid == MASTER)
    {
       // printf("MASTER: Number of MPI tasks is: %d\n",numtasks);
       for( i = 0, row = 0; i < display_height/10; i++, row = row + 10  )
        {
         MPI_Send(&row, 1, MPI_INT, i, 0, MPI_COMM_WORLD);   
           
        }
        for( i = 0; i < (display_height*display_width); i++ )
        {
            // r[0] is red coords
            MPI_Recv(&r,display_width, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status)
           // MPI_Recv(&colors[0] , X_RESN , MPI_INT, MPI_ANY_SOURCE, RESULT_TAG, MPI_COMM_WORLD, &status);
           pim_write_color(fileName, 
                display_width, 
                display_height,
                (const unsigned char **)r,
                (const unsigned char **)g, 
                (const unsigned char **)b
                );
        }

    }
else if( taskid == i ){
    MPI_Recv(&row, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);

    for( x = 0; x < disp_width; x++)
    {
        for( y = row; y < (row + 10); y++ )
        {
            c.real = real_min + ((float)x * scale_real);
            c.imag = imag_min + ((float)y * scale_imag);
            //static int n = cal_pixel(c);
            r[y][x] = cal_pixel(c);
            g[y][x] = 0;
            b[y][x] = 0;

            MPI_Send(&r, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD )

        }


    }


   // printf("CHILD: Number of MPI tasks is: %d\n",numtasks);

}



MPI_Finalize();

}


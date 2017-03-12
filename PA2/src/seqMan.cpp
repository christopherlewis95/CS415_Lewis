#include <math.h>
//#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "../include/pimfunctions.h"

using namespace std;

struct complex{

    float real;
    float imag;

};

int cal_pixel(complex c);


int main()
    {
    // Initialize complex number struct
    complex c;
    
    bool good;
   const char * const fileName = "newimage.ppm";

    int display_width = 680;
    int display_height = 480;
    int scale_real, scale_imag, real_max, real_min, imag_max, imag_min;
    //unsigned char ** pix = new unsigned char *[display_height];
    unsigned char **r;
    unsigned char **g;
    unsigned char **b;

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
    real_max = 2;
    
    imag_min = -1;
    imag_max = imag_min + (real_max-real_min)*display_height/display_width;
    
    // Set scale;
    scale_real = (real_max - real_min)/display_width;
    scale_imag = (imag_max - imag_min)/display_height;
    



    for( int y = 0; y < display_height; y++ )
    {

        for( int x = 0; x < display_width; x++ )
            {
            c.real = real_min + ((float)x * scale_real);
            c.imag = imag_min + ((float)y * scale_imag);
            static int n = cal_pixel(c);
            r[y][x] = cal_pixel(c);
            g[y][x] = 0;
            b[y][x] = 0;


            }


    }
 pim_write_color(fileName, 
                display_width, 
                display_height,
                (const unsigned char **)r,
                (const unsigned char **)g, 
                (const unsigned char **)b
                );



    
    return 0;
    }

//// FUNCTIONS

int cal_pixel(complex c)
{
    int count, maxIter;
    complex z;
    float temp, lengthSq;


    maxIter = 256;
    z.real = 0;
    z.imag = 0;
    count = 0;
    do{
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        lengthSq = z.real * z.real+z.imag*z.imag;
        count++;
    }while( (lengthSq < 4.0) && (count < maxIter) );

    return count;
}


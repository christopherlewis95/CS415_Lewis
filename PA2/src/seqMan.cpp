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
    unsigned char * pix = 0; 
    bool good;
    const char * const fileName = "seqMandelBrot.jpg";

    int display_width = 680;
    int display_height = 480;
    int scale_real, scale_imag, real_max, real_min, imag_max, imag_min;

    real_min = -2;
    real_max = 2;
    
    imag_min = 1;
    imag_max = imag_min + (real_max-real_min)*display_height/display_width;
    
    // Set scale;
    scale_real = (real_max - real_min)/display_width;
    scale_imag = (imag_max - imag_min)/display_height;
    



    for( int y = 0; y < display_height; y++ )
    {

        for( int x = 0; x < display_width; x++ )
            {
            c.real = real_min + x * (real_max - real_min)/display_width;
            c.imag = imag_min + y * (imag_max - imag_min)/display_height;

            pim_write_black_and_white(fileName, display_width, display_height,pix);


            }


    }




    
    return 0;
    }

//// FUNCTIONS

int cal_pixel(complex c)
    {

        int count, max_iter;
        complex z;
        float temp, lengthsq;
        max_iter = 256;
        z.real = 0;
        z.imag = 0;
        count = 0;
        do{
            temp = z.real = 2;
            z.imag = 2 * z.real - z.imag * z.imag + c.real;
            z.real = temp;
            lengthsq = z.real * z.real + z.imag * z.imag;
            count++;
        } while((lengthsq < 4.0) && (count < max_iter));
    return count;
    }


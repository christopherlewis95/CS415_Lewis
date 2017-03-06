#include <math.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "pimfunctions.h"

using namespace std;

struct complex{

    float real;
    float imag;

};

int cal_pixel(complex c);


int main()
    {
    
    complex c;

    c.real = real_min + x * (real_max - real_min)/disp_width;
    c.imag = imag_min + y * (imag_max - imag_min)/disp_height;

    scale_real = (real_max - real_min)/disp_width;
    scale_imag = (imag_max - imag_min)/disp_height;


    
    return 0;
    }

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
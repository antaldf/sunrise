/*
Copyright (c) 2016 Dave Antal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


/*
 * File:   sunrise.c
 * Author: dantal
 *
 * Created on November 9, 2016, 8:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "pigpiod_if2.h"
#include "sunrise.h"


int red(int);
int red2(int);
int green(int );
int green2(int );

int main(int argc, char** argv) {

    int pi =  pigpio_start(0, 0);
    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return 1;
    }

    set_PWM_range(pi,GREEN_PIN,1000);
    set_PWM_range(pi,RED_PIN,1000);
    set_PWM_range(pi,BLUE_PIN,1000);

        for( int x = 0; x < 5000; x++)
        {
            red2(pi);
            green2(pi);
        }

    return 0;

}

int green2(int pi)
{

    set_PWM_dutycycle(pi, GREEN_PIN, 0 );
    set_PWM_dutycycle(pi, RED_PIN, 0 );
    set_PWM_dutycycle(pi, BLUE_PIN, 0 );

    int x = 0;
    for( x = 0;x <= 1000; x = x + 1)
    {
       usleep(1000);
       double xxx = (double)x / (double)1000;
       set_PWM_dutycycle(pi,GREEN_PIN, pow(xxx,3)*1000 );
    }
    usleep(50000);
    for( x = 1000;x > 0; x = x - 1)
    {
       usleep(1000);
       double xxx = (double)x / (double)1000;
       set_PWM_dutycycle(pi, GREEN_PIN, pow(xxx,3)*1000 );
    }
    return 0;

}
int red2(int pi)
{

    set_PWM_dutycycle(pi, GREEN_PIN, 0 );
    set_PWM_dutycycle(pi, RED_PIN, 0 );
    set_PWM_dutycycle(pi, BLUE_PIN, 0 );

    int x = 0;
    for( x = 0;x <= 1000; x = x + 1)
    {
       usleep(2000);
       double xxx = (double)x / (double)1000;
       set_PWM_dutycycle(pi, RED_PIN, pow(xxx,3)*1000 );
    }
    usleep(50000);
    for( x = 1000;x > 0; x = x - 1)
    {
       usleep(2000);
       double xxx = (double)x / (double)1000;
       set_PWM_dutycycle(pi, RED_PIN, pow(xxx,3)*1000 );
    }
    return 0;

}
int green(int pi)
{

    set_PWM_dutycycle(pi, GREEN_PIN, 0 );
    set_PWM_dutycycle(pi, RED_PIN, 0 );
    set_PWM_dutycycle(pi, BLUE_PIN, 0 );

    int x = 0;
    for( x = 0;x <= 500; x = x + 1)
    {
       usleep(10000);
       set_PWM_dutycycle(pi, GREEN_PIN, x );
    }
    for( ;x <= 1000; x = x + 4)
    {
       usleep(4000);
       set_PWM_dutycycle(pi, GREEN_PIN, x );
    }
    for( int x = 1000;x > 50; x = x - 4)
    {
       usleep(4000);
       set_PWM_dutycycle(pi, GREEN_PIN, x );
    }
    return 0;

}

int red(int pi)
{

    set_PWM_dutycycle(pi, RED_PIN, 0 );
    set_PWM_dutycycle(pi, GREEN_PIN, 0 );
    set_PWM_dutycycle(pi, BLUE_PIN, 0 );
    for( int x = 0;x <= 1000; x = x + 4)
    {
       usleep(4000);
       set_PWM_dutycycle(pi, RED_PIN, x );
    }
    for( int x = 1000;x > 50; x = x - 4)
    {
       usleep(4000);
       set_PWM_dutycycle(pi, RED_PIN, x );
    }


    return 0;

}


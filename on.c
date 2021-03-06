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
 * File:   setled.c
 * Author: dantal
 *
 * Created on November 9, 2016, 8:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "pigpiod_if2.h"
#include "sunrise.h"

int main(int argc, char** argv) {


    int pi =  pigpio_start(0, 0);
    int rtn;

    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return 1;
    }


    rtn = set_PWM_dutycycle(pi, RED_PIN, 255  );
    if ( rtn != 0 )
    {
        fprintf(stderr,"error set dutycycle:%d\n",rtn);
    }

    rtn = set_PWM_dutycycle(pi, GREEN_PIN, GREEN_MAX );
    if ( rtn != 0 )
    {
        fprintf(stderr,"error set dutycycle:%d\n",rtn);
    }

    rtn = set_PWM_dutycycle(pi, BLUE_PIN, BLUE_MAX );
    if ( rtn != 0 )
    {
        fprintf(stderr,"error set dutycycle:%d\n",rtn);
    }


    pigpio_stop(pi);

    return 0;

}


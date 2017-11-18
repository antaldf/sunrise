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
 * File:   sunrise.h
 * Author: antaldf
 *
 * Created on November 9, 2016, 8:29 AM
 */


#define RED_PIN  17
#define GREEN_PIN  22
#define BLUE_PIN  24

#define RED_MAX 1000
#define GREEN_MAX  700
#define BLUE_MAX  700

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "pigpiod_if2.h"
#include "sunrise.h"


int riseOn(int );
int on(int argc, char** argv);
int off();
void getColor();

int main(int argc, char** argv) {

    const char delim[2] = "/";
    char *tok;
    char last[1024];

    tok = strtok(argv[0],delim);
    while ( tok != NULL )
    {
	strcpy(last,tok);
	tok = strtok(NULL,delim);
    }

    int minutes = 10;


    int oni = strcmp(last, "on");
    int offi = strcmp(last, "off");
    int getci = strcmp(last, "getc");
   
    if ( oni == 0 )
    {
        on(argc, argv);
    }
    else if ( getci == 0 )
    {
       getColor();
    }
    else if ( offi == 0 )
    {
       off();
    }
    else
    {
        if (argc > 1) {
            minutes = atoi(argv[1]);
            if ( minutes < 1 )
            {
                return 1;
            }
        }
        riseOn(minutes);
        off();
    }

    return 0;

}

int riseOn(int minutes)
{
    double percentTime;
    time_t startTime = time(0);

    time_t endTime = startTime + (minutes * 60);

    time_t now = time(0);

    int pi =  pigpio_start(0, 0);

    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return 1;
    }
    int x = set_PWM_range(pi,RED_PIN,255);
    int y = set_PWM_range(pi,GREEN_PIN,255);
    int z = set_PWM_range(pi,BLUE_PIN,255);
    if (x+y+z < 0) {
        fprintf(stderr, "pigpio range set failed (%d).\n", pi);
        return 1;
    }

    while ( now < endTime )
    {

        percentTime =  (double)( now - startTime ) / (double) ( minutes * 60 );

        set_PWM_dutycycle(pi, RED_PIN, pow(percentTime,3.00) * RED_MAX  );
        set_PWM_dutycycle(pi, GREEN_PIN, pow(percentTime,3.00) * GREEN_MAX - 5 );
        set_PWM_dutycycle(pi, BLUE_PIN, pow(percentTime,3.00) * BLUE_MAX  );

        sleep(5);
        now = time(0);
    }

	return 0;
}

int off()
{
    int pi =  pigpio_start(0, 0);
    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return 1;
    }

    set_PWM_dutycycle(pi, RED_PIN, 0 );
    set_PWM_dutycycle(pi, GREEN_PIN, 0 );
    set_PWM_dutycycle(pi, BLUE_PIN, 0 );

    return 0;

}

void getColor()
{
    int pi =  pigpio_start(0, 0);
    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return;
    }

    int red = get_PWM_dutycycle(pi, RED_PIN );
    int green = get_PWM_dutycycle(pi, GREEN_PIN );
    int blue = get_PWM_dutycycle(pi, BLUE_PIN );

    printf("{\"red\":\"%d\", \"green\":\"%d\", \"blue\":\"%d\"} ",red, green, blue);

}
int on(int argc, char** argv)
{

    int opt;
    int r = 0;
    int g = 0;
    int b = 0;
    while ((opt = getopt(argc, argv, "r:g:b:")) != -1) {
               switch (opt) {
               case 'r':
                   r = atoi(optarg);
                   break;
               case 'g':
                   g = atoi(optarg);
                   break;
               case 'b':
                   b = atoi(optarg);
                   break;
		}
    }

    if ( r > 255 ) { r = 255; }
    if ( g > 255 ) { g = 255; }
    if ( b > 255 ) { b = 255; }



    int pi =  pigpio_start(0, 0);
    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return 1;
    }
    //int x = set_PWM_range(pi,RED_PIN,1000);
    //int y = set_PWM_range(pi,GREEN_PIN,1000);
    //int z = set_PWM_range(pi,BLUE_PIN,1000);
    //if (x+y+z < 0) {
    //    fprintf(stderr, "pigpio range set failed (%d).\n", pi);
    //    return 1;
    //}
    //set_PWM_dutycycle(pi, RED_PIN, RED_MAX * ( r / 100.0d));
    //set_PWM_dutycycle(pi, GREEN_PIN, GREEN_MAX * ( g / 100.0d) );
    //set_PWM_dutycycle(pi, BLUE_PIN, BLUE_MAX * ( b / 100.0d ));
    set_PWM_dutycycle(pi, RED_PIN, r);
    set_PWM_dutycycle(pi, GREEN_PIN, g);
    set_PWM_dutycycle(pi, BLUE_PIN, b);

    return 0;

}



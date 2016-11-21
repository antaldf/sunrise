/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
#include "pigpiod_if2.h"

#define RED_PIN  17
#define GREEN_PIN  22
#define BLUE_PIN  24

#define RED_MAX 254
#define GREEN_MAX  150
#define BLUE_MAX  200

int riseOn(int );

int main(int argc, char** argv) {

    int minutes = 10;

    if (argc > 1) {
        minutes = atoi(argv[1]);
        if ( minutes < 1 )
        {
            return 1;
        }
    }

    riseOn(minutes);

    return 0;

}
/*
red: 100/ (1 + e^(-0.07(x-60)))
   green: 100 / (1 + e^(-0.08(x-75)))
   blue:  10/(1+0.005*abs(x-20)^3) +  (100*e)/(e + e^(-0.08(x-80)))

*/
int riseOn(int minutes)
{
    double percentTime;
    time_t startTime = time(0);
    int pi =  pigpio_start(0, 0);

    if (pi < 0) {
        fprintf(stderr, "pigpio initialisation failed (%d).\n", pi);
        return 1;
    }

    time_t endTime = startTime + (minutes * 60);

    time_t now = time(0);
    while ( now < endTime )
    {


        percentTime =  (double)( now - startTime ) / (double) ( minutes * 60 );
	precentTime = percnetTime * 100;
	double red = 100 / exp((-0.07*(percentTime-60)));

	printf("%d\n");
//        set_PWM_dutycycle(pi, RED_PIN, (percentTime*percentTime) * RED_MAX + 1 );
//        set_PWM_dutycycle(pi, GREEN_PIN, (percentTime*percentTime*percentTime) * GREEN_MAX - 10 );
//        set_PWM_dutycycle(pi, BLUE_PIN, (percentTime*percentTime) * BLUE_MAX -3 );

        sleep(5);
        now = time(0);
    }

	return 0;
}

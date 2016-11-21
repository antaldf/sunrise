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
#define GREEN_MAX  200
#define BLUE_MAX  200


int main(int argc, char** argv) {


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


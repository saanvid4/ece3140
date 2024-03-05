/*
 * test_part2.c
 *
 *  Created on: Feb 17, 2024
 *      Author: nen38
 */

#include "ECE3140Lab2.h"
#include "led.h"

void main(void){

	int i; //counter for loops

	/* values for led(s) out */
	grb32_t led1_val;
	grb32_t led2_val;
	grb32_t led_vals[2];

	int up_flag [2]; //flag to implement pulsing behavior below.

	set15MHz();
	led_init();
	delay(1); // make sure the LEDs are reset in case led_init is messed up

	/* Turn on the red,green, and blue LEDs one at a time
	 *
	 * Cycle through them in one second each, first for LED1 then LED2.
	 */

	led1_val.red=64; // don't go full power but set it 1/4 power
	led1_val.green=0;
	led1_val.blue=0;
	set_led(led1_val);
	delay(333);

	led1_val.red=0;
	led1_val.green=64;
	set_led(led1_val);
	delay(333);

	led1_val.green=0;
	led1_val.blue=64;
	set_led(led1_val);
	delay(333);

	led1_val.red=0;
	led1_val.green=0;
	led1_val.blue=0;

	led2_val.red=64;
	led2_val.green=0;
	led2_val.blue=0;
	set_led(led1_val); // the values for LED2 need to go through LED1
	set_led(led2_val); // so you need to send both to set LED2
	delay(333);

	led2_val.red=0;
	led2_val.green=64;
	set_led(led1_val);
	set_led(led2_val);
	delay(333);

	led2_val.green=0;
	led2_val.blue=64;
	set_led(led1_val);
	set_led(led2_val);
	delay(333);

	//turn off LED1 and LED2 and wait for a second.
	leds_off(2);
	delay(1000);

	/* The official Cornell color red is called
	 * Carnellian and has the RGB coordinates (179,27,27).
	 *
	 * The code below should pulse this most pleasing color of
	 * red on both LED1 and LED2, but out of phase.
	 *
	 * Since the color coordinates are not divisible by each other
	 * we approximate an even dimming by going up/down in fixed steps.
	 * As a result, the color will get redder as it dims.
	 */
	led_vals[0].red=179;
	led_vals[0].blue=27;
	led_vals[0].green=27;

	led_vals[1].red=18; //we'll go down in steps of 6 so 179-27*6
	led_vals[1].blue=0;
	led_vals[1].green=0;

	up_flag[0] = 0; //LED1 starts off going down
	up_flag[1] = 1; //LED2 starts off going up

	 while(1){
		for(i=0; i<2;i++){

			//check if the red value has reached
			//extremes and switch directions
			if (led_vals[i].red >= 179){
				up_flag[i]=0;
			}else if(led_vals[i].red <= 18){
				up_flag[i]=1;
			}

			//in/de-crease the LED values
			if (up_flag[i]) {
				led_vals[i].red +=6;
				led_vals[i].blue +=1;
				led_vals[i].green +=1;
			} else {
				led_vals[i].red -=6;
				led_vals[i].blue -=1;
				led_vals[i].green -=1;
			}

			//write new values to LED1 and LED2
			set_leds(led_vals,2);
			delay(50); // spends 2.7 per pulse

		}//end for loop
     }//end while loop
}

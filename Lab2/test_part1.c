/*
 * test_part1.c
 *
 *  Created on: Feb 17, 2024
 *      Author: nen38
 */

#include "ECE3140Lab2.h"
#include "led.h"

/* This notation passes in a function by its address
 * The parameter is called a function pointer and it's super useful
 * since we can write sub-routines that take functions as arguments.
 */
void dot( void (* led_toggle_fun)(void)){
	led_toggle_fun();
	delay(200);
	led_toggle_fun();
	delay(200);
}

void dash( void (* led_toggle_fun)(void)){
	led_toggle_fun();
	delay(600);
	led_toggle_fun();
	delay(200);}


/* Function that outputs a digit (0-9)
 * on different LEDs. The address of the function for
 * toggling the LED is passed as the second argument.
 *
 * This approach uses the structure of Morse digits
 * and computes dots and dashes using modular arithmatic.
 *
 * If you write down all the digits and look at the position
 * for the "mark" in the 5-mark digit then:
 *
 * (digit + mark) mod 10 is greater or equal to 5 for dots
 *
 * Looking at the digit pattern written down, mark 5
 * should be output first. This is nice an compact in C
 * but would be difficult to write in assembly without a
 * divide instruction. Here, the mod operator % is implemented
 * in software by the C library.
 */
void morse(int digit, void * led_toggle_fun){
	for(int mark=4; mark >= 0; mark--){
		if ((digit + mark)%10 >=5 ){
			dot(led_toggle_fun);}
		else{
			dash(led_toggle_fun);}
	}
	/*add two more dot lengths to finish digit*/
	delay(400);
}

/*first 30 digits of Pi*/
uint8_t pi[30] ={3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7};

/* Array for function pointers to the three different toggle functions for LED0 */
void (*toggle_funs[3])={red_toggle,green_toggle,blue_toggle};

void main(void){
	set15MHz(); //Initialize clocks.
	led_init(); //Initialize LEDs

	/* Turn on all the the leds one at a time.
	 * Cycle through them in 1 second.
	 */
	red_on();
	delay(333);
	red_off();
	green_on();
	delay(333);
	green_off();
	blue_on();
	delay(333);
	blue_off();

	//wait one second.
	delay(1000);

	/*
	 * Output Morse digits in different colors
	 */

	//Test all the functions in
	for(int i=0; i<10; i++){
		morse(i,blue_toggle);
	}

	//Output the first 30 digits of PI and cycle through the colors
	for(int i=0; i<30; i++){
		morse(pi[i],toggle_funs[i%3]);
	}

	while(1){} //trap execution
}

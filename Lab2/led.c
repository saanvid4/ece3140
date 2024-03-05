#include <MKL46Z4.h>
#include <led.h>
#include "ECE3140Lab2.h"

const int LED_PIN = 3;
const int RED_PIN = 16;
const int BLUE_PIN = 2;
const int GREEN_PIN = 6;


void led_init(void){

	// initialize led
	SIM -> SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE -> PCR[LED_PIN] = PORT_PCR_MUX(0b001);
	PTE -> PDDR |= GPIO_PDDR_PDD(1 << LED_PIN);


	// set up for red led
	PORTE -> PCR[RED_PIN] = PORT_PCR_MUX(0b001);
	PTE -> PDDR |= GPIO_PDDR_PDD(1 << RED_PIN);

	// set up for green led
	PORTE -> PCR[GREEN_PIN] = PORT_PCR_MUX(0b001);
	PTE -> PDDR |= GPIO_PDDR_PDD(1 << GREEN_PIN);

	// set up for blue led
	PORTE -> PCR[BLUE_PIN] = PORT_PCR_MUX(0b001);
	PTE -> PDDR |= GPIO_PDDR_PDD(1 << BLUE_PIN);

	PTE -> PCOR |= GPIO_PCOR_PTCO(1 << LED_PIN);
	PTE -> PSOR |= GPIO_PSOR_PTSO(1 << RED_PIN);
	PTE -> PSOR |= GPIO_PSOR_PTSO(1 << GREEN_PIN);
	PTE -> PSOR |= GPIO_PSOR_PTSO(1 << BLUE_PIN);

}



void all_leds_off(void){

	red_off();
	green_off();
	blue_off();

}

void led_off(void){
	grb32_t rgb_val;
	rgb_val.red = 0;
	rgb_val.green = 0;
	rgb_val.blue = 0;
	set_led(rgb_val);
}

void set_led(grb32_t rgb_val){
	set(rgb_val);
}




void set_leds(grb32_t * rgb_vals, uint32_t num_led){
	delay(345);
	for (uint32_t i = 0; i < num_led; i++){
		set_led(rgb_vals[i]);
	}
}

void leds_off(uint32_t num_led){
	for(uint32_t i = 0; i < num_led; i++){
		led_off();
	}
}


// red led

void red_on(void){

	PTE -> PCOR = GPIO_PCOR_PTCO(1 << RED_PIN);

}

void red_off(void){

	PTE -> PSOR = GPIO_PSOR_PTSO(1 << RED_PIN);

}

void red_toggle(void){

	PTE -> PTOR = GPIO_PTOR_PTTO(1 << RED_PIN);

}



// blue led

void blue_on(void){

	PTE -> PCOR = GPIO_PCOR_PTCO(1 << BLUE_PIN);

}

void blue_off(void){

	PTE -> PSOR = GPIO_PSOR_PTSO(1 << BLUE_PIN);

}

void blue_toggle(void){

	PTE -> PTOR = GPIO_PTOR_PTTO(1 << BLUE_PIN);

}

// green led

void green_on(void){

	PTE -> PCOR = GPIO_PCOR_PTCO(1 << GREEN_PIN);

}

void green_off(void){

	PTE -> PSOR = GPIO_PSOR_PTSO(1 << GREEN_PIN);

}

void green_toggle(void){

	PTE -> PTOR = GPIO_PTOR_PTTO(1 << GREEN_PIN);

}






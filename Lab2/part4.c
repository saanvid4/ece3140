#include <MKL46Z4.h>
#include "led.h"
#include "ECE3140Lab2.h"

// define load values for the PIT
#define PIT_LED_ON_DURATION (1500000)
#define PIT_LED_OFF_DURATION (15000000)

// initialize the PIT for controlling the green led
void init_pit(void) {

    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    PIT->MCR &= ~PIT_MCR_MDIS_MASK;

    PIT->CHANNEL[0].LDVAL = PIT_LED_ON_DURATION;

    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;

    NVIC_EnableIRQ(PIT_IRQn);
}

// PIT interrupt handler
void PIT_IRQHandler(void) {
    green_toggle_frdm();

    if (PIT->CHANNEL[0].LDVAL == PIT_LED_ON_DURATION) {
        PIT->CHANNEL[0].LDVAL = PIT_LED_OFF_DURATION;
    } else {
        PIT->CHANNEL[0].LDVAL = PIT_LED_ON_DURATION;
    }

    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}

int main(void) {
    led_init_frdm();
    init_pit();

    while (1) {
        red_toggle_frdm();
        delay(1000);
    }
}



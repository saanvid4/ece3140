#include <MKL46Z4.h>
#include <led.h>
#include <ECE3140Lab2.h>

/* ----------------------------------------------------------------------
 Note the different characters around the library names.
 Use <> characters to include system libraries
 Use "" characters to include your own libraries from the sources folder 
 ------------------------------------------------------------------------*/
void initPIT(void) {
    // enable clock to PIT module
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // enable PIT module (turn off PIT module disable bit)
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;

    // set load value for PIT channel 0 for 1 second interval at 15MHz
    PIT->CHANNEL[0].LDVAL = 10000000; // 15,000,000 - 1

    // enable PIT0 timer
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void initRedLED(void) {
    // enable clock to port E
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    PORTE->PCR[29] = (1 << 8);
    // set PTE29 as output
    GPIOE->PDDR |= (1 << 29);
    GPIOE->PSOR |= (1 << 29);

}


//int main(void) {
//    initRedLED();
//    initPIT();
//
//    while (1) {
//        // poll the TFLG register to check for the timer expiration
//        if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
//            // timer has expired, toggle the red led
//            red_toggle_frdm();
//
//            // clear the timer interrupt flag to reset the timer
//            PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
//        }
//    }
//    return 0; // the code should never reach this point
//}

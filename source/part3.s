.section .text
.global main


//Set up constants for port. Don't Change!
.equ 	PCRD5, 		0x4004C014 //PORTD_PCR5   (GREEN), the manual has these backward
.equ 	SCGC5, 		0x40048038 //SIM_SCGC5    address
.equ 	PDDRD,  	0x400FF0D4 //GPIOB_PDDR   address
.equ 	PCORD,  	0x400FF0C8 //GPIOB_PCOR   address
.equ 	PSORD,  	0x400FF0C4 //GPIOB_PSOR   address


.equ 	bit_twelve, 0x00001000  // 1 << 12, for turning on port clock
.equ 	bit_eight, 	0x00000100  // 1 << 8,  for setting MUX to GPIO
.equ	bit_five, 	0x00000020  // 1 << 5,  for manipulating PIN


/*
---  Write your code below this line ---
Feel free to include additional labels as needed.
*/

/* main:
    BL      LEDSETUP          // Initialize LED setup
    MOV     R0, #9            // Set R0 to 6 for fib(6)
    BL      fib               // Calculate Fibonacci number for R0
    BL      morseMulti       // Display the result in Morse code
    B       forever           // Loop forever after displaying
 */

fib:
    PUSH {R1, R2, LR}          // Save LR, R1, and R2 to stack for later restoration
    CMP R0, #0                 // Check if n <= 0
    BLE fib_zero               // If so, branch to handle n <= 0
    CMP R0, #1                 // Check if n == 1
    BEQ fib_one                // If so, branch to handle n == 1

    // Recursive case for n > 1: fib(n-1) + fib(n-2)
    SUB R1, R0, #1             // Prepare argument for fib(n-1)
    MOV R0, R1
    BL fib                     // Call fib(n-1)
    MOV R2, R0                 // Save result of fib(n-1) in R2

    SUB R1, R1, #1             // Prepare argument for fib(n-2)
    MOV R0, R1
    BL fib                     // Call fib(n-2)
    ADD R0, R0, R2             // Sum results: fib(n-1) + fib(n-2)

    POP {R1, R2, PC}           // Restore R2, R1, and LR
    BX LR                      // Return from function

fib_zero:
    MOV R0, #0                 // Return 0 for fib(0)
    B fib_end

fib_one:
    MOV R0, #1                 // Return 1 for fib(1)

fib_end:
    POP {R1, R2, PC}           // Restore R2, R1, and LR
    BX LR                      // Return from function

// Call this function first to set up the LED
LEDSETUP:
        PUSH  {R4, R5} // To preserve R4 and R5
        LDR   R4, = bit_twelve // Load the value 1 << 10
        LDR   R5, = SCGC5
        STR   R4, [R5]

        LDR   R4, = bit_eight
        LDR   R5, = PCRD5
        STR   R4, [R5]

        LDR   R4, = bit_five
        LDR   R5, = PDDRD
        STR   R4, [R5]
        POP   {R4, R5}
        BX    LR

// The functions below are for you to use freely
LEDON:
        PUSH  {R4, R5}
        LDR   R4, = bit_five
        LDR   R5, = PCORD
        STR   R4, [R5]
        POP   {R4, R5}
        BX    LR
LEDOFF:
        PUSH  {R4, R5}
        LDR   R4, = bit_five
        LDR   R5, = PSORD
        STR   R4, [R5]
        POP   {R4, R5}
        BX    LR

   // function to display a single digit in morse code
morse_digit:
        PUSH  {LR}
        CMP   R0, #5
        BGT   n_gt5
        // If here, n <= 5
        // number of dots in n :  R0 = n
        // number of dashs in n : R1 = 5 - n
        ADD   R1, R0, #-5
        NEG   R1, R1

loop_dot1:
        CMP   R0, #0
        BLE   loop_dash1
        BL    dot
        SUB  R0, R0, #1
        B     loop_dot1

loop_dash1:
        CMP   R1, #0
        BLE   done
        BL    dash
        SUB R1, R1, #1
        B     loop_dash1

n_gt5:
        // If here, n > 5
        // number of dashs in n : n - 5
        SUB   R0, R0, #5
        // number of dots in n : 5 - (n - 5)
        ADD   R1, R0, #-5
        NEG   R1, R1

loop_dash2:
        CMP   R0, #0
        BLE   loop_dot2
        BL    dash
        SUB  R0, R0, #1
        B     loop_dash2

loop_dot2:
        CMP   R1, #0
        BLE   done
        BL    dot
        SUB R1, R1, #1
        B     loop_dot2

done:
        POP   {PC}
        BX    LR

    // function to display a single dash with LED
dash:
        PUSH  {LR}
        BL    LEDON
        BL    space
        BL    space
        BL    space
        BL    LEDOFF
        BL    space
        POP   {PC}
        BX    LR

    // function to display a single dot with LED
dot:
        PUSH  {LR}
        BL    LEDON
        BL    space
        BL    LEDOFF
        BL    space
        POP   {PC}
        BX    LR

    // function to create a delay between LED on / off
space:
        PUSH  {LR}
        LDR   R2, = 0x1E8480     // set R2 to an arbitary large value
loop:
    	SUB R2, R2, #1
        BNE   loop
        POP   {PC}
        BX    LR

forever:
        B   forever           // wait here forever

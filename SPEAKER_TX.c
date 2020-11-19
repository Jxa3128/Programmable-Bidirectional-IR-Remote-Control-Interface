//Jorge Avila 1001543128

// When the interrupt is called (or hit)
// Modified _ccs.c file too
#include "IR_TX.h"
#include "uart0.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "SPEAKER_TX.h"


//inits all the components for the speaker
void initSPEAKER_TX()
{

    //initalize
    //port B was initalized here
    SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0;
    //port e
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0 | SYSCTL_RCGCTIMER_R1;
    _delay_cycles(3);

    // Set GPIO ports to use APB -- this was moved from initHw()
    SYSCTL_GPIOHBCTL_R = 0;

    //configure the PWMO (Gen 0 - Output A)
    GPIO_PORTE_DIR_R |= speakerTX_MASK; //GPO_PWM_MASK;   // make bit 6 an output
    GPIO_PORTE_DR2R_R |= speakerTX_MASK; //GPO_PWM_MASK; // set drive strength to 2mA
    GPIO_PORTE_DEN_R |= speakerTX_MASK; //GPO_PWM_MASK;   // enable digital
    GPIO_PORTE_AFSEL_R |= speakerTX_MASK; //GPO_PWM_MASK;

//    GPIO_PORTE_PCTL_R &= GPIO_PCTL_P4_M;      // enable PWM
//    GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE4_M0PWM0;

    SYSCTL_SRPWM_R = SYSCTL_SRPWM_R0;
    SYSCTL_SRPWM_R = 0;
    PWM0_0_CTL_R = 0;
    PWM0_0_GENA_R |= PWM_0_GENA_ACTCMPBD_ZERO | PWM_0_GENA_ACTLOAD_ONE;
    PWM0_0_LOAD_R = DutyCycle;
    PWM0_INVERT_R = PWM_INVERT_PWM0INV;
    PWM0_0_CMPB_R = (DutyCycle / 2) - 1;
    PWM0_0_CTL_R = PWM_0_CTL_ENABLE;
    PWM0_ENABLE_R = PWM_ENABLE_PWM0EN;

    GPIO_PORTE_DEN_R &= ~speakerTX_MASK;
}

void playSound(uint8_t address, uint8_t data)
{
    uint8_t addressArray[8], dataArray[8];
    uint8_t i, test;
    test = address;
    //converting the address and data first to binary
    //before sending it at the bottom to
    //sendData(addressArray,dataArray);
    for (i = 8; i > 0; --i)
    {
        addressArray[8 - i] = (1 << (i - 1)) & test;
    }
    test = data;
    for (i = 8; i > 0; --i)
    {
        addressArray[8 - i] = (1 << (i - 1)) & test;
    }
    sendData(addressArray, dataArray);
}


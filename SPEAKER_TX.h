//Jorge Avila
//1001543128
#ifndef SPEAKER_TX_H_
#define SPEAKER_TX_H_
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>

#define DutyCycle 1050
//speaker transmitter TX -> PE4
#define speakerTX    (*((volatile uint32_t *)(0x42000000 + (0x40024400-0x40000000)*32 + 4*4))) //bit 4
#define speakerTX_MASK  16//2^6

void initSPEAKER_TX(void);
void playSound(uint8_t address, uint8_t data);

#endif

#include "DigiJoystick.h"

#define DATA_PIN 2

char mask = (1 << DATA_PIN);

void high() {
  DDRB &= ~mask;
}

void low() {
  DDRB |= mask;
}
void setup() {
  digitalWrite(DATA_PIN, LOW);
  high();
}

void loop() {
  char mask_ = mask;
  char buf[8] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x00, 0x00
  };

  noInterrupts();
  for (int i = 0; i < 7; i++) {
    low();
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    high();
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  }
  low();
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  high();
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");

  low();
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
  high();

  for (int i = 0; i < 8; i++) {
    while (PINB & mask_);
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    buf[7] = (buf[7] << 1) | (PINB & mask) != 0;
    while (!(PINB & mask_));
  }

  for (int i = 0; i < 8; i++) {
    while (PINB & mask_);
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    buf[6] = (buf[6] << 1) | (PINB & mask) != 0;
    while (!(PINB & mask_));
  }

  for (int i = 0; i < 8; i++) {
    while (PINB & mask_);
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    buf[0] = (buf[0] << 1) | (PINB & mask) != 0;
    while (!(PINB & mask_));
  }
  
  for (int i = 0; i < 8; i++) {
    while (PINB & mask_);
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    asm volatile ("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t");
    buf[1] = (buf[1] << 1) | (PINB & mask) != 0;
    while (!(PINB & mask_));
  }
  
  //  while (PINB & mask_);
  //  while (!(PINB & mask_));
  
  buf[0] = buf[0] - 127;
  buf[1] = 128 - buf[1];
  DigiJoystick.setValues(buf);
  interrupts();
  DigiJoystick.delay(3);
}

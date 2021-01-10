#include "src/Encoder/Encoder.h"
#include "src/USBKeyboard/USBKeyboard.h"

#define MMKEY_VOL_UP 0xE9
#define MMKEY_VOL_DOWN 0xEA
#define MMKEY_PLAYPAUSE 0xCD

#define CLK_PIN 9
#define DT_PIN 10
#define SW_PIN PB3 // digital pin 11
#define DEFAULT_POS_VALUE -999
#define DELAY 2000
long oldPosition = DEFAULT_POS_VALUE;
long is_pressed = LOW;

Encoder encoder(CLK_PIN, DT_PIN);
USBKeyboard keyboard = USBKeyboard();

void setup() {
  TIMSK0 = 0;

  DDRB |= (1 << SW_PIN);
  PORTB |= (1 << SW_PIN);
}

void loop() {
  keyboard.update();
  
  long newPosition = encoder.read();

  if (newPosition != oldPosition) {
    if (oldPosition != DEFAULT_POS_VALUE && newPosition % 2)
    {
      for (int i = 0; i < abs(newPosition - oldPosition); i = i + 2)
      {
        keyboard.sendMultimediaKey(
          newPosition > oldPosition ? 
          MMKEY_VOL_DOWN : 
          MMKEY_VOL_UP
        );
      }
    }
    oldPosition = newPosition;
  }
  
  if (!(PINB & (1 << SW_PIN)))
  {
    if (!is_pressed)
    {
      keyboard.sendMultimediaKey(MMKEY_PLAYPAUSE);
    }
    is_pressed = HIGH;
  }
  else
  {
    is_pressed = LOW;
  }

  delayMicroseconds(DELAY);
}

#include<FastLED.h>

// Based on FastLED example NoisePlayground

#define NUM_LEDS 240

// The 32bit version of our coordinates
static uint16_t x;
static uint16_t y;
static uint16_t z;

// The leds
CRGB leds[NUM_LEDS];

uint16_t speed = 4;

// uint16_t scale = 1; // mostly just solid colors
// uint16_t scale = 4011; // very zoomed out and shimmery
uint16_t scale = 3311;

// This is the array that we keep our computed noise values in
uint8_t noise[NUM_LEDS];

void setup() {
  delay(3000);
  LEDS.addLeds<WS2811,6,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(36);

  // Initialize our coordinates to some random values
  x = random16();
  y = random16();
  z = random16();
}

// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  for(int i = 0; i < NUM_LEDS; i++) {
    int ioffset = scale * i;
    noise[i] = inoise8(x + ioffset,y + ioffset,z);
  }
  z += speed;
}


void loop() {
  fillnoise8();
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i > 210) {
      leds[i] = CHSV(HUE_BLUE,5,noise[i]);
    } else {
      if(i%2 == 0) {
        leds[i] = CHSV(HUE_RED,255,noise[i]);
      } else {
        leds[i] = CHSV(HUE_GREEN,255,noise[i]);
      }
    }
  }

  LEDS.show();
}

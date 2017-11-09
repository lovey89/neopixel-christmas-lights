#include <Adafruit_NeoPixel.h>
#include <EnableInterrupt.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "constants.h"
#include "light_utils.h"
#include "light_effects.h"
#include "button_utils.h"

/* Constants */
uint32_t last_interrupt_time = 0;
uint8_t button_pressed = FALSE;

uint16_t light_effect = 1000;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NO_OF_PIXELS, DATA_PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setupInterruptPin()
{
  //set the pin to input
  pinMode(BUTTON_PIN, INPUT);
  //attach a PinChange Interrupt to our pin on the rising edge
  enableInterrupt(BUTTON_PIN, buttonCallback, RISING);
}

void setupLeds()
{
  strip.begin();
  blank();
  strip.show(); // Initialize all pixels to 'off'
}

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000)
    {
      clock_prescale_set(clock_div_1);
    }
  #endif
  // End of trinket special code

  Serial.begin(9600);

  setupLeds();
  setupInterruptPin();

  fadeInEffect();
}

void buttonCallback()
{
  uint32_t interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY)
  {
    button_pressed = TRUE;
    light_effect++;
    Serial.print("click!\n");
    Serial.flush();
  }

  last_interrupt_time = interrupt_time;
}

void loop()
{
  Serial.print("loop2\n");
  Serial.flush();

  switch (light_effect)
  {
    case 0:
      colorWipe(strip.Color(200, 200, 200), 250);
      break;
    case 1:
      police(1);
      break;
    case 2:
      layerRainbowCycle(20);
      break;
    case 3:
      layerRainbow(50);
      break;
    default:
      // If there are no more light effects, start from the beginning
      light_effect = 0;
      break;
  }

  //theaterChaseRainbow(50);

  //rainbow(20);
  //rainbowCycle(20);
  //colorWipe(strip.Color(255, 0, 0), 500); // Green
  //colorWipe(strip.Color(0, 255, 0), 500); // Red
  //colorWipe(strip.Color(0, 0, 255), 500); // Blue

  /*
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);

  */
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < NO_OF_PIXELS; i++)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < NO_OF_PIXELS; i++)
    {
      strip.setPixelColor(i, wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) // 5 cycles of all colors on wheel
  {
    for (i = 0; i < NO_OF_PIXELS; i++)
    {
      strip.setPixelColor(i, wheel(((i * 256 / NO_OF_PIXELS) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait)
{
  for (int j = 0; j < 10; j++) // do 10 cycles of chasing
  {
    for (int q = 0; q < 3; q++)
    {
      for (uint16_t i = 0; i < NO_OF_PIXELS; i = i + 3)
      {
        strip.setPixelColor(i + q, c); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < NO_OF_PIXELS; i = i + 3)
      {
        strip.setPixelColor(i + q, 0); //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait)
{
  for (int j = 0; j < 256; j++) // cycle all 256 colors in the wheel
  {
    for (int q = 0; q < 3; q++)
    {
      for (uint16_t i = 0; i < NO_OF_PIXELS; i = i + 3)
      {
        strip.setPixelColor(i+q, wheel((i + j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < NO_OF_PIXELS; i = i + 3)
      {
        strip.setPixelColor(i + q, 0); // turn every third pixel off
      }
    }
  }
}


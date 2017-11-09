#include "light_utils.h"
#include "light_effects.h"
#include "constants.h"
#include "button_utils.h"
#include "global_variables.h"

void blinkRange(uint8_t fromPixel, uint8_t toPixel, uint32_t color, uint16_t blinkDelay, uint8_t iterations);

void police(uint8_t iterations)
{
  uint16_t blinkDelay = 90;
  uint8_t blinkIterations = 3;

  blank();

  for (uint8_t i = 0; i < iterations; i++)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    blinkRange(MIN_PIXEL, MIDDLE_PIXEL, strip.Color(0, 0, 150), blinkDelay, blinkIterations);
    blinkRange(MIDDLE_PIXEL, MAX_PIXEL, strip.Color(150, 0, 0), blinkDelay, blinkIterations);
  }
}

void blinkRange(uint8_t fromPixel, uint8_t toPixel, uint32_t color, uint16_t blinkDelay, uint8_t iterations)
{
  for (uint8_t i = 0; i < iterations; i++)
  {
    setRange(TRUE, color, fromPixel, toPixel);
    delay(blinkDelay);
    setRange(TRUE, strip.Color(0, 0, 0), fromPixel, toPixel);
    delay(blinkDelay);
  }
}

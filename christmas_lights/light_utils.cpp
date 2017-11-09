#include "light_utils.h"
#include "constants.h"
#include "global_variables.h"

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(uint8_t wheelPos)
{
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85)
  {
    return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  else if (wheelPos < 170)
  {
    wheelPos -= 85;
    return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  else
  {
    wheelPos -= 170;
    return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  }
}

/* 0 means middle light */
uint8_t getLeftPixelForLayer(uint8_t layer)
{
  return MIDDLE_PIXEL - layer;
}

uint8_t getRightPixelForLayer(uint8_t layer)
{
  return MIDDLE_PIXEL + layer;
}

void setRange(uint8_t showStrip, uint32_t color, uint8_t fromPixel, uint8_t toPixel)
{
  for (uint16_t pixel = fromPixel; pixel <= toPixel; pixel++)
  {
    strip.setPixelColor(pixel, color);
  }

  if (showStrip)
  {
    strip.show();
  }
}

void setPixels(uint8_t showStrip, uint32_t color, uint8_t noOfPixels, ...)
{
  int pixels[noOfPixels];

  va_list valist;

  /* initialize valist for num number of arguments */
  va_start(valist, noOfPixels);

  for (uint8_t i = 0; i < noOfPixels; i++)
  {
    pixels[i] = va_arg(valist, int);
  }

  /* clean memory reserved for valist */
  va_end(valist);

  for (uint8_t pixelIndex = 0; pixelIndex < noOfPixels; pixelIndex++)
  {
    int pixel = pixels[pixelIndex];
    strip.setPixelColor(pixel, color);
  }

  if (showStrip)
  {
    strip.show();
  }
}

void setLayer(uint8_t showStrip, uint32_t color, uint8_t layer)
{
  /* This works also for layer 0 (middle pixel) */
  setPixels(showStrip, color, 2, getLeftPixelForLayer(layer), getRightPixelForLayer(layer));
}

void blank()
{
  for (uint8_t i = 0; i < NO_OF_PIXELS; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

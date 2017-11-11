#include "constants.h"
#include "light_utils.h"
#include "light_effects.h"
#include "button_utils.h"

void layerRainbowHelper(uint8_t spacing, uint8_t wait);

void layerRainbow(uint8_t wait)
{
  layerRainbowHelper(10, wait);
}

void layerRainbowMiddle(uint8_t wait)
{
  layerRainbowHelper(256 / (NO_OF_LAYERS * 3), wait);
}

void layerRainbowCycle(uint8_t wait)
{
  layerRainbowHelper(256 / NO_OF_LAYERS, wait);
}

void theaterChaseRainbow(uint8_t wait)
{
  for (int j = 0; j < 256; j++) // cycle all 256 colors in the wheel
  {
    for (int q = 0; q < 3; q++)
    {
      for (uint16_t i = 0; i < NO_OF_PIXELS; i = i + 3)
      {
        strip.setPixelColor(i + q, wheel((i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      RETURN_IF_BUTTON_WAS_PRESSED();
      delay(wait);

      for (uint16_t i = 0; i < NO_OF_PIXELS; i = i + 3)
      {
        strip.setPixelColor(i + q, 0); // turn every third pixel off
      }
    }
  }
}

/* PRIVATE FUNCTIONS */
void layerRainbowHelper(uint8_t spacing, uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    for (i = 0; i < NO_OF_LAYERS; i++)
    {
      setLayer(wheel((i * spacing + j) & 255), (NO_OF_LAYERS - 1) - i);
    }
    strip.show();
    delay(wait);
  }
}

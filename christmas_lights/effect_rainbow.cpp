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

void layerRainbowHelper(uint8_t spacing, uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
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

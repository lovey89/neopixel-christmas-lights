#include "light_utils.h"
#include "light_effects.h"
#include "constants.h"
#include "button_utils.h"

// Fill the dots one after the other with a color
void colorWipe(uint32_t color, uint8_t wait)
{
  for (uint16_t i = 0; i < NO_OF_PIXELS; i++)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void colorWipeLayer(uint32_t color, uint8_t wait)
{
  for (uint16_t i = MAX_LAYER; i >= MIN_LAYER; i--)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    
    setLayer(FALSE, color, i);
    strip.show();
    delay(wait);
  }
}

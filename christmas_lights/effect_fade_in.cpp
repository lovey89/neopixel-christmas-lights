#include "light_utils.h"
#include "light_effects.h"
#include "constants.h"
#include "button_utils.h"

void fadeIn(uint8_t maxWhite, uint16_t wait, uint8_t layer);
void fadeAllFromTo(uint8_t fromWhite, uint8_t toWhite, uint16_t wait);

void fadeInEffect()
{
  Serial.print("bootup\n");
  Serial.flush();
  blank();

  for (uint8_t layer = 0; layer < NO_OF_LAYERS; layer++)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    fadeIn(10, 75, layer);
  }

  delay(500);
  fadeAllFromTo(10, 200, 25);

  delay(300);
}

void fadeAllFromTo(uint8_t fromWhite, uint8_t toWhite, uint16_t wait)
{
  for (uint8_t white = fromWhite; white < toWhite; white++)
  {
    RETURN_IF_BUTTON_WAS_PRESSED();
    for (uint8_t pixel = 0; pixel < NO_OF_PIXELS; pixel++)
    {
      strip.setPixelColor(pixel, strip.Color(white, white, white));
    }
    strip.show();
    delay(wait);
  }
}

void fadeIn(uint8_t maxWhite, uint16_t wait, uint8_t layer)
{
  for (uint8_t white = 0; white <= maxWhite; white++)
  {
    setLayer(TRUE, strip.Color(white, white, white), layer);
    delay(wait);
  }
}


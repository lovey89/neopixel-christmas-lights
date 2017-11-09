#ifndef LIGHT_UTILS_H
#define LIGHT_UTILS_H

#include <stdint.h>

uint32_t wheel(uint8_t WheelPos);

uint8_t getLeftPixelForLayer(uint8_t layer);

uint8_t getRightPixelForLayer(uint8_t layer);

void setRange(uint32_t color, uint8_t fromPixel, uint8_t toPixel);

void setPixels(uint32_t color, uint8_t noOfPixels, ...);

void setLayer(uint32_t color, uint8_t layer);

void blank();

#endif // LIGHT_UTILS_H

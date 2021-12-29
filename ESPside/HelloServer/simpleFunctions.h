#include <Adafruit_NeoPixel.h>
#include "ledConfig.h"
#include "argManagement.h"

void simpleColorWipe(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}
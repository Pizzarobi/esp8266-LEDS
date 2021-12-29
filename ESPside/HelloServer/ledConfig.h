#include <Adafruit_NeoPixel.h>

const int LED_PIN = D3;
const int LED_COUNT = 279;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Colors STANDARD
const uint32_t RED = strip.Color(255, 0, 0);
const uint32_t GREEN = strip.Color(0, 255, 0);
const uint32_t BLUE = strip.Color(0, 0, 255);
const uint32_t WHITE = strip.Color(100, 100, 100);
// Colors Favourites
const uint32_t LIGHT_RED = strip.Color(255, 100, 100);
// GetColorFrom Arguments
const uint32_t USE_ARG = 1;

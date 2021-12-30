// Argument Management
#ifndef ARGMANAGEMENT_H
#define ARGMANAGEMENT_H

#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

extern bool loadRGBValues(ESP8266WebServer &server, int *rgb);

#endif
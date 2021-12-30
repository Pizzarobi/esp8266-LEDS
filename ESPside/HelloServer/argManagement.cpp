#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "argManagement.h"

const char *rgbNames[] = {"r", "g", "b"};

// loads RGB values from arguments -- made by Bitlunislab
bool loadRGBValues(ESP8266WebServer &server, int *rgb) {

    // Serial.println("Loading RGB values"); // DEBUG
    bool valid = false;
    for (int i = 0; i < 3; i++)
    {
        // Serial.println("in for Loop"); // DEBUG
        // Serial.println(server.argName(i)); // DEBUG
        // Serial.println(server.arg(rgbNames[i])); // DEBUG
        if (server.hasArg(rgbNames[i]))
        {
            // Serial.println("if hasArg start"); // DEBUG
            int value = server.arg(rgbNames[i]).toInt();
            // Serial.print("Y dis no work?"); // DEBUG
            // Serial.println(value); // DEBUG
            if (value < 0 || value > 255)
            {
                // Serial.println("Illegal value"); // DEBUG
                String message = "Illegal value:\n\n";
                message += rgbNames[i];
                message += "=";
                message += server.arg(rgbNames[i]);
                message += "\nOnly values 0 to 255 are allowed. 0 is off and 255 is 100% lit.";
                server.send(200, "text/plain", message);
                // Serial.println("Illegal Value"); // DEBUG
                return false;
            } else
            {
                // Serial.println("I am in else rn??"); // DEBUG
            }
            rgb[i] = value;
            Serial.print("value: ");
            Serial.println(value);
        }
    }
    // Serial.println("Finished loading RGBs"); // DEBUG
    return true;
}

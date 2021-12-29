#include <ESP8266WebServer.h>
#include "ledConfig.h"

const char *rgbNames[] = {"r", "g", "b"};

// loads RGB values from arguments -- made by Bitlunislab
uint32_t loadRGBValues(ESP8266WebServer &server) {
    uint8_t* rgb;
    bool valid = false;
    for (int i = 0; i < 3; i++)
        if (server.hasArg(rgbNames[i]))
        {
            int value = server.arg(rgbNames[i]).toInt();
            if (value < 0 || value > 255)
            {
                String message = "Illegal value:\n\n";
                message += rgbNames[i];
                message += "=";
                message += server.arg(rgbNames[i]);
                message += "\nOnly values 0 to 255 are allowed. 0 is off and 255 is 100% lit.";
                server.send(200, "text/plain", message);
                return false;
            }
            rgb[i] = value;
        }
    return strip.Color(rgb[1],rgb[2],rgb[3]);
}

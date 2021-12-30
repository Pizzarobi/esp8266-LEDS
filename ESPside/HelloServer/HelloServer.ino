#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Adafruit_NeoPixel.h>

#include "credentials.h"
#include "argManagement.h"
// #include "simpleFunctions.h"

ESP8266WebServer server(80);

const int led = 13;

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

int counter = 0;

void simpleColorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void handleRoot()
{
  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Following functions are available:<br><br>";
  message += "<a href='/colorWipe'>/colorWipe?r=32&g=64&b=32</a> a Color Wipe animation on LEDs<br>";
  message += "<a href='/setleds?r=32&g=64&b=32&fade=1000'>/setleds</a> sets LEDs to the color from arguments: r=<0..255> g=<0..255> b=<0..255><br>";
  message += "<a href='/ledsoff?fade=500'>/ledsoff</a> turns off LEDs<br>";
  message += "<br>Syntax is as follows: http://&ltip>/&ltcommand>?&ltargument1>=&ltvalue1>&&ltargument2>=&ltvalue2>&...<br>";
  message += "You can click on each link to see an example.<br><br>";
  message += "Big Inspiration from <a href='http://youtube.com/bitlunislab'>bitluni</a></body></html>";
  server.send(200, "text/html", message);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void colorWipe()
{
  Serial.println("Starting colorWipe");
  int rgb[] = {0,0,0};
  bool color = loadRGBValues(server, rgb);
  Serial.println(color);
  if(color == true){
    server.send(200, "text/plain", "colorWipe");
    simpleColorWipe(strip.Color(rgb[1],rgb[2],rgb[3]), 50);
  } else
  {
    server.send(400, "text/plain", "wrong args");
  }
  
  Serial.println("Ending colorWipe");
}

void debug()
{
  simpleColorWipe(strip.Color(64,32,32),50);
  Serial.println("Starting debug");
  
  String message = "dis no work.\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  // Serial.println("\n Here are some method pointers  ");
  // Serial.println("\ncolorWipe: ");
  // int (*ptrColor)() = colorWipe;
  // Serial.print((unsigned char *)&ptrColor);
  // Serial.println("\nsetup: ");
  // Serial.print("%p",&setup);
  server.send(200, "text/plain", message);
}

void setup(void)
{
  // pinMode(led, OUTPUT);
  // digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // connect as https://lights.local
  if (MDNS.begin("lights"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  // server.on("/colorWipe", []()
  // {
  //   uint32_t color = loadRGBValues(server, strip);
  //   if(color != false){
  //     server.send(200, "text/plain", "colorWipe");
  //     simpleColorWipe(color, 10, strip);
  //   } else
  //     server.send(400, "text/plain", "wrong args");
  // });

  server.on("/colorWipe", colorWipe);

  server.on("/debug", debug);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  strip.begin();

  // digitalWrite(led, 1);
  counter = 1;
  Serial.println(counter++);
  Serial.print(" in setup");
}

void loop(void)
{
  Serial.println(counter++);
  server.handleClient();
  delay(500);
}

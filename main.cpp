#include <DMXSerial.h>
#include <FastLED.h>

const int LED_PIN = 14; // Replace with your LED pin
#define DMXChannels = 8
const int DMX_CHANNEL_BRIGHTNESS = 1; // Replace with your DMX channel for brightness
const int DMX_CHANNEL_COLOR1_R = 2; // Replace with your DMX channel for color1 red
const int DMX_CHANNEL_COLOR1_G = 3; // Replace with your DMX channel for color1 green
const int DMX_CHANNEL_COLOR1_B = 4; // Replace with your DMX channel for color1 blue
const int NUM_LEDS = 30; // Replace with the number of LEDs in your strip
CRGB leds[NUM_LEDS]; // Array to store LED colors

unsigned long lastReadTime = 0; // Variable to store the last read time
int dmxData[4]; // Array to store the DMX data for brightness and color1

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  DMXSerial.init(DMXReceiver);
  DMXSerial.maxChannel(4);
}

void loop() {
  // Read DMX data once every second
  if (millis() - lastReadTime >= 1000) {
    lastReadTime = millis();
    for (int i = 0; i < 4; i++) {
      dmxData[i] = DMXSerial.read(i + 1);
    }
    
  void printDMXChart(int* dmxData, int DMXChannels) {
    // Assign DMX data to variables
    // int dmxBrightness = dmxData[0];
    // int dmxColor1R = dmxData[1];
    // int dmxColor1G = dmxData[2];
    // int dmxColor1B = dmxData[3];

    // Use DMX data to control LED brightness and color
    // float brightness = (float) dmxBrightness / 255;
    // CRGB color1(dmxColor1R, dmxColor1G, dmxColor1B);
    // fill_gradient(leds, 0, color1, NUM_LEDS, CRGB::Black, CRGB::Black, FORWARD_LIN, NOBLEND);
    // FastLED.show();

    
  }
}



void printDMXChart(int* dmxData, int numChannels) {
  Serial.println("DMX Chart:");
  for (int i = 0; i < numChannels; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(dmxData[i]);
  }
  Serial.println();
}
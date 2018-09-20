#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LEDSPERROW 8
#define MATRIXPIN 6
#define ROWPOTPIN A3
#define HUEPOTPIN A4
#define VALPOTPIN A5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    NUMPIXELS, STRIPPIN, NEO_GRB + NEO_KHZ800); // Led Strip Initialiseren

byte rgb[3];                // max [255,255,255]
float hsv[3];               // max [359.0, 100.0 ,100.0]
int maxBrightness = 40;     // 0 is maximal maxBrightness, 255 just below maximum

// set led and show effect
void setLed(int led) {
    pixels.setPixelColor(led, rgb[0], rgb[1], rgb[2]);
    pixels.show();
}

// set led without showing
void setSingleLed(int led) {
    pixels.setPixelColor(led, rgb[0], rgb[1], rgb[2]);
}

// HSV waarden (360,100,100) uit hsv[] omzetten tot RGB waarden (255) in rgb[]
void HSVtoRGB() {
    float h = hsv[0]; float s = hsv[1]; float v = hsv[2];
    int i; float f, p, q, t;

    h = max(0.0, min(360.0, h)); s = max(0.0, min(100.0, s)); v = max(0.0, min(100.0, v));

    s /= 100; v /= 100;

    if (s == 0) {
        // Achromatic (grey)
        rgb[0] = rgb[1] = rgb[2] = round(v * 255);
        return;
    }

    h /= 60; // sector 0 to 5
    i = floor(h);
    f = h - i; // factorial part of h
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));
    switch (i) {
    case 0:
        rgb[0] = round(255 * v); rgb[1] = round(255 * t); rgb[2] = round(255 * p);
        break;
    case 1:
        rgb[0] = round(255 * q); rgb[1] = round(255 * v); rgb[2] = round(255 * p);
        break;
    case 2:
        rgb[0] = round(255 * p); rgb[1] = round(255 * v); rgb[2] = round(255 * t);
        break;
    case 3:
        rgb[0] = round(255 * p); rgb[1] = round(255 * q); rgb[2] = round(255 * v);
        break;
    case 4:
        rgb[0] = round(255 * t); rgb[1] = round(255 * p); rgb[2] = round(255 * v);
        break;
    default: // case 5:
        rgb[0] = round(255 * v); rgb[1] = round(255 * p); rgb[2] = round(255 * q);
    }
}

void setup() {
    Serial.begin(9600);
    pixels.begin(); // This initializes the NeoPixel library.
    pixels.setBrightness(maxBrightness);
}

void loop() {
    int row = map(analogRead(ROWPOTPIN),0,1023,0,7);
    int hue = map(analogRead(HUEPOTPIN),0,1023,0,365);
    int val = map(analogRead(VALPOTPIN),0,1023,0,100);
    
    Serial.print("row"); Serial.print(" : "); Serial.print(row);
    Serial.print(", hue"); Serial.print(" : "); Serial.print(hue);
    Serial.print(", val"); Serial.print(" : "); Serial.println(val);
}
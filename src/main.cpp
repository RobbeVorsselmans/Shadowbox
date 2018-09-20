#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LEDSPERROW 8
#define MATRIXPIN 6
#define ROWPOTPIN A3
#define HUEPOTPIN A4
#define VALPOTPIN A5

byte rgb[3];                // max [255,255,255]
float hsv[3];               // max [359.0, 100.0 ,100.0]

void setup() {
    Serial.begin(9600);
}

void loop() {
    int row = map(analogRead(ROWPOTPIN),0,1023,0,7);
    int hue = map(analogRead(HUEPOTPIN),0,1023,0,365);
    int val = map(analogRead(VALPOTPIN),0,1023,0,100);
    
    Serial.print("row"); Serial.print(" : "); Serial.println(row);
    Serial.print("hue"); Serial.print(" : "); Serial.println(hue);
    Serial.print("val"); Serial.print(" : "); Serial.println(val);

    delay(500);
}
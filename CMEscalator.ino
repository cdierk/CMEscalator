// the setup function runs once when you press reset or power the board
//#include <SharpIR.h>
//SharpIR sharp(0, 25, 93, 1080);
#include <Adafruit_NeoPixel.h>
#define PIXELPIN 6
#define NUM_PIXELS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  for(int i=0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}
 
void loop() {
  int dis = analogRead(A0);
  int dis2 = analogRead(A1);
  int dis3 = analogRead(A2);
  int dis4 = analogRead(A3);

  int linearized = 6787/(dis - 3) - 4;
  int linearized2 = 6787/(dis2 - 3) - 4;
  int linearized3 = 6787/(dis3 - 3) - 4;
  int linearized4 = 6787/(dis4 - 3) - 4;
  Serial.print(linearized);
  Serial.print(" ");
  Serial.print(linearized2);
  Serial.print(" ");
  Serial.print(linearized3);
  Serial.print(" ");
  Serial.println(linearized4);

  int r = linearized < 10 ? 255 : 0;
  int g = linearized2 < 10 ? 255 : 0;
  int b = linearized3 < 10 ? 255 : 0;
  for(int i=0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}



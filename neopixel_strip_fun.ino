#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 0
#define NUMPIXELS 60
#define SLEEP 50

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  pixels.begin();
  pixels.setBrightness(80);
  pixels.show(); // Initialize all pixels to 'off'
}

int delayVal = 100; // delay for half a second
int red[3] = {255, 0, 0};
int orange[3] = {255, 127, 0};
int yellow[3] = {255, 255, 0};
int green[3] = {0, 255, 0};
int blue[3] = {0, 0, 255};
int indigo[3] = {75, 0, 130};
int violet[3] = {148, 0, 211};
int magenta[3] = {255, 0, 255};
int white[3] = {0,0,0};

int rainbow[7][3] = {{red}, {orange}, {yellow}, {green}, {blue}, {indigo}, {violet}};

void loop() {
  // put your main code here, to run repeatedly:

  everyOther(red, blue);
  delay(SLEEP);
  everyOther(yellow, green);
  delay(SLEEP);
  everyOther(green, blue);
  delay(SLEEP);
  everyOther(blue, yellow);
  delay(SLEEP);
  everyOther(indigo, red);
  delay(SLEEP);
  everyOther(violet, green);
  delay(SLEEP);

  
  openCloseLights(red, blue);

  delay(SLEEP); 
  openCloseLights(yellow, green);
  delay(SLEEP);

  openCloseLights(indigo, red);
  delay(SLEEP);

  openCloseLights(green, blue);
  delay(SLEEP);

  openCloseLights(red, yellow);
  delay(SLEEP);

  openCloseLights(blue, yellow);
  delay(SLEEP);

  openCloseLights(violet, green);
  delay(SLEEP);

  blinkLights();
  delay(SLEEP);

  colorWipe(pixels.Color(255, 0, 0), SLEEP); // Red
  colorWipe(pixels.Color(0, 255, 0), SLEEP); // Green
  colorWipe(pixels.Color(0, 0, 255), SLEEP); // Blue

  rainbowFunc(SLEEP);
  rainbowCycle(SLEEP);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

void rainbowFunc(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void everyOther(int color1[3], int color2[3]){
  
  for(int i=NUMPIXELS; i>-1; i-=2){
    lightUp(i, color1);
    delay(SLEEP);
    lightUp(i+1, color2);
    delay(SLEEP);
  }
}

void openCloseLights(int color1[3], int color2[3]){
  for(int j=0; j<NUMPIXELS; j++)
  {
    lightUp(j, color1);
    delay(SLEEP);
  }

  for(int j=NUMPIXELS; j>-1; j--)
  {
    lightUp(j, color2);
    delay(SLEEP);
  }
}

void blinkLights()
{
  for(int i=0; i<7; i++){
    int color = rainbow[i][3];

    for(int j=0; j<NUMPIXELS; j++){
      pixels.clear();
      delay(SLEEP);
      lightUp(j, color);
    }
  }

  for(int i=0; i<49; i++){
    int color = rainbow[i%7][3];
    pixels.clear();
    pixels.show();
    delay(SLEEP);
    for(int j=0; j<NUMPIXELS; j++){
      lightUp(j, color);
    }
    delay(150);
  }
}

void rainbowLights(){
  for(int i=0; i<NUMPIXELS+7;i+=7){
    lightUp(i, red);
    lightUp(i+1, orange);
    lightUp(i+2, yellow);
    lightUp(i+3, green);
    lightUp(i+4, blue);
    lightUp(i+5, indigo);
    lightUp(i+6, violet);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void lightUp(int charIndex, int color[3])
{
  pixels.setPixelColor(charIndex, color[0], color[1], color[2]);
  pixels.show();
  delay(5);
  //delay(delayVal);
}

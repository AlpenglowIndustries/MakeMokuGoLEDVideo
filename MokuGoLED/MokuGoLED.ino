
/*
This controls 5 addressable LEDs as well as 3 discrete individual R, G, B LEDs
Demo for a video for the Moku:Go logic analyzer by Liquid Instruments, for Make! Magazine.

Some LED strip code is based off an example in Adafruit's Neopixel library.
Other code written by Carrie Sundra, Alpenglow Industries.
Please let us know if you make something with it!  
@alpenglowind on Twitter and Instagram
*/

#include <Adafruit_NeoPixel.h>

#define LED_PIN 4     // pin for the addressable strip of LEDs
#define LED_COUNT 5   // number of LEDs in the strip
#define RED_PIN 3     // pin for the discrete red LED and red channel in discrete RGB LED
#define GRN_PIN 5     // pin for the discrete grn LED and grn channel in discrete RGB LED
#define BLU_PIN 6     // pin for the discrete blu LED and blu channel in discrete RGB LED

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(127); // Set BRIGHTNESS to about 1/2 (max = 255)

  pinMode(RED_PIN, OUTPUT); // Set up discrete RED LED 
  pinMode(GRN_PIN, OUTPUT); // Set up discrete GRN LED 
  pinMode(BLU_PIN, OUTPUT); // Set up discrete BLU LED 

  // Sets LEDs in strip to RGBOP
  strip.setPixelColor(0, strip.Color(255, 0, 0));   //red
  strip.setPixelColor(1, strip.Color(0, 255, 0));   //green
  strip.setPixelColor(2, strip.Color(0, 0, 255));   //blue
  strip.setPixelColor(3, strip.Color(128, 64, 0));  //orange
  strip.setPixelColor(4, strip.Color(96, 0, 128));  //purple
  strip.show();
  delay(1000);

}

// The following code was used to generate the different LED sequences in the video.
// Sections were uncommented and then filmed as needed.

void loop() {
  // put your main code here, to run repeatedly:

// // Pulses discrete LEDs slowly to full on, then full off
  pulse(RED_PIN, 10);
  pulse(GRN_PIN, 10);
  pulse(BLU_PIN, 10);

  // Rainbow fading sequence for discrete LEDs
  // rainbowPulse(10);
  // rainbowPulse(10);

// // Sequences for the WS2812B strip

  // for (int i = 0; i < 3; i++){
  //   // syntax: LED number, strip.Color(red, grn, blu)
  //   strip.setPixelColor(0, strip.Color(255, 0, 0));   //red
  //   strip.setPixelColor(1, strip.Color(0, 255, 0));   //green
  //   strip.setPixelColor(2, strip.Color(0, 0, 255));   //blue
  //   strip.setPixelColor(3, strip.Color(128, 64, 0));  //orange
  //   strip.setPixelColor(4, strip.Color(96, 0, 128));  //purple
  //   strip.show();
  //   delay(1000);

  //   strip.setPixelColor(0, strip.Color(255, 255, 255));
  //   strip.setPixelColor(1, strip.Color(0, 0, 0));
  //   strip.setPixelColor(2, strip.Color(255, 255, 255));
  //   strip.setPixelColor(3, strip.Color(0, 0, 0));
  //   strip.setPixelColor(4, strip.Color(255, 255, 255));
  //   strip.show();
  //   delay(1000);
  // }

  // larson(3, 100);
  // theaterChase(strip.Color(127, 127, 127), 30); // White, half brightness
  // rainbow(3);             // Flowing rainbow cycle along the whole strip
  // theaterChaseRainbow(20); // Rainbow-enhanced theaterChase variant

  // // sets all pixels to one color, varying brightness
  // strip.setPixelColor(0, strip.Color(5, 10, 20));
  // strip.setPixelColor(1, strip.Color(10, 20, 40));   // half brightness
  // strip.setPixelColor(2, strip.Color(20, 40, 80));   // "normal" brightness
  // strip.setPixelColor(3, strip.Color(40, 80, 160));  // twice brightness
  // strip.setPixelColor(4, strip.Color(62, 125, 250));
  // strip.show();
  // delay(3000);


  // //sets all pixels to one color
  // for(int i = 0; i < strip.numPixels(); i++) {               // For each pixel in strip...
  //   strip.setPixelColor(i, strip.Color(20, 40, 80));         //  Set pixel's color (in RAM)
  //   strip.show();                                            //  Update strip to match
  //   delay(200);
  // }

  // // cycles colors between red, green, and blue
  // colorWipe(strip.Color(255,   0,   0), 20); // Red
  // colorWipe(strip.Color(  0, 255,   0), 20); // Green
  // colorWipe(strip.Color(  0,   0, 255), 20); // Blue
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<20; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

// Does a red Larson scanner pattern, ala KITT and Cylons
void larson(int cycles, int wait) {
  strip.clear();
  strip.show();
  delay(50);
  for (int j = 0; j < cycles; j++){
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      strip.show();
      delay(wait);
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
    }
    for (int i = strip.numPixels() - 1; i >= 0; i--) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
      strip.show();
      delay(wait);
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
    }
  }
  strip.clear();
  strip.show();
}

// Pulses individual (discrete) red, green, blue LEDs
void pulse(int pinNum, int wait) {
  for (int i = 0; i <= 255; i++){
    analogWrite(pinNum, i);
    delay(wait);
  }
  for (int i = 255; i >= 0; i--){
    analogWrite(pinNum, i);
    delay(wait);
  }
}

// Helper for below function, fades two discrete LEDs in opposite directions
void fadeTwo (int led1, int led2, int wait){
  int j = 128;
  for (int i = 0; i <= 128; i++) {
    analogWrite(led1, j-i);
    analogWrite(led2, i);
    delay(wait);
  }
}

// Does rainbow fading pattern with discrete red, green, blue LEDs
void rainbowPulse(int wait) {
  analogWrite(RED_PIN, 0);
  analogWrite(GRN_PIN, 0);
  analogWrite(BLU_PIN, 0);
  fadeTwo(RED_PIN, GRN_PIN, wait);
  fadeTwo(GRN_PIN, BLU_PIN, wait);
  fadeTwo(BLU_PIN, RED_PIN, wait);
  analogWrite(RED_PIN, 0);
}

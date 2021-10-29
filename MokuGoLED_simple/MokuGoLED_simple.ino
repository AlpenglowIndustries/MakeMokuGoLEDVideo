
/*
This controls 5 addressable LEDs 
Demo for the Moku:Go logic analyzer
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

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(127); // Set BRIGHTNESS to about 1/2 (max = 255)

  pinMode(RED_PIN, OUTPUT);
  pinMode(GRN_PIN, OUTPUT);
  pinMode(BLU_PIN, OUTPUT);

  // syntax: LED number, strip.Color(red, grn, blu)
  strip.setPixelColor(0, strip.Color(255, 0, 0));   //red
  strip.setPixelColor(1, strip.Color(0, 255, 0));   //green
  strip.setPixelColor(2, strip.Color(0, 0, 255));   //blue
  strip.setPixelColor(3, strip.Color(128, 64, 0));  //orange
  strip.setPixelColor(4, strip.Color(96, 0, 128));  //purple
  strip.show();
  delay(500);

  strip.clear();
  strip.show();
  delay(3000);

}


// The following code was used to generate the different LED sequences in the video.
// Sections were uncommented and then filmed as needed.

void loop() {
  // put your main code here, to run repeatedly:

  // pulse(RED_PIN, 10);
  // pulse(GRN_PIN, 10);
  // pulse(BLU_PIN, 10);

  // rainbowPulse(10);



// //For microscope view, red dim to bright
//   for (int j = 0; j < 5; j++){
//     strip.setPixelColor(j, strip.Color(5, 0, 0));
//     strip.show();
//   }
//   delay(5000);

//   for (int i = 5; i <= 255; i++){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(i, 0, 0));
//       strip.show();
//     }
//     delay(25);
//   } 



// //For microscope view, RGB individual pulse on then off

//   int dtime = 50;
//   for (int i = 5; i <= 25; i++){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(i, 0, 0));
//       strip.show();
//     }
//     delay(dtime);
//   } 

//   for (int i = 25; i > 4; i--){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(i, 0, 0));
//       strip.show();
//     }
//     delay(dtime);
//   } 

//   for (int i = 5; i <= 25; i++){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(0, i, 0));
//       strip.show();
//     }
//     delay(dtime);
//   } 

//   for (int i = 25; i > 4; i--){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(0, i, 0));
//       strip.show();
//     }
//     delay(dtime);
//   } 
 
//   for (int i = 5; i <= 25; i++){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(0, 0, i));
//       strip.show();
//     }
//     delay(dtime);
//   } 

//   for (int i = 25; i > 4; i--){
//     for (int j = 0; j < 5; j++){
//       strip.setPixelColor(j, strip.Color(0, 0, i));
//       strip.show();
//     }
//     delay(dtime);
//   } 

//For microscope view, RGB all on at once
  for (int j = 0; j < 5; j++){
    strip.setPixelColor(j, strip.Color(25, 25, 25));
    strip.show();
  }
  delay(5000);

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

void fadeTwo (int led1, int led2, int wait){
  int j = 255;
  for (int i = 0; i <= 255; i++) {
    analogWrite(led1, j-i);
    analogWrite(led2, i);
    delay(wait);
  }
}

void rainbowPulse(int wait) {
  analogWrite(RED_PIN, 0);
  analogWrite(GRN_PIN, 0);
  analogWrite(BLU_PIN, 0);
  fadeTwo(RED_PIN, GRN_PIN, wait);
  fadeTwo(GRN_PIN, BLU_PIN, wait);
  fadeTwo(BLU_PIN, RED_PIN, wait);
  analogWrite(RED_PIN, 0);
}

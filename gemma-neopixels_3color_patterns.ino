// A few 3-color patterns for GEMMA + 16 pixel NeoPixel Ring
//  by Jessica Nayes

// Notes for loading code onto GEMMA: https://learn.adafruit.com/introducing-gemma/setting-up-with-arduino-ide

#include <Adafruit_NeoPixel.h>

#define PIN 0 // assign constant PIN to the pin D0~ on the Gemma
static int PixelCount = 16 ; // 16-pixel ring, but easy to change for other sizes

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PixelCount, PIN);

//**********************************************************************************************
// MODIFIABLE PARAMETERS - PERSONALIZE YOUR GEMMA NEOPIXELS HERE
//**********************************************************************************************

  //***************************************** CHOOSE COLORS *************************************

  // Colors/color names from https://materialuicolors.co/ - level 500
  
//  uint32_t color1 = 0x03A9F4; // light blue
// uint32_t color1 =  0x3F51B5; // indigo
//  uint32_t color1 = 0xFF9800; // orange
 uint32_t color1 =  0x009688; // teal
  
//  uint32_t color2 = 0xF44336; // red
  uint32_t color2 = 0xE91E63; // pink
//  uint32_t color2 = 0xFFC107 ; // amber

//  uint32_t  bkgrnd = 0x9E9E9E; // grey
  uint32_t bkgrnd = 0x673AB7; // deep purpple

  uint32_t myColors_patt0[] = 
    {color1, color1, color1, color1, 
    bkgrnd, bkgrnd, bkgrnd, bkgrnd, 
    color2, color2, color2, color2,
    bkgrnd, bkgrnd, bkgrnd, bkgrnd};

  //********************************** CHOOSE PATTERN **********************************

    // 0: Bowtie twist
    // 1: Flag merge
    // 2: Drop fill
    // 3: Random twister
    
    uint8_t  myPattern = 3; // ← Change this value to your desired pattern
    
  //********************************** CHOOSE SPEED ********************************************
  
    // 0: FAST
    // 1: MEDIUM
    // 2: SLOW 
    // 3: EXTRA SLOW (good for debugging!)

    uint8_t mySpeed = 1; // ← Change this value to your desired speed


//**********************************************************************************************
// UTILITY VARIABLES
//**********************************************************************************************
  
  uint32_t delayTime; // Utility variable for timing
//  uint32_t color = 0xffffff; // default white
  uint8_t positionInPattern = 0; // Current position of moving pattern
//  uint8_t positionInColorChart = 0; // Current position within colour chart

//**********************************************************************************************
// SETUP
//**********************************************************************************************
void setup() // setup() runs once
{ 
  pixels.begin();
  randomSeed(analogRead(0));
  
  pixels.setBrightness(20); // 1/5 brightness to save battery
  
    switch (mySpeed) // where the speed timings are set
    { 
      case 0:
          delayTime = 50;
      break;

      case 1:
          delayTime = 150;
      break;
      
      case 2:
          delayTime = 300;
      break;

      default: // if mySpeed is set to 3 (or any integer other than 0, 1, or 2)
          delayTime = 750;
      break;
    }  
    
}

//**********************************************************************************************
// LOOP THAT WILL RUN OVER AND OVER
//**********************************************************************************************
void loop() // after setup() runs, loop() will run over and over as long as the GEMMA has power
{
  switch(myPattern) {

    //**********************************************************************************************
    // Case 0: Bowtie twist
    //**********************************************************************************************

    case 0:
    
      static int16_t a = 0; // the 'start' position each time the code loops
      static int16_t b = 4; // how far to 'bounce'
      static boolean turn = true; // to flip direction of rotation

      for (uint8_t pixel_index = 0; pixel_index < PixelCount; pixel_index++)  //Sets color to each pixel position
      {        
        pixels.setPixelColor((pixel_index + a) % PixelCount, myColors_patt0[pixel_index]);
      }

      if (turn) {
        a++; // rotate start pixel counter-clockwise
        if (a == b) {
          turn = false;
        }
      } else {
        a--; // rotate start pixel clockwise
        if (a == 0) {
          turn = true;
        }
      }
      
      pixels.show();
      delay(delayTime);
      
      break;
      
      
    //**********************************************************************************************
    // Case 1: Flag merge
    //**********************************************************************************************
    
    case 1:
    
      static int16_t c = 0; // the 'start' position each time the code loops

      for (uint8_t pixel_index = 0; pixel_index < PixelCount; pixel_index += 2)  
      {        
        pixels.setPixelColor(pixel_index + 1, bkgrnd); // Sets background color on every other pixel
        pixels.setPixelColor(pixel_index, color2); // Sets color 2 on every other pixel
      }

      pixels.setPixelColor(c, color1); // Sets color 1 on every other pixel
      pixels.setPixelColor(PixelCount - c, color1); // Sets color 1 on every other pixel


      c += 2; // color 1's pixel motion
      c %= PixelCount;
      
      pixels.show();
      delay(delayTime);
      
      break;

    //**********************************************************************************************
    // Case 2: Drop fill - WORK IN PROGRESS!!!!!
    //**********************************************************************************************
    
    case 2:
    
      static int16_t d = 0; // the 'start' position each time the code loops
      static int16_t e = 0; // ...


//      uint32_t myColors_patt2[PixelCount];
//      for (uint8_t pixel_index = 0; pixel_index < PixelCount; pixel_index ++)  
//      {
//        myColors_patt2[pixel_index] = bkgrnd; // Sets background color on every pixel
//      }
//
//      for (uint8_t pixel_index = 0; pixel_index < PixelCount; pixel_index ++)  
//      {        
//        pixels.setPixelColor(pixel_index, bkgrnd); // Sets background color on every pixel
//      }
//
//      pixels.setPixelColor(d, color1); // Sets color 1 on first pixel
////      pixels.setPixelColor(PixelCount +1 - d, color2); // Sets color 2 on every other pixel
//
//
//      d += 2; // color 1's pixel motion
//      d %= PixelCount;
      
      pixels.show();
      delay(delayTime);
      
      break;

    //**********************************************************************************************
    // Case 3: Random twister
    //**********************************************************************************************
    
    case 3:
      
      static int16_t f = 0; // the 'start' position each time the code loops
      static int16_t g = 0; // track along magnitude
      static int16_t magnitude =  10; // how far to twist
      static boolean twist = true; // to flip direction of rotation

      for (int8_t pixel_index = 0; pixel_index < PixelCount; pixel_index ++) {
        
        int temp = (pixel_index + f) % PixelCount;
        if (temp < 0 ) temp += PixelCount;
        
        if (pixel_index % 4 == 0) {
          pixels.setPixelColor(temp, color1);
        } 
        else if (pixel_index % 4 == 1) {
          pixels.setPixelColor(temp, color2); 
        }
          else {
          pixels.setPixelColor(temp, bkgrnd); 
        }
      }

      if (twist) {
        f++; // rotate start pixel counter-clockwise
      } else {
        f--; // rotate start pixel clockwise
      }
      
      g++; // track twist 'position'

      if (g > magnitude) {
        
        if (twist) {
          twist = false;
        } else {
          twist = true;
        }
        
        g = 0; 
        magnitude = random(3, PixelCount * 3);
      }
      
      pixels.show();
      delay(delayTime);
      
      break;

  } // end of pattern switcher
}

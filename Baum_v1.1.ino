#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#define LED_PIN_TREE     10
#define NUM_LEDS_TREE    13
#define LED_PIN_STAR     11
#define NUM_LEDS_STAR    15
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

extern const TProgmemPalette16 ForestTree_p PROGMEM;
CRGB ledsTree[NUM_LEDS_TREE];
CRGB ledsStar[NUM_LEDS_STAR];


//int ledSideBySideStar[3][7] =  {{ 6, 5, 4, 3, 2, 1, 0},
//                                { 8, 9,10,11,12,13,14},
//                                { 7,-1,-1,-1,-1,-1,-1}};



int ledSideBySideTree[3][6] =  {{ 12,11, 0, 1, 2, 3},
                                { 10, 9, 8, 7, 6, 5},
                                {  4,-1,-1,-1,-1,-1,}};
                                
int ledSideBySideStar[3][7] =  {{  0, 1, 2, 3, 4, 5, 6},
                                { 14,13,12,11,10, 9, 8},
                                { 7,-1,-1,-1,-1,-1,-1}};

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPaletteTree;
TBlendType    currentBlendingTree;

CRGBPalette16 currentPaletteStar;
TBlendType    currentBlendingStar;

uint8_t brightnessTree = 255;
uint8_t brightnessStar = 255;
uint8_t UPDATES_PER_SECOND = 5;

int Switch_1;
int Switch_2;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN_TREE, COLOR_ORDER>(ledsTree, NUM_LEDS_TREE).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN_STAR, COLOR_ORDER>(ledsStar, NUM_LEDS_STAR).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(0);
    
    currentPaletteTree = RainbowStripeColors_p;
    currentBlendingTree = NOBLEND;
    currentPaletteStar = LavaColors_p;
    currentBlendingStar = NOBLEND;

    pinMode(4, INPUT_PULLUP); 
    pinMode(5, INPUT_PULLUP); 
    pinMode(6, INPUT_PULLUP); 
    pinMode(7, INPUT_PULLUP); 
    pinMode(8, INPUT_PULLUP); 
    pinMode(9, INPUT_PULLUP); 
    Serial.begin(9600);
}


void loop()
{
    static uint8_t startIndexTree = 0;
    static uint8_t startIndexStar = 0;
    
    Switch_1 = !digitalRead(7) * 3 + !digitalRead(8) * 2 + !digitalRead(9) * 1;
    Switch_2 = !digitalRead(4) * 3 + !digitalRead(5) * 2 + !digitalRead(6) * 1;

  switch (Switch_1) {
  case 1:
    brightnessTree = 50; 
    brightnessStar = 5;
    break;
  case 2:
    brightnessTree = 100; 
    brightnessStar = 20;
    break;
  case 3:
    brightnessTree = 255; 
    brightnessStar = 100;
    break;
  default:
    brightnessTree = 255; 
    brightnessStar = 255;
}

 switch (Switch_2) {
  case 1:
    UPDATES_PER_SECOND = 20;
    currentPaletteTree = ForestTree_p;
    currentBlendingTree = LINEARBLEND;
    currentPaletteStar = LavaColors_p;
    currentBlendingStar = NOBLEND;
    break;
  case 2:
    UPDATES_PER_SECOND = 10;
    currentPaletteTree = ForestColors_p;
    currentBlendingTree = LINEARBLEND;
    currentPaletteStar = CloudColors_p;
    currentBlendingStar = LINEARBLEND;
    break;
  case 3:
    UPDATES_PER_SECOND = 10;
    currentPaletteTree = RainbowStripeColors_p;
    currentBlendingTree = NOBLEND;
    currentPaletteStar = PartyColors_p;
    currentBlendingStar = NOBLEND;
    break;
  default:
    UPDATES_PER_SECOND = 20;
    currentPaletteTree = ForestTree_p;
    currentBlendingTree = LINEARBLEND;
    currentPaletteStar = LavaColors_p;
    currentBlendingStar = NOBLEND;
}
 
   FastLED.setBrightness(255);
    
    startIndexTree = startIndexTree + 1; /* motion speed */
    FillLEDsFromPaletteColorsTree(startIndexTree);
    FastLED.show();
    
    for( int i = 0; i < 2; i++) {
      startIndexStar = startIndexStar + 1; /* motion speed */
      FillLEDsFromPaletteColorsStar(startIndexStar);
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND / 2);
    }
 
}

void FillLEDsFromPaletteColorsTree( uint8_t colorIndex)
{   
    ledsTree[ledSideBySideStar[2][0]] = ColorFromPalette( currentPaletteTree, colorIndex, brightnessTree, currentBlendingTree);
    colorIndex += 3;
    for( int i = 0; i <= 5; i++) {//        Serial.print("i=");
        ledsTree[ledSideBySideTree[0][i]] = ColorFromPalette( currentPaletteTree, colorIndex, brightnessTree, currentBlendingTree);
        ledsTree[ledSideBySideTree[1][i]] = ColorFromPalette( currentPaletteTree, colorIndex, brightnessTree, currentBlendingTree);
        colorIndex += 5;
    }
}

void FillLEDsFromPaletteColorsStar( uint8_t colorIndex)
{   
    ledsStar[ledSideBySideStar[2][0]] = ColorFromPalette( currentPaletteStar, colorIndex, brightnessStar, currentBlendingStar);
    colorIndex += 3;
    for( int i = 0; i <= 6; i++) {
        ledsStar[ledSideBySideStar[0][i]] = ColorFromPalette( currentPaletteStar, colorIndex, brightnessStar, currentBlendingStar);
        ledsStar[ledSideBySideStar[1][i]] = ColorFromPalette( currentPaletteStar, colorIndex, brightnessStar, currentBlendingStar);
        colorIndex += 3;
    }
}

const TProgmemPalette16 ForestTree_p PROGMEM =
{
    CRGB::Green,
    CRGB::Green, // 'white' is too bright compared to red and blue
    CRGB::DarkSlateGray,
    CRGB::Green,
    
    CRGB::Green,
    CRGB::Green,
    CRGB::GreenYellow,
    CRGB::Green,
    
    CRGB::Green,
    CRGB::Green,
    CRGB::Olive,
    CRGB::Green,
    
    CRGB::Green,
    CRGB::Green,
    CRGB::YellowGreen,
    CRGB::Green
};

#define FASTLED_INTERNAL
#include <FastLED.h>

// LED Strip configs (number of leds on a "strip")
#define NUM_LEDS 1050
#define SPINE_NUMLEDS 282
#define M1_TALED_NUMLEDS 96
#define M1_UALED_NUMLEDS 96
#define M2_TALED_NUMLEDS 96
#define M2_UALED_NUMLEDS 96
#define M3_TALED_NUMLEDS 96 
#define M3_UALED_NUMLEDS 96
#define M4_TALED_NUMLEDS 96
#define M4_UALED_NUMLEDS 96

// LED Signal Pins
#define SPINE_LED_PIN 0
#define M1_TALED_PIN  8
#define M1_UALED_PIN  7
#define M2_TALED_PIN  1
#define M2_UALED_PIN  2
#define M3_TALED_PIN  4
#define M3_UALED_PIN  3
#define M4_TALED_PIN  6
#define M4_UALED_PIN  5

// not sure what this does, but effects don't work without it
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// IO Setup
#define RX_pin 10
int pulse;

// LED Setup
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 25
#define FRAMES_PER_SECOND 120
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

void setup() {
  // put your setup code here, to run once:
  //------------------Flight-Control-Pin------------------//
  // Setup the PWM Recieve pin
  pinMode(RX_pin, INPUT);

  //----------------------LED-Setup-----------------------//
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,SPINE_LED_PIN,COLOR_ORDER>(leds, SPINE_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M1_TALED_PIN,COLOR_ORDER>(leds, M1_TALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M1_UALED_PIN,COLOR_ORDER>(leds, M1_UALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M2_TALED_PIN,COLOR_ORDER>(leds, M2_TALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M2_UALED_PIN,COLOR_ORDER>(leds, M2_UALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M3_TALED_PIN,COLOR_ORDER>(leds, M3_TALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M3_UALED_PIN,COLOR_ORDER>(leds, M3_UALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M4_TALED_PIN,COLOR_ORDER>(leds, M4_TALED_NUMLEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,M4_UALED_PIN,COLOR_ORDER>(leds, M4_UALED_NUMLEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds,NUM_LEDS,10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(gHue + random8(64),200,255);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read the PWM pulse
  pulse = pulseIn(RX_pin, HIGH);
  Serial.println(pulse);

  // Mode 5 (Demo Confetti)
  if((pulse > 1200) && (pulse <= 1250)){
    confetti();
    // send the 'leds' array out to the actual LED strip
    FastLED.show();  
    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND);
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  }
}

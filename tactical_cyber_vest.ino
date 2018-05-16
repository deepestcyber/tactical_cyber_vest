#include "FastLED.h"
#include "Wire.h"

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

typedef uint16_t ledaddr_t;

#define LED_ADDR(pin, led) ((pin<<8) | (led&0xff))
#define LED_TO_PIN(addr) ((addr>>8) & 0xff)
#define LED_TO_LED(addr) (addr & 0xff)

const uint8_t LED_PIN_COUNT = 4;
const uint8_t LED_LED_COUNT = 28;
const uint8_t LED_PINS[LED_PIN_COUNT] = {2, 3, 4, 5,};

const uint8_t I2C_ADDR = 4;

ledaddr_t upleft[] = {
  LED_ADDR(0,3),
  LED_ADDR(0,2),
  LED_ADDR(0,1),
  LED_ADDR(0,0),
  LED_ADDR(1,0),
  LED_ADDR(1,1),
  LED_ADDR(1,2),
  // snip
  LED_ADDR(1,3),
  LED_ADDR(1,4),
  LED_ADDR(1,5),
  LED_ADDR(1,6),
  LED_ADDR(1,7),
  LED_ADDR(1,8),
  LED_ADDR(1,9),
  LED_ADDR(1,10),
  LED_ADDR(1,11),
  LED_ADDR(1,12),
  LED_ADDR(1,13),
  LED_ADDR(1,14),
  LED_ADDR(1,15),
  LED_ADDR(1,16),
  LED_ADDR(1,17),
  LED_ADDR(1,18),
  LED_ADDR(1,19),
  LED_ADDR(1,20),
  LED_ADDR(1,21),
  LED_ADDR(1,22),
  LED_ADDR(1,23),
};

ledaddr_t loleft[] = {
  LED_ADDR(0, 4),
  LED_ADDR(0, 5),
  LED_ADDR(0, 6),
  LED_ADDR(0, 7),
  LED_ADDR(0, 8),
  LED_ADDR(0, 9),
  LED_ADDR(0, 10),
  LED_ADDR(0, 11),
  LED_ADDR(0, 12),
};

ledaddr_t upright[] = {
  LED_ADDR(3, 6),
  LED_ADDR(3, 5),
  LED_ADDR(3, 4),
  LED_ADDR(3, 3),
  LED_ADDR(3, 2),
  LED_ADDR(3, 1),
  LED_ADDR(3, 0),
  LED_ADDR(2, 0),
  LED_ADDR(2, 1),
  LED_ADDR(2, 2),
  LED_ADDR(2, 3),
  LED_ADDR(2, 4),
  LED_ADDR(2, 5),
  LED_ADDR(2, 6),
  LED_ADDR(2, 7),
  LED_ADDR(2, 8),
  LED_ADDR(2, 9),
  LED_ADDR(2, 10),
  LED_ADDR(2, 11),
  LED_ADDR(2, 12),
  LED_ADDR(2, 13),
  LED_ADDR(2, 14),
  LED_ADDR(2, 15),
  LED_ADDR(2, 16),
  LED_ADDR(2, 17),
  LED_ADDR(2, 18),
  LED_ADDR(2, 19),
  LED_ADDR(2, 20),
};
ledaddr_t loright[] = {
  LED_ADDR(3, 7),  
  LED_ADDR(3, 8),  
  LED_ADDR(3, 9),  
  LED_ADDR(3, 10),  
  LED_ADDR(3, 11),  
  LED_ADDR(3, 12),  
  LED_ADDR(3, 13),  
  LED_ADDR(3, 14),  
  LED_ADDR(3, 15),  
};

ledaddr_t top[] = {
  // left
  LED_ADDR(1,23),
  LED_ADDR(1,22),
  LED_ADDR(1,21),
  LED_ADDR(1,20),
  LED_ADDR(1,19),
  LED_ADDR(1,18),
  LED_ADDR(1,17),
  LED_ADDR(1,16),
  LED_ADDR(1,15),
  LED_ADDR(1,14),
  LED_ADDR(1,13),
  LED_ADDR(1,12),
  LED_ADDR(1,11),
  LED_ADDR(1,10),
  LED_ADDR(1,9),
  LED_ADDR(1,8),
  LED_ADDR(1,7),
  LED_ADDR(1,6),
  LED_ADDR(1,5),
  LED_ADDR(1,4),
  LED_ADDR(1,3),
  LED_ADDR(1,2),
  LED_ADDR(1,1),
  LED_ADDR(1,0),
  LED_ADDR(0,0),
  LED_ADDR(0,1),
  LED_ADDR(0,2),
  LED_ADDR(0,3),
  // right
  LED_ADDR(3, 6),
  LED_ADDR(3, 5),
  LED_ADDR(3, 4),
  LED_ADDR(3, 3),
  LED_ADDR(3, 2),
  LED_ADDR(3, 1),
  LED_ADDR(3, 0),
  LED_ADDR(2, 0),
  LED_ADDR(2, 1),
  LED_ADDR(2, 2),
  LED_ADDR(2, 3),
  LED_ADDR(2, 4),
  LED_ADDR(2, 5),
  LED_ADDR(2, 6),
  LED_ADDR(2, 7),
  LED_ADDR(2, 8),
  LED_ADDR(2, 9),
  LED_ADDR(2, 10),
  LED_ADDR(2, 11),
  LED_ADDR(2, 12),
  LED_ADDR(2, 13),
  LED_ADDR(2, 14),
  LED_ADDR(2, 15),
  LED_ADDR(2, 16),
  LED_ADDR(2, 17),
  LED_ADDR(2, 18),
  LED_ADDR(2, 19),
  LED_ADDR(2, 20),
};

CRGB leds[LED_PIN_COUNT][LED_LED_COUNT];

#define BRIGHTNESS          80
#define FRAMES_PER_SECOND  120

void setup() {
  delay(2000); // 2 second delay for recovery

  Wire.begin(I2C_ADDR);
  Wire.onReceive(i2c_receive);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, 2, COLOR_ORDER>(leds[0], LED_LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(leds[1], LED_LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds[2], LED_LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds[3], LED_LED_COUNT).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t pos = 0;
uint8_t circ = 0;

uint8_t hue = 0;

void i2c_receive(int count) {
  char c = 0;
  while ( Wire.available() ) {
    c = Wire.read();
  }
  hue = c;
}

void loop() {
  receive();

  sensors();
  
  write_leds();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

  EVERY_N_MILLISECONDS( 10 ) { 
    pos++;
    pos &= 63;
  }
  return;
  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 10 ) { 
    pos++;
//    if ( pos >= 28 ) {
//      pos = 0;
//    }
  }
}


void receive() {
}


void sensors() {  
}

void write_leds() {
  CHSV col = CHSV(hue, 255, 255);
  fill_solid(leds[0], 28, col);
  fill_solid(leds[1], 28, col);
  fill_solid(leds[2], 28, col);
  fill_solid(leds[3], 28, col);
  return;
  single_pos(upleft, 28, pos);
  single_pos(loleft, 9, pos);
  single_pos(upright, 28, pos);
  single_pos(loright, 9, pos);
}

void single_pos(ledaddr_t line[], uint8_t len, uint8_t pos) {
  for ( int i=0; i<len; i++) {
    ledaddr_t led = line[i];
    if ( i==pos ) {
      set_led(led, CRGB::Blue);
    } else {
      set_led(led, CRGB::Black);
    }
  }
}

void run1() {
  grow(upleft, 28, pos/256.0f);
  grow(loleft, 9, pos/256.0f);
  grow(upright, 28, pos/256.0f);
  grow(loright, 9, pos/256.0f);
}


void set_led(ledaddr_t addr, CRGB colour) {
  leds[LED_TO_PIN(addr)][LED_TO_LED(addr)] = colour;
}


void grow(ledaddr_t line[], uint8_t led_num, float progress) {
  progress = max(0.0f, min(1.0f, progress));
  uint8_t active = led_num * progress;

  for ( int i=0; i<led_num; i++ ) {
    ledaddr_t led = line[i];
    if ( i==active ) {
      set_led(led, CRGB::Blue);
    } else {
      set_led(led, CRGB::Black);
    }
  }
}


void rainbow() 
{
  // FastLED's built-in rainbow generator
//  fill_rainbow( leds[0], NUM_LEDS, gHue, 7);
//  fill_rainbow( leds[1], NUM_LEDS, gHue, 7);
//  fill_rainbow( leds[2], NUM_LEDS, gHue, 7);
//  fill_rainbow( leds[3], NUM_LEDS, gHue, 7);
}



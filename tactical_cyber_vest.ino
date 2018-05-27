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
  LED_ADDR(3, 6),
  LED_ADDR(3, 5),
  LED_ADDR(3, 4),
  LED_ADDR(3, 3),
  LED_ADDR(3, 2),
  LED_ADDR(3, 1),
  LED_ADDR(3, 0),
  LED_ADDR(2, 20),
  LED_ADDR(2, 19),
  LED_ADDR(2, 18),
  LED_ADDR(2, 17),
  LED_ADDR(2, 16),
  LED_ADDR(2, 15),
  LED_ADDR(2, 14),
  LED_ADDR(2, 13),
  LED_ADDR(2, 12),
  LED_ADDR(2, 11),
  LED_ADDR(2, 10),
  LED_ADDR(2, 9),
  LED_ADDR(2, 8),
  LED_ADDR(2, 7),
  LED_ADDR(2, 6),
  LED_ADDR(2, 5),
  LED_ADDR(2, 4),
  LED_ADDR(2, 3),
  LED_ADDR(2, 2),
  LED_ADDR(2, 1),
  LED_ADDR(2, 0),
  //
  LED_ADDR(0,3),
  LED_ADDR(0,2),
  LED_ADDR(0,1),
  LED_ADDR(0,0),
  LED_ADDR(1,0),
  LED_ADDR(1,1),
  LED_ADDR(1,2),
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

ledaddr_t bottom[] = {
  LED_ADDR(3, 15),  
  LED_ADDR(3, 14),  
  LED_ADDR(3, 13),  
  LED_ADDR(3, 12),  
  LED_ADDR(3, 11),  
  LED_ADDR(3, 10),  
  LED_ADDR(3, 9),  
  LED_ADDR(3, 8),  
  LED_ADDR(3, 7),  
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

CRGB leds[LED_PIN_COUNT][LED_LED_COUNT];

#define BRIGHTNESS          80
#define FRAMES_PER_SECOND  120

void setup() {
  delay(500); // 2 second delay for recovery

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

// i2c callback
void i2c_receive(int count) {
  uint8_t c = 0;
  while ( Wire.available() ) {
    c = Wire.read();
    eval_cmd(c);
  }
}

uint8_t mode = 0;

void eval_cmd(uint8_t cmd) {
  switch ( cmd ) {
    case 100:
      mode = 0;
      start_mode();
      break;
    case 101:
      mode = 1;
      start_mode();
      break;
    case 102:
      mode = 2;
      start_mode();
      break;
    case 103:
      mode = 3;
      start_mode();
      break;
    case 104:
      mode = 4;
      start_mode();
      break;
    case 105:
      mode = 5;
      start_mode();
      break;
    case 200:
      FastLED.setBrightness(0);
      break;
    case 201:
      FastLED.setBrightness(3);
      break;
    case 202:
      FastLED.setBrightness(9);
      break;
    case 203:
      FastLED.setBrightness(27);
      break;
    case 204:
      FastLED.setBrightness(81);
      break;
    case 205:
      FastLED.setBrightness(243);
      break;
  }
}

void loop() {
  receive();

  sensors();

  EVERY_N_MILLISECONDS(10) {
    update_leds();
  }

  write_leds();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

//  EVERY_N_MILLISECONDS( 10 ) { 
//    pos++;
//  }
//  return;
  
  // insert a delay to keep the framerate modest
//  FastLED.delay(1000/FRAMES_PER_SECOND); 
  // do some periodic updates
//  EVERY_N_MILLISECONDS( 10 ) { 
//    pos++;
//    if ( pos >= 28 ) {
//      pos = 0;
//    }
//  }
}

void start_mode() {
  switch (mode) {
    case 0:
      i_pulse();
      break;
    case 1:
      i_circle();
      break;
    case 2:
      i_runner();
      break;
    case 3:
      i_rainbow();
      break;
    case 4:
      i_black();
      break;
  }
}
void update_leds() {
  switch (mode) {
    case 0:
      u_pulse();
      break;
    case 1:
      u_circle();
      break;
    case 2:
      u_runner();
      break;
    case 3:
      u_rainbow();
      break;
    case 4:
      u_black();
      break;
  }
}
void write_leds() {
  switch (mode) {
    case 0:
      w_pulse();
      break;
    case 1:
      w_circle();
      break;
    case 2:
      w_runner();
      break;
    case 3:
      w_rainbow();
      break;
    case 4:
      w_black();
      break;
  }
}

uint8_t s0=0;
uint8_t s1=0;
ledaddr_t *sline=NULL;
uint8_t slen = 0;
void i_circle() {
  s1=0;
}
void w_circle() {
  if ( s1==0 ) {
    fill_solid(upleft, sizeof(upleft)/2, CRGB::Blue);
    fill_solid(upright, sizeof(upright)/2, CRGB::Black);
    fill_solid(loleft, sizeof(loleft)/2, CRGB::Black);
    fill_solid(loright, sizeof(loright)/2, CRGB::Black);
  } else if ( s1==1 ) {
    fill_solid(upleft, sizeof(upleft)/2, CRGB::Black);
    fill_solid(upright, sizeof(upright)/2, CRGB::Blue);
    fill_solid(loleft, sizeof(loleft)/2, CRGB::Black);
    fill_solid(loright, sizeof(loright)/2, CRGB::Black);
  } else if ( s1==2 ) {
    fill_solid(upleft, sizeof(upleft)/2, CRGB::Black);
    fill_solid(upright, sizeof(upright)/2, CRGB::Black);
    fill_solid(loleft, sizeof(loleft)/2, CRGB::Black);
    fill_solid(loright, sizeof(loright)/2, CRGB::Blue);
  } else if ( s1==3 ) {
    fill_solid(upleft, sizeof(upleft)/2, CRGB::Black);
    fill_solid(upright, sizeof(upright)/2, CRGB::Black);
    fill_solid(loleft, sizeof(loleft)/2, CRGB::Blue);
    fill_solid(loright, sizeof(loright)/2, CRGB::Black);
  }
}
void u_circle() {
  EVERY_N_MILLISECONDS(50) {
    s1++;
    if ( s1>3 ) {
      s1=0;
    }
  }
}

void i_pulse() {
  s1=0;
}
void w_pulse() {
  single_pos(upleft, sizeof(upleft)/2, s1);
  single_pos(upright, sizeof(upright)/2, s1);
  single_pos(loleft, sizeof(loleft)/2, s1);
  single_pos(loright, sizeof(loright)/2, s1);
}
void u_pulse() {
  EVERY_N_MILLISECONDS(5) {
    s1++;
    s1 &= 63;
  }
}

// runner --
void i_runner() {
  s0 = 3;
  s1 = 0;
  runner_pick(s1);
}
void runner_pick(uint8_t last) {
  last &= 3;
  s0 = (last + random8(3) + 1) % 4;
  switch ( s0) {
    case 0:
      sline = upleft;
      slen = sizeof(upleft)/2;
      break;
    case 1:
      sline = upright;
      slen = sizeof(upright)/2;
      break;
    case 2:
      sline = loleft;
      slen = sizeof(loleft)/2;
      break;
    default:
      sline = loright;
      slen = sizeof(loright)/2;
      break;
  }
}
void w_runner() {
  fill_solid(top, sizeof(top)/2, CRGB::Black);
  fill_solid(bottom, sizeof(bottom)/2, CRGB::Black);
  set_led(sline[s1], CRGB::Blue);
}
void u_runner() {
  if ( s0&4 == 0 ) {
    // up:
    if ( s1 < slen-1 ) {
      s1++;
    } else {
      s1--;
      s0|=4;
    }
  } else {
    // down:
    if ( s1 == 0 ) {
      // pick next branch:
      runner_pick(s0&4);
    } else {
      s1--;
    }
  }
}

// RAINBOW -- colours over all leds
void i_rainbow() {
  s1=0;
}
void w_rainbow() {
  fill_rainbow( top, sizeof(top)/2, s1, 7);
  fill_rainbow( bottom, sizeof(bottom)/2, s1, 14);
}
void u_rainbow() {
  s1+=1;
}

// BLACK
void i_black() {}
void w_black() {
  fill_solid(top, sizeof(top)/2, CRGB::Black);
  fill_solid(bottom, sizeof(bottom)/2, CRGB::Black);
}
void u_black() {}

void receive() {
  
}


void sensors() {  
}

int numAllLeds;
uint8_t h = 0;
uint8_t bright=0;

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

int pos=0;
void run1() {
  grow(upleft, 28, pos/256.0f);
  grow(loleft, 9, pos/256.0f);
  grow(upright, 28, pos/256.0f);
  grow(loright, 9, pos/256.0f);
}


void set_led(ledaddr_t addr, const struct CRGB& color) {
  leds[LED_TO_PIN(addr)][LED_TO_LED(addr)] = color;
}

void set_led(ledaddr_t addr, const struct CHSV& color) {
  leds[LED_TO_PIN(addr)][LED_TO_LED(addr)] = color;
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



//-- FASTLEDFOO
void fill_rainbow(ledaddr_t line[], int numToFill, uint8_t initialhue, uint8_t deltahue) {
  CHSV hsv;
  hsv.hue = initialhue;
  hsv.val = 255;
  hsv.sat = 240;
  for ( int i=0; i<numToFill; i++) {
    set_led(line[i], hsv);
    hsv.hue += deltahue;
  }
}

void fill_solid(ledaddr_t line[], int numToFill, const struct CRGB& color) {
  for ( int i=0; i<numToFill; i++ ) {
    set_led(line[i], color);
  }
}

void fill_solid(ledaddr_t line[], int numToFill, const struct CHSV& color) {
  for ( int i=0; i<numToFill; i++ ) {
    set_led(line[i], color);
  }
}

void nscale8(ledaddr_t line[], uint16_t num_leds, uint8_t scale) {
  for ( uint16_t i=0; i<num_leds; i++ ) {
    ledaddr_t addr = line[i];
    leds[LED_TO_PIN(addr)][LED_TO_LED(addr)].nscale8(scale);
  }
}


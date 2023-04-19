
#define FASTLED_ALLOW_INTERRUPTS 0
#include <Setup_DMX.h>
#include <FastLED.h>
#include <Potis.h>




FASTLED_USING_NAMESPACE

#define DATA_PINBCK         26
#define NUM_BCK             150
#define COLOR_ORDERBCK      GRB

#define DATA_PINSTRIPE1     25
#define NUM_STRIPE1         14
#define COLOR_ORDERSTRIPE1  RGB

#define DATA_PINSTRIPE2     17
#define NUM_STRIPE2         17
#define COLOR_ORDERSTRIPE2  RGB

#define LED_TYPESTRIPE      WS2812B
#define LED_TYPE            WS2812B

//////////////////////////////////////////////////////////////////////////

//Constructor for Potentiometer CLASS Object with wired PINS! First Poti is NR : 0
Potentiometer pots(2, 4, 35, 34, 36, 39);

//////////////////////////////////////////////////////////////////////////

CRGB bckleds[NUM_BCK];
CRGB stripeone[NUM_STRIPE1];
CRGB stripetwo[NUM_STRIPE2];

///////////////////////////////////////////////////////////////////////////

//Pallets 

DEFINE_GRADIENT_PALETTE (heatmap_one) {
    0,   255,   255,   255,   //black
  128, 255,   0,   0,   //red
  200, 255,   0,   0,   //bright yellow
  255, 255, 255, 255    //full white 
};

CRGBPalette16 PalRed = heatmap_one;

DEFINE_GRADIENT_PALETTE (heatmap_two) {
    0,   185,   0,   31,   //Lila
  128, 42, 21,   85,   //Blue
  255, 185, 0, 31    //Lila
};

CRGBPalette16 Palfunk = heatmap_two;




CRGBPalette16 purplePalette = CRGBPalette16 (
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::DarkViolet,
    
    CRGB::Magenta,
    CRGB::Magenta,
    CRGB::Linen,
    CRGB::Linen,
    
    CRGB::Magenta,
    CRGB::Magenta,
    CRGB::DarkViolet,
    CRGB::DarkViolet,

    CRGB::DarkViolet,
    CRGB::DarkViolet,
    CRGB::Linen,
    CRGB::Linen
);


CRGBPalette16 PalPurple = purplePalette;

/////////////////////////////////////////////////////////////////////////////////////////////////////

bool Potimode = false;
int value1;

void getCommand(){

  Potimode = digitalRead(12);

  if (Potimode){ //Der Fall: Poti
    value1 = pots.getValue(0);

  }
  else { //Der Fall: DMX
    value1 = dmxdata[1];
  }
}
void setup() {
  
  delay( 3000); // 3 second delay for boot recovery, and a moment of silence

  Serial.begin(9600);
  pots.init();
  initDMX();
  
  FastLED.addLeds<LED_TYPE,DATA_PINBCK,COLOR_ORDERBCK>(bckleds, NUM_BCK)
        .setCorrection( TypicalSMD5050 );
  FastLED.addLeds<LED_TYPESTRIPE,DATA_PINSTRIPE1,COLOR_ORDERSTRIPE1>(stripeone, NUM_STRIPE1)
        .setCorrection( TypicalSMD5050 );
  FastLED.addLeds<LED_TYPESTRIPE,DATA_PINSTRIPE2,COLOR_ORDERSTRIPE2>(stripetwo, NUM_STRIPE2)
        .setCorrection( TypicalSMD5050 );


  pinMode(12, INPUT_PULLDOWN);
}

int random_X;

void loop()
{
dmx_event_t packet;

EVERY_N_MILLISECONDS(100)
{
pots.readAll();
if (xQueueReceive(queue, &packet, DMX_PACKET_TIMEOUT_TICK)) {

  if (packet.status == DMX_OK) 
  dmx_read_packet(dmxPort, dmxdata, packet.size);
  }
}
getCommand();

//fill_palette(bckleds, NUM_BCK, 0 , 255 / NUM_BCK, Palfunk, value1, LINEARBLEND);

//fill_palette(stripeone, NUM_STRIPE1, paletteIndex1, 255 / NUM_STRIPE1, PalPurple, 255, LINEARBLEND);
fill_solid(bckleds,NUM_BCK,CHSV(value1,255,255));
//fill_solid(stripeone,NUM_STRIPE1,CRGB::Black);
fill_solid(stripetwo,NUM_STRIPE2,CRGB::OrangeRed);



EVERY_N_MILLISECONDS(200)
{
  random_X = random(0,NUM_STRIPE1); 
  stripeone[random_X-1] = ColorFromPalette(PalPurple,random8(),255,LINEARBLEND);
  
}

fadeToBlackBy(stripeone, NUM_STRIPE1, 1);

FastLED.show();

}





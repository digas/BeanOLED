/*********************************************************************
 * This is an example for our Monochrome OLEDs based on SSD1306 drivers
 * 
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/category/63_98
 * 
 * This example is for a 128x64 size display using SPI to communicate
 * 4 or 5 pins are required to interface
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada  for Adafruit Industries.  
 * BSD license, check license.txt for more information
 * All text above, and the splash screen must be included in any redistribution
 *********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   3
#define OLED_CLK   5
#define OLED_DC    A0
#define OLED_CS    2
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
 #define OLED_DC     6
 #define OLED_CS     7
 #define OLED_RESET  8
 Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
 */

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_WIDTH  46
#define LOGO16_GLCD_HEIGHT 46

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ 
	0x0F, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, //     ##################################    
	0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, //   ######################################  
	0x78, 0x00, 0x00, 0x00, 0x07, 0x80, //  ####                                #### 
	0x60, 0x00, 0x00, 0x00, 0x01, 0x80, //  ##                                    ## 
	0xC0, 0x00, 0x00, 0x00, 0x01, 0xC0, // ##                                     ###
	0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                      ##
	0xC0, 0x07, 0xFC, 0x00, 0x00, 0xC0, // ##           #########                  ##
	0xC0, 0x01, 0xC3, 0x80, 0x00, 0xC0, // ##             ###    ###               ##
	0xC0, 0x01, 0x80, 0xE0, 0x00, 0xC0, // ##             ##       ###             ##
	0xC0, 0x01, 0x80, 0x60, 0x00, 0xC0, // ##             ##        ##             ##
	0xC0, 0x01, 0x80, 0x70, 0x00, 0xC0, // ##             ##        ###            ##
	0xC0, 0x01, 0x80, 0x30, 0x00, 0xC0, // ##             ##         ##            ##
	0xC0, 0x01, 0x80, 0x38, 0x00, 0xC0, // ##             ##         ###           ##
	0xC0, 0x01, 0x80, 0x38, 0x00, 0xC0, // ##             ##         ###           ##
	0xC0, 0x01, 0x80, 0x38, 0x00, 0xC0, // ##             ##         ###           ##
	0xC0, 0x01, 0x80, 0x38, 0x00, 0xC0, // ##             ##         ###           ##
	0xC0, 0x01, 0x80, 0x30, 0x00, 0xC0, // ##             ##         ##            ##
	0xC0, 0x01, 0x80, 0x30, 0x00, 0xC0, // ##             ##         ##            ##
	0xC0, 0x01, 0x80, 0x70, 0x00, 0xC0, // ##             ##        ###            ##
	0xC0, 0x01, 0x80, 0xE0, 0x00, 0xC0, // ##             ##       ###             ##
	0xC0, 0x01, 0x83, 0xC0, 0x00, 0xC0, // ##             ##     ####              ##
	0xC0, 0x07, 0xFE, 0x00, 0x00, 0xC0, // ##           ##########                 ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                      ##
	0xC0, 0x00, 0x00, 0x00, 0x00, 0xC0, // ##                                      ##
	0xC0, 0x3F, 0x3E, 0x0F, 0x00, 0xC0, // ##        ######  #####     ####        ##
	0xC0, 0x0C, 0x0C, 0x06, 0x00, 0xC0, // ##          ##      ##       ##         ##
	0xC0, 0x0C, 0x0C, 0x04, 0x00, 0xC0, // ##          ##      ##       #          ##
	0xC0, 0x06, 0x0C, 0x04, 0x00, 0xC0, // ##           ##     ##       #          ##
	0xC0, 0x06, 0x06, 0x08, 0x00, 0xC0, // ##           ##      ##     #           ##
	0xC0, 0x07, 0x0E, 0x08, 0x00, 0xC0, // ##           ###    ###     #           ##
	0xC0, 0x03, 0x0F, 0x08, 0x00, 0xC0, // ##            ##    ####    #           ##
	0xC0, 0x03, 0x0B, 0x10, 0x00, 0xC0, // ##            ##    # ##   #            ##
	0xC0, 0x01, 0x93, 0x10, 0x00, 0xC0, // ##             ##  #  ##   #            ##
	0xC0, 0x01, 0x93, 0x90, 0x00, 0xC0, // ##             ##  #  ###  #            ##
	0xC0, 0x01, 0xD1, 0xA0, 0x00, 0xC0, // ##             ### #   ## #             ##
	0xC0, 0x00, 0xE1, 0xE0, 0x00, 0xC0, // ##              ###    ####             ##
	0xC0, 0x00, 0xE0, 0xC0, 0x00, 0xC0, // ##              ###     ##              ##
	0xC0, 0x00, 0xC0, 0xC0, 0x00, 0xC0, // ##              ##      ##              ##
	0xC0, 0x00, 0x40, 0xC0, 0x00, 0xC0, // ##               #      ##              ##
	0xC0, 0x00, 0x40, 0x00, 0x03, 0xC0, // ##               #                    ####
	0xC0, 0x00, 0x00, 0x00, 0x07, 0xC0, // ##                                   #####
	0xC0, 0x00, 0x00, 0x00, 0x0E, 0x00, // ##                                  ###   
	0x60, 0x00, 0x00, 0x00, 0x1C, 0x00, //  ##                                ###    
	0x70, 0x00, 0x00, 0x00, 0x18, 0x00, //  ###                               ##     
	0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, //   ###################################     
	0x0F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, //     #################################     
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

static int8_t temp = 0;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(500);

  // draw a bitmap icon and 'animate' movement
  display.clearDisplay();
  display.display();
  //testdrawbitmap(logo16_glcd_bmp , LOGO16_GLCD_HEIGHT , LOGO16_GLCD_WIDTH);
}

void loop() {
//  // Sleep for a second before reading the temperature again 
	uint16_t accelZ;
	accelZ = Bean.getAccelerationZ();
  
    int8_t newTemp = Bean.getTemperature();
  
  if ( newTemp != temp )
  {
    temp = newTemp;
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10,0);
    display.clearDisplay();
    display.print("  DIGASWISE");
    display.setTextSize(1);
    display.setCursor(19,10);
    String sAux = String(temp);
    display.println("T: " + sAux + "c");
    display.drawBitmap(78, 19,  logo16_glcd_bmp, 46, 46, 1);
    display.display();
  }
  
  Bean.sleep(2000);
  display.clearDisplay(); 

 
uint16_t b = abs(accelZ)/ 4;
Bean.setLed((uint8_t)0, 0, b);
Bean.sleep(2000);


}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];

  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;

    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    display.display();
    delay(200);

    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
  }
}


void textoscroll(void) 
{
  int8_t newTemp = Bean.getTemperature();
  //int8_t newTemp = Bean.getTemperature();
  
  if ( newTemp != temp )
  {
    temp = newTemp;
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10,0);
    display.clearDisplay();
    display.print("  DIGASWISE");
    display.setTextSize(1);
    display.setCursor(19,10);
    String sAux = String(temp);
    display.println("Temp: " + sAux + "c");
    display.drawBitmap(20, 20,  logo16_glcd_bmp, 46, 46, 1);
    display.display();
    display.startscrollright(0x00, 0x0F);
    delay(500);
    display.stopscroll();
    delay(500);
    display.startscrollleft(0x00, 0x0F);
    delay(500);
    display.stopscroll();
    delay(500);    
    display.stopscroll();
  }
}



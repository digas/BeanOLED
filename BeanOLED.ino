/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
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
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
}


void loop() {

 textoscroll();
 // Sleep for a second before reading the temperature again  
 Bean.sleep(1000);  
 display.clearDisplay(); 
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
  display.setTextSize(2);
  display.setCursor(5,10);
  String sAux = String(temp);
  display.println("Temp: " + sAux + "c");
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

void testscrolltext(void) {
    int8_t newTemp = Bean.getTemperature();
 
 if ( newTemp != temp )
 {
   temp = newTemp;
   
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,0);
  display.clearDisplay();
  display.println("Temp is ");
  display.println(temp);
  display.println(" Celsius");
  display.display();
 }
  

  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
}


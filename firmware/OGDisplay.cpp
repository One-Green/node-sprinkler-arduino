#include "Arduino.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include "OGDisplay.h"

#define TFT_CS   15
#define TFT_RST  4
#define TFT_DC   2
#define TFT_MOSI 23
#define TFT_SCLK 18
// not required
// #define TFT_MISO 12

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// color definitions
extern uint16_t  Display_Color_Black        = 0x0000;
extern uint16_t  Display_Color_Blue         = 0x001F;
extern uint16_t  Display_Color_Red          = 0xF800;
extern uint16_t  Display_Color_Green        = 0x07E0;
extern uint16_t  Display_Color_Cyan         = 0x07FF;
extern uint16_t  Display_Color_Magenta      = 0xF81F;
extern uint16_t  Display_Color_Yellow       = 0xFFE0;
extern uint16_t  Display_Color_White        = 0xFFFF;


void DisplayLib::initR(){

	tft.initR(INITR_BLACKTAB);
	tft.fillScreen(ST7735_BLACK);
	delay(500);
	// large block of text
	tft.fillScreen(ST7735_BLACK);
	drawtext("Screen initialised",ST7735_WHITE);

}

void DisplayLib::drawtext(char *text, uint16_t color) {
	tft.setCursor(0, 0);
	tft.setTextColor(color);
	tft.setTextWrap(true);
	tft.print(text);
}
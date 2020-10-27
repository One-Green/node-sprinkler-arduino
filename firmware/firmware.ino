
#include "OGDisplay.h"

DisplayLib displayLib;

#define TFT_CS   15
#define TFT_RST  4
#define TFT_DC   2
#define TFT_MOSI 23
#define TFT_SCLK 18
// not required
// #define TFT_MISO 12



void setup(void) {
	displayLib.initR();
}

void loop() {

}

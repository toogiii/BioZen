#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define NAVY 0x000F /* 0, 0, 128 */
#define DARKGREEN 0x03E0 /* 0, 128, 0 */
#define DARKCYAN 0x03EF /* 0, 128, 128 */
#define MAROON 0x7800 /* 128, 0, 0 */
#define PURPLE 0x780F /* 128, 0, 128 */
#define OLIVE 0x7BE0 /* 128, 128, 0 */
#define LIGHTGREY 0xC618 /* 192, 192, 192 */
#define DARKGREY 0x7BEF /* 128, 128, 128 */
#define ORANGE 0xFD20 /* 255, 165, 0 */
#define GREENYELLOW 0xAFE5 /* 173, 255, 47 */

#define BUTTON_X 40
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 3
#define TEXT_TCOLOR MAGENTA

#define TEXT_LEN 12
char textfield[TEXT_LEN+1] = "";
uint8_t textfield_i = 0;

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 100
#define TS_MAXX 920
#define TS_MINY 70
#define TS_MAXY 900

#define STATUS_X 10
#define STATUS_Y 65

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button buttons[15];
char buttonlabels[15][5] = {"Send", "Clr", "End", "1", "2", "3", "4", "5", "6", "7",
"8", "9", "*", "0", "#" };
uint16_t buttoncolors[15] = {DARKGREEN, DARKGREY, RED, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, ORANGE, BLUE, ORANGE};


void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("USING Adafruit 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.4\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); 
  Serial.print("x");
  Serial.println(tft.height());
 
  tft.reset();
 
  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  } else if (identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101) {
    identifier=0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F(" #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
  } 

  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(BLACK);

  for (uint8_t row=0; row<5; row++) {
    for (uint8_t col=0; col<3; col++) {
       buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X), BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), BUTTON_W, BUTTON_H, WHITE, buttoncolors[col + row * 3], WHITE, buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
       buttons[col + row * 3].drawButton();
    }
  }

  tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, WHITE);
 
}

void status(const __FlashStringHelper *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

void status(char *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop() {
  
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  for (uint8_t b = 0; b < 15; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      Serial.print("Pressing: "); 
      Serial.println(b);
      buttons[b].press(true);
    } else {
      buttons[b].press(false);
    }
  }

  for (uint8_t b = 0; b < 15; b++) {
    if (buttons[b].justReleased()) {
      Serial.print("Released: ");
      Serial.println(b);
      buttons[b].drawButton();
    }
    if (buttons[b].justPressed()) {
      buttons[b].drawButton(true);

      if (b >= 3) {
        if (textfield_i < TEXT_LEN) {
          textfield[textfield_i] = buttonlabels[b][0];
          textfield_i++;
          textfield[textfield_i] = 0;
        }
      }

      if (b == 1) {
        textfield[textfield_i] = 0;
        if (textfield > 0) {
          textfield_i--;
          textfield[textfield_i] = ' ';
        }
      }

      Serial.println(textfield);
      tft.setCursor(TEXT_X + 2, TEXT_Y + 10);
      tft.setTextColor(TEXT_TCOLOR, BLACK);
      tft.setTextSize(TEXT_TSIZE);
      tft.print(textfield);
      
      if (b == 2) {
        status(F("Hanging up"));
      }
      if (b == 0) {
        status(F("Calling"));
        Serial.print("Calling ");
        Serial.print(textfield);
      }
      
      delay(100);
    }
  }
  
}

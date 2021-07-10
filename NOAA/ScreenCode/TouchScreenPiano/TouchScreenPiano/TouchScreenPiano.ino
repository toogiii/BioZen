#include <Adafruit_GFX.h> // Adafruit graphics core library
#include <MCUFRIEND_kbv.h> // library for the display
#include "TouchScreen_kbv.h"> // library for touch screen
#include "Key.h"// declares Key class for keyboard keys and includes methods 'contains' and 'draw'
#include "Button.h" // declares Button class for octave buttons and includes methods 'contains' and 'draw'

#define TS_MINX 85
#define TS_MAXX 950
#define TS_MINY 90
#define TS_MAXY 910
#define MINPRESSURE 50

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

// definitions for display screen and touch screen
TouchScreen_kbv ts = TouchScreen_kbv(XP, YP, XM, YM, 300);
TSPoint_kbv p;
MCUFRIEND_kbv tft;

// variable for octave - beginning octave is octave 4, range is 0 to 7
int octave = 4;

// pin definition and duration for playing music notes 
#define buzzerPin A5
int duration = 100;

// constant for number of keys to be drawn on screen 
const int keyCount = 13;

// Key is the class or data type declared in header file Key.h. 
// The following is an array of key captions, the note frequencies of the first octave, beginning at low C
// and the x coordinate used for drawing each key on the TFT screen.

Key keys[] = 
{
  Key ("C",KEY_WHITE,33,0),
  Key ("D",KEY_WHITE,37,60),
  Key ("E",KEY_WHITE,41,120),
  Key ("F",KEY_WHITE,44,180),
  Key ("G",KEY_WHITE,49,240),
  Key ("A",KEY_WHITE,55,300),
  Key ("B",KEY_WHITE,62,360),
  Key ("C",KEY_WHITE,65,420),
  Key ("C#",KEY_BLACK,35,45),
  Key ("D#",KEY_BLACK,39,105),
  Key ("F#",KEY_BLACK,46,165),
  Key ("G#",KEY_BLACK,52,285),
  Key ("A#",KEY_BLACK,58,345),
};

// Button is the class or data type for drawing the plus and minus octave buttons and checking for 
// octave changes. This class is defined in header file Button.h
// Values specified indicate caption ( '+' or '-') and the x and y coordinates of the octave buttons.  

Button minusButton = Button("   -", 20, 250); 
Button plusButton = Button("   +", 280, 250);

void setup(void)
{
  //Serial.begin(9600);
  tft.reset();
  tft.begin(tft.readID());
  tft.setTextSize(4); // text size for key and octave captions
  tft.setRotation(1); // draws screen in 'landscape' orientation 
  tft.fillScreen(TFT_BLACK);
    
  for (int i = 0; i<keyCount; i++) // draws keys
  {
    keys[i].draw(tft);
  }
  
  tft.setCursor (230, 260);
  tft.println(octave);
  minusButton.draw(tft); // draws minus octave button
  plusButton.draw(tft);  // draws plus octave button
}

void loop()
{ 
 /* ___________________________________________________________________________
    |                                                                         |
    |  BLOCK ONE - GET CURRENT TOUCH STATE, READ TOUCH DATA, AND PLAY A NOTE  |
    |_________________________________________________________________________|*/
    
    do {
    delay(20);
     } while (ts.pressure() < MINPRESSURE);
     readTouch();
     // Read note if finger is on the screen
    // check which note was touched and play that note
   for (int i = 0; i < keyCount; i++)
    {
     if (keys[i].contains (p.x,p.y))
      {
        playNote((keys[i].m_frequency) * (1 << (octave - 1))); 
        // Musical frequencies increase by a factor of 2 to the power n where n is the selected octave number. 
        // To make this frequency adjustment we use the bitshift operator ">>" 
        // The power function 'pow()' could be used to achieve the same result.
        }
     }
  
  /*  _________________________________________________________________________
     |                                                                         |
     |  BLOCK TWO - DETECT SCREEN TOUCH STATE AND CHANGE OCTAVE                |
     |_________________________________________________________________________|*/
  // State change is monitored to ensure a single touch, no matter the duration, 
  // only changes the octave once (i.e. it avoids jumping octaves).
  // Button change is processed when finger is lifted.
    
    if (minusButton.contains(p.x,p.y))
     {
      shiftMinus();
      delay(100);
     }
     if (plusButton.contains(p.x,p.y))
     {
      shiftPlus();
      delay(100);
     }
  } // END loop()


// FUNCTION DEFINITIONS

void shiftMinus()
{
  octave -=1;
  if (octave < 1)
  {
    octave = 1;
  }
  tft.setCursor (230, 260);
  tft.fillRect (230,260,40,50,TFT_BLACK);
  tft.println (octave);
}

void shiftPlus()
{
  octave +=1;
  if (octave >7)
  {
    octave = 7;
  }
  tft.setCursor (230,260);
  tft.fillRect(230,260,40,50,TFT_BLACK);
  tft.println (octave);
}

void playNote(int f) 
{
  tone(buzzerPin, f, duration);
}
void readTouch() {
  p = ts.getPoint();
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
}
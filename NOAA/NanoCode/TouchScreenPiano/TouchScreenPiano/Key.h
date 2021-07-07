/* ______________________________________________________________________________________________________________________
  |  Key.h is the header file that declares the Key class. This class is used to draw keyboard keys on the touch screen  |
  |  and to check if a key has been touched.                                                                             |
  |  Key.h declares these data members: caption, color, frequency, and the coordinates, and dimensions used for drawing  |
  |  keys and checking for key touch.                                                                                    |
  |  (The implementation of methods draw and contains is defined in Key.cpp.)                                            |
  |______________________________________________________________________________________________________________________| 
   */
   
#ifndef Key_h
#define Key_h

#include "Arduino.h"
#include <MCUFRIEND_kbv.h>


enum Keycolor {KEY_WHITE, KEY_BLACK}; // enum creates a data type 'Keycolor' with 2 values as indicated

class Key // defines data type 'Key'
{
  public:
    String m_caption; // member variables are designated with 'm_' prefix
    Keycolor m_color;
    int m_frequency;
    int m_x; // x and y coordinates set the start point for drawing keys
    int m_y;  
    int m_width; // width of key
    int m_height; // height of key

  Key(String keyCaption, Keycolor color, int keyFrequency, int keyx); // prototype of constructor for 'Key' data type
  
  
  boolean contains(int tx, int ty);// method (or "member function") declaration.
                                   // Its implementation (in Key.cpp) will check to see if a key has been pressed.
  
  void draw(MCUFRIEND_kbv); // A second method declaration, it passes the parameter "Adafruit_ILI9341" 
                                   // to draw() and gives it the local name "tft". 
};

#endif

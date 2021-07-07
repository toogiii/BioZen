// Key.cpp
/*   ___________________________________________________________________________________________
    |   The class 'Key' has a constructor for the keyboard keys, and two methods (also called   |
    |   'member functions'): draw and contains.                                                 |
    |   Key.cpp defines the implementation of these methods.                                    |
    |___________________________________________________________________________________________|  */
 
#include "Key.h"
#include <MCUFRIEND_kbv.h>

// constructor for keyboard keys
Key::Key(String keyCaption, Keycolor color, int keyFrequency, int keyx) 
{
  m_caption = keyCaption;
  m_color  = color;
  m_frequency = keyFrequency;
  m_x = keyx;
  if (m_color == KEY_WHITE)
  {
  m_width = 60 ;
  m_height = 130 ;
  m_y = 100; 
  }
  else // else key is black
  {
  m_width = 35 ;
  m_height = 110;
  m_y = 0;
  }
}


// The 'contains' method checks to see if a given point that has been 
// touched on the screen is inside the key - i.e. if the key has been pressed.
boolean Key::contains(int tx, int ty)
{
  if ((tx > m_x) && (tx < m_x + m_width))
  {
    if ((ty > m_y) && (ty < m_y + m_height))
    {
      return true;  // Test point lies inside the key
    }
  }
  return false;  // Test point lies outside the key
}


// the 'draw' method checks the key colour and draws the key 
void Key::draw(MCUFRIEND_kbv tft) 
{
  if (m_color == KEY_WHITE)
  {
    // screen background is black, so drawing white keys with 4 unit inset produces white keys with outline in black
    tft.fillRect(m_x + 4, 0, m_width - 4, m_height - 4 + 80, TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(m_x + 20, m_y+50);
    tft.println(m_caption);
  } 

  if (m_color == KEY_BLACK)
  {
    tft.fillRect(m_x, m_y, m_width, m_height, TFT_BLACK); // black keys do not have captions
  }
}

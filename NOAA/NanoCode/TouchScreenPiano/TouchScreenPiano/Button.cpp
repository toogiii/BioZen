/*   _____________________________________________________________________________________________
    |   The class Button' has a constructor for the octave buttons, and two methods (also called  |
    |   member functions): draw and contains.                                                     |
    |   This .cpp file contains the code that implements these functions.                         |
    |_____________________________________________________________________________________________|  */
 

#include "Button.h"
#include <MCUFRIEND_kbv.h>

// constructor for plus and minus octave buttons
Button::Button(String buttonCaption, int xcoord, int ycoord)
{  
  m_caption = buttonCaption; // i.e. '+' or '-'
  m_color = TFT_BLUE;
  m_x = xcoord;
  m_y = ycoord;
  m_width = 180;
  m_height = 50;  
}

// The member function 'boolean contains(int tx, int ty)' checks to see if a given point is within 
// one of the Octave buttons - i.e. if the button has been pressed.
boolean Button::contains(int tx, int ty)
{
  if ((tx > m_x) && (tx < m_x + m_width))
  {
    if ((ty > m_y) && (ty < m_y + m_height))
    {
      return true;  // point lies inside the plus or minus octave button
    }
  }
  return false;  // point lies outside the plus or minus octave button
}

// The member function 'draw(Adafruit_IL9341 tft' draws the octave + and - buttons
void Button::draw(MCUFRIEND_kbv tft)
{ 
  tft.fillRoundRect(m_x, m_y, m_width, m_height, 5, TFT_BLUE);
  tft.drawRoundRect(m_x, m_y, m_width, m_height, 5, TFT_WHITE);
  tft.setCursor(m_x + 10 , m_y + 10);
  tft.setTextColor(TFT_WHITE);
  tft.println(m_caption);
}

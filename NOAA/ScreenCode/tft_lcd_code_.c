/*
 
 this is a project
 where i have made custom
 buttons used to change colour
 of background
 
*/

#include <Adafruit_GFX.h> // main graphics library
#include <TouchScreen.h> // supporting library
#include <MCUFRIEND_kbv.h> // main tft library

const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9488
int TS_LEFT=858,TS_RT=142,TS_TOP=757,TS_BOT=104; // values after doing lcd clibration. you can upload the clibration example from one of three libraries used here and then copy paste the values here


#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// initialising the colours used in code

#define BLACK   0x0000 
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(){
   uint16_t ID = tft.readID();
   if (ID == 0xD3) ID = 0x9488; // if your LCD have another ID then paste it.     tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.fillRect(250 , 75 , 100, 100 , BLUE );
    tft.fillRect(140,75,100,100,RED);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.setCursor(165,115);
    tft.print("RED");
    tft.setCursor(265,115);
    tft.print("BLUE");
    tft.setTextColor(WHITE);
    tft.setCursor(200,235);
    tft.print("BLACK");
    tft.drawRect(250 , 75 , 100, 100 , WHITE );
    tft.drawRect(140,75,100,100,WHITE);
    tft.drawRect(195,200,100,100,WHITE);
    
    
  }
void loop(){
  int button_on = 0;
  int pixel_x, pixel_y;   
  TSPoint p = ts.getPoint();
  if (p.z > ts.pressureThreshhold) {
    
    pixel_x = map(p.y, TS_LEFT=757, TS_RT=104, 0, 480);// mapping the values
    pixel_y = map(p.x, TS_TOP=142, TS_BOT=858, 0, 320);
  
       // if the LCD sens the touch in following coordinates, then the                 condition will be executed 
  
       if(pixel_x>250 && pixel_x<350 && pixel_y>75 && pixel_y<175 ){
      
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    
    tft.fillScreen(BLUE);
    tft.drawRect(250 , 75 , 100, 100 , BLACK );
    tft.fillRect(140,75,100,100,RED);
    tft.drawRect(251 , 76 , 98, 98 , WHITE );
    tft.drawRect(140,75,100,100,WHITE);
    tft.fillRect(195,200,100,100,BLACK);
    tft.drawRect(195,200,100,100,BLACK);
    tft.drawRect(196,201,100,100,WHITE);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.setCursor(165,115);
    tft.print("RED");
    tft.setCursor(265,115);
    tft.print("BLUE");
    tft.setTextColor(WHITE);
    tft.setCursor(200,235);
    tft.print("BLACK");
   
   }
   
       if(pixel_x>140 && pixel_x<240 && pixel_y>75 && pixel_y<175 ){
      
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    tft.fillScreen(RED);
    tft.fillRect(250 , 75 , 100, 100 , BLUE );
    tft.drawRect(140,75,100,100,BLACK);
    tft.drawRect(250 , 75 , 100, 100 , WHITE );
    tft.drawRect(141,76,98,98,WHITE);
    tft.fillRect(195,200,100,100,BLACK);  
    tft.drawRect(195,200,100,100,BLACK);
    tft.drawRect(196,201,100,100,WHITE);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.setCursor(165,115);
    tft.print("RED");
    tft.setCursor(265,115);
    tft.print("BLUE");
    tft.setTextColor(WHITE);
    tft.setCursor(200,235);
    tft.print("BLACK");
   }  
   
     if(pixel_x>195 && pixel_x<295 && pixel_y>200 && pixel_y<300 ){
      
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    tft.fillScreen(BLACK);
    tft.fillRect(250 , 75 , 100, 100 , BLUE );
    tft.fillRect(140,75,100,100,RED);
    tft.drawRect(195,200,100,100,WHITE);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.setCursor(165,115);
    tft.print("RED");
    tft.setCursor(265,115);
    tft.print("BLUE");
    tft.setTextColor(WHITE);
    tft.setCursor(200,235);
    tft.print("BLACK");
  }
 }
}      

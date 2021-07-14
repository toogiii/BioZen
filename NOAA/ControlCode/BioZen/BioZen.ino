#include <Adafruit_NeoPixel.h>

#define RED 5
#define GREEN 3
#define BLUE 6

#define PUMP 2 
#define VALVE 3

#define NeoPixel A1

#define NUMPIXELS 26 

Adafruit_NeoPixel pixels(NUMPIXELS, NeoPixel, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;

bool rain, mist, sun, lighting, rainbow = false;

bool day = true;
bool sunrise, sunset, night = false; 

void setup() {
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  pixels.begin();
  pixels.setBrightness(255);
}

void serialLoop(){
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    char input = data.charAt(0);
    switch(input){
      case '3': rain = true; sun, mist, lighting = false; break;
      case '2': mist = true; rain, sun, lighting = false; break;
      case '1': sun = true; lighting, mist, rain = false; break;
      case '4': lighting, rain = true; sun, mist = false; break;
      case '6': sunrise = true; day,sunset,night = false; break;
      case '9': day = true; sunrise,sunset,night = false; break;
      case '7': sunset = true; day,sunrise,night = false; break;
      case '8': night = true; day,sunset,sunrise = false; break;
      case 'r': rainbow = true; rain = true; day,sunset,sunrise,lighting,mist,rain,sun = false; break;
    }
  }
}

int time = 12;
void SunClock(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 3600000) {
    previousMillis = currentMillis;
    time++;
    if(time >= 25){
      time = 1;
    }
      pixels.clear();
      if(time > 20 || time < 6){
        pixels.setPixelColor(time, pixels.Color(255, 100, 1));
        pixels.setPixelColor(time+1, pixels.Color(255, 100, 1));
      }else{
        pixels.setPixelColor(time, pixels.Color(255, 255, 255));
        pixels.setPixelColor(time+1, pixels.Color(255, 255, 255));
      }
  }
  pixels.show();
}

void Lighting(){
  int brightint = random(40, 100);
  double brightness = brightint/100.0;
  int durration = random(200, 600);
  for(int i = 0; i < random(0,5); i++){
    analogWrite(RED, 125*brightness);
    analogWrite(GREEN, 249*brightness);
    analogWrite(BLUE, 255*brightness);
    delay(durration);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    delay(durration/2);
  }
}

void Sunrise(){
  analogWrite(RED, 255);
  analogWrite(GREEN, 80);
  analogWrite(BLUE, 10);
}

void Day(){
  analogWrite(RED, 255);
  analogWrite(GREEN, 125);
  analogWrite(BLUE, 10);
}

void Sunset(){
  analogWrite(RED, 255);
  analogWrite(GREEN, 50);
  analogWrite(BLUE, 2);
}

void Night(){
  analogWrite(RED, 255);
  analogWrite(GREEN, 220);
  analogWrite(BLUE, 230);
}

void CloudLight(){
  if(sunrise){
    Sunrise();
  }else if(day){
    Day();
  }else if(sunset){
    Sunset();
  }else if(night){
    Night();
  }
}

void Mist(){
  if(mist){
    digitalWrite(PUMP, HIGH);
  }else{
    digitalWrite(PUMP, LOW);
  }
}

void Rain(){
  if(rain){
    mist = true;
    digitalWrite(VALVE, HIGH);
  }else{
    mist = false;
    digitalWrite(VALVE, LOW);
  }
}

void loop() {
  serialLoop();
  SunClock();
  CloudLight();
  Mist();
  Rain();
  Lighting();
  
}

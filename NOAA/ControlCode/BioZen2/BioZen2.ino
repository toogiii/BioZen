 #include <Adafruit_NeoPixel.h>

#define RED 5
#define GREEN 3
#define BLUE 6

#define PUMP 0
#define VALVE A0

#define NeoPixel A1

#define NUMPIXELS 26 


#define enPin 8
#define dirPin 10
#define stepPin 9


Adafruit_NeoPixel pixels(NUMPIXELS, NeoPixel, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = -4000000;
unsigned long previousMillis2 = 0;

bool rain, mist, sun, lighting, rainbow = false;



const int stepsPerRevolution = 200;


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
  
  pinMode(VALVE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  pixels.begin();
  pixels.setBrightness(255);

   pinMode(stepPin, OUTPUT);
   pinMode(dirPin, OUTPUT);
   pinMode(enPin, OUTPUT);
   
   digitalWrite(enPin, HIGH);
}

int sunsetting = 4;

void serialLoop(){
  int data = Serial.readString().toInt();
  Serial.println(data);
  lighting = false;
  switch(data){
    case 1: rain = true; lighting, rainbow = false; break;
    //case 'm':  mist = !mist; break;
    case 2: rain, lighting, rainbow = false; break;
    case 3: lighting, rain = true; rainbow = false;  break;
    case 4: sunsetting = 1; break;
    case 5: sunsetting = 2; break;
    case 6: sunsetting = 3; break;
    case 7: sunsetting = 4; break;
    case 8: digitalWrite(enPin, !digitalRead(enPin)); break;
    case 9: rainbow, rain = true;  lighting = false;  break;
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
  if(lighting){
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
  switch(sunsetting){
    case 1: Sunrise();break;
    case 2: Day();break;
    case 3: Sunset();break;
    case 4: Night(); break;
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

bool up = true;

void Oss(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis2 >= 30000){
    previousMillis2 = currentMillis;
    up = !up;
    if(up){
      digitalWrite(dirPin, LOW);
    }else{
      digitalWrite(dirPin, HIGH);
    }
  }
   digitalWrite(stepPin, HIGH);
   delay(3);
   digitalWrite(stepPin, LOW);
   delay(3);
}


void Rainbow(){
  
  if(rainbow){
    rain = true;
    pixels.setBrightness(100);
    for(int i = 0; i < NUMPIXELS; i++){
      switch(i%7){
        case 1:  pixels.setPixelColor(i, pixels.Color(255, 0, 0)); break;
        case 2:  pixels.setPixelColor(i, pixels.Color(255, 128, 0)); break;
        case 3:  pixels.setPixelColor(i, pixels.Color(255, 255, 0)); break;
        case 4:  pixels.setPixelColor(i, pixels.Color(0, 255, 0)); break;
        case 5:  pixels.setPixelColor(i, pixels.Color(0, 255, 255)); break;
        case 6:  pixels.setPixelColor(i, pixels.Color(127, 0, 255)); break;
        case 0:  pixels.setPixelColor(i, pixels.Color(255, 51, 119)); break;
      }
    }
  }
}
void loop() {
  if (Serial.available()) {
    serialLoop();
  }
  SunClock();
  CloudLight();
  Lighting();
  Mist();
  Rain();
  Oss();
  Rainbow();
  
}

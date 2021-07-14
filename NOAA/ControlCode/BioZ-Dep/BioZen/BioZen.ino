#define RED 5
#define GREEN 3
#define BLUE 6

#define PUMP 2 
#define VALVE 3

bool rain, mist, sun, lighting = false;
bool sunset, sunrise, moon, sunny = false;

void setup() {
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void serialLoop(){
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    char input = data.charAt(0);
    rain, mist, sun, lighting = false;
    sunset, sunrise, moon, sunny = false;
    switch(input){
      case '3':  rain = true; Serial.println("rain"); break;
      case '2':  mist = true; Serial.println("mist"); break;
      case '1':  sun = true; Serial.println("sun"); break;
      case '4':  lighting = true; Serial.println("lightning"); break;
    }
    switch(input){
      case '6': sunrise = true; Serial.println("sunrise"); break;
      case '7': sunset = true; Serial.println("sunset"); break;
      case '8': moon = true; Serial.println("moon"); break;
      case '9': sunny = true; Serial.println("sunny"); break;
    }
  }
}

void Lighting(){
  if(lighting){
    int brightint = random(40, 100);
    double brightness = brightint/100.0;
    int durration = random(200, 600);
    analogWrite(RED, 125*brightness);
    analogWrite(GREEN, 249*brightness);
    analogWrite(BLUE, 255*brightness);
    delay(durration);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    lighting = false;
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
  /*
  Lighting();
  Mist();
  Rain();
  */
}

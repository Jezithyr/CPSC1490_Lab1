const byte pinSetup = 11111100;
byte pinstates;
byte delaySettings[4][3] = {{1,1,1},{2,1,2},{5,2,5},{30,10,30}};
byte currentConfig = 00000000;


void pinwrite(byte pinstates){
  //PORTC=pinstates;

  currentConfig=11111111;
  
 /* switch (pinstates){
    case B11000000: {
      Serial.print("Solid Red\n");
    }
    case B01100000: {
      Serial.print("North Green/West Red\n");
    }
    case B10000100: {
      Serial.print("North Yellow/West Red\n");
    }
    case B10010000: {
      Serial.print("West Green/North Red\n");
    }
    case B10001000: {
      Serial.print("West Yellow/North Red\n");
    }
    }
*/
  
}
byte pinread(){
  return PORTC;
}


void setup() {
  Serial.begin(9600);
  //DDRC=pinSetup;
  pinwrite(11111100);
  pinwrite(11111100);
  
}

void loop() {
int startTime = millis();
int curTime = 0;
bool cycle = true;
byte currentState = 0;
bool loopback = false;

while (cycle){
  pinstates = pinread();
  curTime = millis();
  switch (currentState)
  {
    case 0: {//solid red
        pinwrite(11000000);
        if ((startTime+20000) <= curTime) {
          if (!loopback) { 
            currentState = 1;
            Serial.print("North Green/West Red\n");
          } else{
            currentState = 3;
            Serial.print("West Green/North Red\n");
            loopback = false;
          }
        }
      }
    case 1: {// North green
        pinwrite(01100000);
        if ((startTime+20000) <= curTime) {
          Serial.print("North Yellow/West Red\n");
          currentState = 2;
        }
    }
    case 2: { // North yellow
        pinwrite(10000100);
         if ((startTime+20000) <= curTime) {
          currentState = 0;
          Serial.print("Solid Red\n");
          loopback = true;
        }
      }
    case 3: { //West green
         pinwrite(10010000);
    if ((startTime+20000) <= curTime) {
          Serial.print("West Yellow/North Red\n");
          currentState = 4;
         
        }
      }
    case 4: { //West Yellow
        pinwrite(10001000);
    if ((startTime+20000) <= curTime) {
          currentState = 0;
          Serial.print("Solid Red\n");
        }
      }
  }
  
  
  
  
}







}

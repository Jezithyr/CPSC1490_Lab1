const byte pinSetup = 11111100;
byte pinstates = 11111100;
byte delaySettings[4][3] = {{1,1,1},{2,1,2},{5,2,5},{30,10,30}};

void pinwrite(byte pinstates){
  PORTC=pinstates;
}
byte pinread(){
  return PORTC;
}


void setup() {
  DDRC=pinSetup;
  pinwrite(11111100);
}

void loop() {
int startTime = millis();
bool cycle = true;

while (cycle){
  pinstates = pinread();
  
  
  
  
  
}







}

const byte pinSetup=11111100;
byte pinstates=11111100;

void pinwrite(byte pinstates){
  PORTC=pinstates;
}
byte pinread(){
  return PORTC;
}
   int lightmain[]={0,0,0};
   int lightcross[]={0,0,0};

void setup() {
  // put your setup code here, to run once:
   DDRC=pinSetup;
   pinwrite(11111100);
  
}

void loop() {
   int startTime = millis();
   int count=0;
   while (true){
    int index=count%4;
    count++;
    switch (index){
      case 0: lightmain[0]=1; lightcross[2]=1; break;
      case 1: lightmain[1]=1; lightcross[2]=1; break;
      case 2: lightmain[2]=1; lightcross[0]=1; break;
      case 3: lightmain[2]=1; lightcross[1]=1; break;
    }
    lightmain[]={0,0,0};
    lightcross[]={0,0,0};
}

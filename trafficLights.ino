/*
 * pin setup:
 * 30, 31: North RED, West Red
 * 32,33: North Green, West Green
 * 34,46: North Yellow, West Yellow
 * 40,31: switch inputs
 * 
*/

/*port setup
 * DRRC = 30-37
 *Pins      30      31         32           33          34        35          36      37
 *State     1       1           1           1           1           1          0      0
 *Light (RedNorth)(RedWest)(GreenNorth)(GreenWest)(YellowNorth)(YellowWest)(Unused)(Unused)
 */

 
const byte pinSetup = B11111100; 
const byte sensorPorts[] = {40,41};

/*
 *Delay state setup: 
 *       
 * Switch State:      [off][off] [on][off]  [off][on]   [on][on]
 *                
 * Delay length(sec)  {{1,1,1},   {2,1,2},   {5,2,5}, {30,10,30}}
 *  
 * Maximum of 4 options corresponding with dipswitch
 * 
 *Delay value: {  1,      1,      1   }
 *                ^       ^       ^
 *Light color:   Green  Yellow   Red
 *
 */
//delay settings all values in seconds
const int delaySettings[4][3] = {{1,1,1},{2,1,2},{5,2,5},{30,10,30}};

/*
 * ======================== Do not edit below here ============================
 */

//look up table and formating arry for delay settings
byte settingIndex = 0;
const byte bitValueArray[2][2] = {{0,1},{2,3}};

//timer variables
long startTime;
long curtime;

//switch states
byte switch1State = 0;
byte switch2State = 0;

//loopback for solid red state
bool loopback = false;

//state tracking
byte currentState = 0;


void pinwrite(byte pinstates){
  PORTC=pinstates;
  
}


void setup() {
  //ddr output in setup
  DDRC=pinSetup;

  //setup sensor pins
  pinMode(sensorPorts[0], INPUT);
  pinMode(sensorPorts[1], INPUT);
  //start timer variable
  startTime = millis();
}

void loop() {
  if (digitalRead(41)==HIGH) {
    switch1State = 1;
  }else {
    switch1State = 0;
  }
  if (digitalRead(40)==HIGH){
    switch2State = 1;
  }else{
    switch2State = 0;
  }
  settingIndex = bitValueArray[switch1State][switch2State];
  curtime = millis();
  switch (currentState){
    case 0: //solid red
        pinwrite(B11000000);
        if ((curtime-(delaySettings[settingIndex][2] * 1000)) >= startTime) {
          if (loopback) { 
            currentState = 3;
            loopback = false;
          } else{
            currentState = 1;
            loopback = true;
          }
          startTime = millis();//timer reset
        }
    break;
    case 1: // North green
        pinwrite(B01100000);
        if ((curtime-(delaySettings[settingIndex][0] * 1000)) >= startTime) {
          currentState = 2;
          startTime = millis();//timer reset
        }
    break;
    
    case 2:  // North yellow
        pinwrite(B1001000); //write lights
        if ((curtime-(delaySettings[settingIndex][1] * 1000)) >= startTime) {
          currentState = 0;
          startTime = millis();//timer reset
        }
    break;
    case 3:  //West green
         pinwrite(B10010000);
         if ((curtime-(delaySettings[settingIndex][0] * 1000)) >= startTime) {
         currentState = 4;
         startTime = millis();//timer reset
        }
    break;
      
    case 4:  //West Yellow
        pinwrite(B10000100);
        if ((curtime-(delaySettings[settingIndex][1] * 1000)) >= startTime) {
          currentState = 0;
          startTime = millis(); //timer reset
        }
         
    break;  
  }
}

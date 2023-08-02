//https://aps-parking-board-default-rtdb.firebaseio.com/
//AIzaSyDD2W1GP6eASpE6Rno_8mw5ZJ1Qb7R0bpU - api key

#include <NewPing.h>
const int triggerP = 2;
const int echoP = 3;
int distanceSense;

NewPing sonar(triggerP, echoP, 50);

//arrays===============================================================
int pinsArr[2][4] = {
  {7, 6, 5, 4}, 
  {13, 12, 11, 10}
};

bool configArr[2][4] = {
  {false, false, true, true},
  {false, true, true, true}
};

//helper methods====================================================================================
//helper method to toggle pin using boolean
void togPin(int pinNum, bool on){
  if(on){
    digitalWrite(pinNum, HIGH);
  } else {
    digitalWrite(pinNum, LOW);
  }
}

//sets all pins to either off or on
void setAllPins(bool on){
  for(int r = 0; r<2; r++){
    for(int c = 0; c<4; c++){
      togPin(pinsArr[r][c], on);
    }
  }
}

//double for loop to go through pinsArr to set it to the configuration in configArr
void updateLot(){
  for(int r = 0; r<2; r++){
    for(int c = 0; c<4; c++){
      togPin(pinsArr[r][c], configArr[r][c]);
    }
  }
}

int getClosestLot(){
  double minDistance = 100;
  double distSq;
  int minR, minC;

  for(int r = 0; r<2; r++){
    for(int c = 0; c<4; c++){
      if(configArr[r][c]){
        distSq = (r-1)*(r-1)+(c)*(c);
        if(distSq<minDistance){
          minDistance = distSq;
          minR = r;
          minC = c;
        }
      }
    }
  }

  return pinsArr[minR][minC];
}

//MAIN=========================================================================
void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

}

void loop() {
  distanceSense = sonar.ping_cm();
  Serial.println(distanceSense);

  if(distanceSense > 1 && distanceSense < 5){
    updateLot();
  } else {
    //setAllPins(false);
    updateLot();
  }

  delay(250);
  togPin(getClosestLot(), false);
  delay(250);

}

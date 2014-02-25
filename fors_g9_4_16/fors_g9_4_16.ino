const int dataPin = 9;
const int clockPin = 10;
const int latchPin = 11;


int counter;

int All_on[4][16] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}        
};

int All_off[4][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} 
};

int kryds[4][16] = {
  {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1} 
};

int streg[4][16] = {
  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
  {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0} 
};

int hej[4][16] = {
  {1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
  {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
  {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0} 
};

int ram[4] = {0,0,0,0};

/*---------------- all commands ----------------
 lightLED
 randomLED
 ----- mitrix's -----
 All_on
 All_off
 kryds
 streg
 */


//---------------- setup ----------------
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600);
}

//---------------- loop ----------------
void loop() {
  moveObj(streg);
  lightLED(streg);
  //randomLED();
  counter++;
  
  Serial.println(analogRead(A0));
}

//---------------- moveObj ----------------
void moveObj(int moveTempObj[4][16]){
  if (counter>map(analogRead(A0), 120, 330, 5, 30)){
    for (int y = 0; y < 4; y++) {  
      for (int x = 0; x < 16; x ++) {
        if (moveTempObj[y][x] == 1) {
          moveTempObj[y][x-1]=1;
          if (x-1==-1){
            ram[y]=1;
          }
        }
        else{
          moveTempObj[y][x-1]=0;
          if (x-1==-1){
            ram[y]=0;
          }
        }
      }
    }
    for (int y = 0; y < 4; y++){
      moveTempObj[y][15]=ram[y];
    }
    counter=0;
  }
}

//---------------- randomLED ----------------
void randomLED(){  
  if (random(5)==2){
    int rx=random(0, 4);
    int ry=random(0, 16);

    if (All_off[ry][rx]==1){
      All_off[ry][rx]=0;
    }
    else{
      All_off[ry][rx]=1;
    }
  }
}

//---------------- lightLED ----------------
void lightLED(int tempLED[4][16]) {
  byte RowToSend = 0;
  byte ColToSend = 0;
  byte ColTwoToSend = 0;

  for (int y = 0; y < 4; y++) {
    ColToSend = 0;
    RowToSend = 0;
    ColTwoToSend = 0;

    for (int x = 0; x < 8; x ++) {
      if (tempLED[y][x] == 0) { //skriv 1 i stedet for 0, hvis mitrix'et virker omvendt!
        bitWrite(ColToSend, x, HIGH);
      } 
    }

    for (int xx = 8; xx < 16; xx ++) {
      if (tempLED[y][xx] == 0) { //skriv 1 i stedet for 0, hvis mitrix'et virker omvendt!
        bitWrite(ColTwoToSend, xx-8, HIGH);
      } 
    }

    digitalWrite(latchPin, LOW);
    bitWrite(RowToSend, y, HIGH);
    shiftOut(dataPin, clockPin, MSBFIRST, ColTwoToSend);
    shiftOut(dataPin, clockPin, MSBFIRST, ColToSend);
    shiftOut(dataPin, clockPin, MSBFIRST, RowToSend);
    digitalWrite(latchPin, HIGH);   
    // delay(1);
  }
}






const int dataPin = 9;
const int clockPin = 10;
const int latchPin = 11;

const int Knap_op = 2;
const int Knap_ned = 3;
const int Knap_venstre = 4;
const int Knap_hoejre = 5;

int reset_state = 0;

int aeble_x;
int aeble_y;

int slange_del_tolv_x;
int slange_del_tolv_y;
int slange_del_elve_x;
int slange_del_elve_y;
int slange_del_ti_x;
int slange_del_ti_y;
int slange_del_ni_x;
int slange_del_ni_y;
int slange_del_otte_x;
int slange_del_otte_y;
int slange_del_syv_x;
int slange_del_syv_y;
int slange_del_seks_x;
int slange_del_seks_y;
int slange_del_fem_x;
int slange_del_fem_y;
int slange_del_fire_x;
int slange_del_fire_y;
int slange_del_tre_x;
int slange_del_tre_y;
int slange_del_to_x;
int slange_del_to_y;
int slange_del_et_x;
int slange_del_et_y;

int aeble_hovedet_x=4;
int aeble_hovedet_y=3;

int aeble_bid=0;

/* --retning--
 1 = op
 2 = ned
 3 = venstre
 4 = hoejre
 */
int retning = 4;

int moving_counter;

const int hastighed=30; //hastighed på slange, mindre værdi højere hastighed

const int screen_orientation=0; //skriv 1 i stedet for 0, hvis mitrix'et virker omvendt!

int All_off[8][30] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int reset_led[8][30] = {
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
  {1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
  {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
  {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
};

int Game_play[8][30] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//---------------- setup ----------------------------------------------------------------
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(Knap_op, INPUT);
  pinMode(Knap_ned, INPUT);
  pinMode(Knap_venstre, INPUT);
  pinMode(Knap_hoejre, INPUT);
  
  randomSeed(analogRead(0));
  aeble();
}

//---------------- loop ----------------------------------------------------------------
void loop() {
  moving_counter++;
  aeble_retning();
  aeble_fangst();
  moving();
  if (reset_state==1)lightLED(reset_led);
  else lightLED(Game_play);
  //slange_bid();
}

//---------------- aeble_fangst --------------------------------
void aeble_fangst(){
  if (aeble_x==aeble_hovedet_x && aeble_y==aeble_hovedet_y){
    aeble_bid++;
    aeble();
  }
}

//---------------- slange_bid --------------------------------
/* void slange_bid(){
  if (aeble_hovedet_x==slange_del_et_x || aeble_hovedet_x==slange_del_to_x || aeble_hovedet_x==slange_del_tre_x || aeble_hovedet_x==slange_del_fire_x
|| aeble_hovedet_x==slange_del_fem_x || aeble_hovedet_x==slange_del_seks_x || aeble_hovedet_x==slange_del_syv_x || aeble_hovedet_x==slange_del_otte_x){
  
    if (aeble_hovedet_y==slange_del_et_y || aeble_hovedet_y==slange_del_to_y || aeble_hovedet_y==slange_del_tre_y || aeble_hovedet_y==slange_del_fire_y
|| aeble_hovedet_y==slange_del_fem_y || aeble_hovedet_y==slange_del_seks_y || aeble_hovedet_y==slange_del_syv_y || aeble_hovedet_y==slange_del_otte_y){
      reset_state=1;
    }
  }
} */

//---------------- moving --------------------------------
void moving(){
  if (moving_counter>hastighed){

    //----------------------------------------------
    if (aeble_bid==11){
      reset_state=1;
    }
    
    if (aeble_bid==10){
      Game_play[slange_del_tolv_y][slange_del_tolv_x]=0;
    }
    
    if (aeble_bid==9){
      Game_play[slange_del_elve_y][slange_del_elve_x]=0;
    }
    
    if (aeble_bid==8){
      Game_play[slange_del_ti_y][slange_del_ti_x]=0;
    }
    
    if (aeble_bid==7){
      Game_play[slange_del_ni_y][slange_del_ni_x]=0;
    }
    
    if (aeble_bid==6){
      Game_play[slange_del_otte_y][slange_del_otte_x]=0;
    }

    if (aeble_bid==5){
      Game_play[slange_del_syv_y][slange_del_syv_x]=0;
    }

    if (aeble_bid==4){
      Game_play[slange_del_seks_y][slange_del_seks_x]=0;
    }

    if (aeble_bid==3){
      Game_play[slange_del_fem_y][slange_del_fem_x]=0;
    }

    if (aeble_bid==2){
      Game_play[slange_del_fire_y][slange_del_fire_x]=0;
    }
    if (aeble_bid==1){
      Game_play[slange_del_tre_y][slange_del_tre_x]=0;
    }

    if (aeble_bid==0){
      Game_play[slange_del_to_y][slange_del_to_x]=0;
    }
    
    slange_del_tolv_x=slange_del_elve_x;
    slange_del_tolv_y=slange_del_elve_y;
    
    slange_del_elve_x=slange_del_ti_x;
    slange_del_elve_y=slange_del_ti_y;
    
    slange_del_ti_x=slange_del_ni_x;
    slange_del_ti_y=slange_del_ni_y;
    
    slange_del_ni_x=slange_del_otte_x;
    slange_del_ni_y=slange_del_otte_y;

    slange_del_otte_x=slange_del_syv_x;
    slange_del_otte_y=slange_del_syv_y;

    slange_del_syv_x=slange_del_seks_x;
    slange_del_syv_y=slange_del_seks_y;

    slange_del_seks_x=slange_del_fem_x;
    slange_del_seks_y=slange_del_fem_y;

    slange_del_fem_x=slange_del_fire_x;
    slange_del_fem_y=slange_del_fire_y;

    slange_del_fire_x=slange_del_tre_x;
    slange_del_fire_y=slange_del_tre_y;

    slange_del_tre_x=slange_del_to_x;
    slange_del_tre_y=slange_del_to_y;

    slange_del_to_x=slange_del_et_x;
    slange_del_to_y=slange_del_et_y;

    slange_del_et_x=aeble_hovedet_x;
    slange_del_et_y=aeble_hovedet_y;

    //----------------------------------------------
    if(retning==1) {
      Game_play[aeble_hovedet_y-1][aeble_hovedet_x]=1;
      aeble_hovedet_y--;
    }
    if(retning==2) {
      Game_play[aeble_hovedet_y+1][aeble_hovedet_x]=1;
      aeble_hovedet_y++;
    }
    if(retning==3) {
      Game_play[aeble_hovedet_y][aeble_hovedet_x-1]=1;
      aeble_hovedet_x--;
    }
    if(retning==4) {
      Game_play[aeble_hovedet_y][aeble_hovedet_x+1]=1;
      aeble_hovedet_x++;
    }
    moving_counter=0;
  }
}

//---------------- retning --------------------------------
void aeble_retning(){
  if (digitalRead(Knap_op)==1)retning=1;
  if (digitalRead(Knap_ned)==1)retning=2;
  if (digitalRead(Knap_venstre)==1)retning=3;
  if (digitalRead(Knap_hoejre)==1)retning=4;
}

//---------------- aeble --------------------------------
void aeble(){
  aeble_x=random(0, 30);      //virker ikke som tilfædige tal!!!!
  aeble_y=random(0, 8);
  Game_play[aeble_y][aeble_x]=1;
}

//---------------- lightLED --------------------------------
void lightLED(int tempLED[8][30]) {
  byte RowToSend = 0;
  byte ColOneSend = 0;
  byte ColTwoToSend = 0;
  byte ColThreeToSend = 0;
  byte ColFourToSend = 0;

  for (int y = 0; y < 8; y++) {
    RowToSend = 0;
    ColOneSend = 0;
    ColTwoToSend = 0;
    ColThreeToSend = 0;
    ColFourToSend = 0;

    for (int x = 0; x < 8; x ++) {
      if (tempLED[y][x] == screen_orientation) {
        bitWrite(ColOneSend, x, HIGH);
      } 
    }

    for (int x = 8; x < 16; x ++) {
      if (tempLED[y][x] == screen_orientation) {
        bitWrite(ColTwoToSend, x-8, HIGH);
      } 
    }

    for (int x = 16; x < 24; x ++) {
      if (tempLED[y][x] == screen_orientation) {
        bitWrite(ColThreeToSend, x-16, HIGH);
      } 
    }

    for (int x = 24; x < 30; x ++) {
      if (tempLED[y][x] == screen_orientation) {
        bitWrite(ColFourToSend, x-24, HIGH);
      } 
    }

    digitalWrite(latchPin, LOW);
    bitWrite(RowToSend, y, HIGH);
    shiftOut(dataPin, clockPin, MSBFIRST, ColFourToSend);
    shiftOut(dataPin, clockPin, MSBFIRST, ColThreeToSend);
    shiftOut(dataPin, clockPin, MSBFIRST, ColTwoToSend);
    shiftOut(dataPin, clockPin, MSBFIRST, ColOneSend);
    shiftOut(dataPin, clockPin, MSBFIRST, RowToSend);
    digitalWrite(latchPin, HIGH);   
    // delay(1);
  }
}











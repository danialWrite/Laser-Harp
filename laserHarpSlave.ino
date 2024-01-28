
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

char key = '1';

const int rs = 14, en = 15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int trig=12;
int echo=13;
int pin1;
float elapsed = micros();
int del = 500;
int mode = 1;

bool serialResMode = true;
bool serialResVol = true;

int modeOut = 11;
int vol;

int dispvol = 100;
int sendMode = 101;

int conf = 1;

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(modeOut,OUTPUT);
}
  
void loop(){
  if(((micros()-elapsed)/1000)>del){
    digitalWrite(trig, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig, HIGH);
    delayMicroseconds(10); 
  
    digitalWrite(trig, LOW);
    int duration = pulseIn(echo, HIGH);
    int distance = duration/58.2;

    if(distance>60 || distance<0){
        del = 500;
    }
    else{
      vol = map(distance,0,60,0,30);
      dispvol = map(distance,0,60,0,100);
      del = 100;
      lcd.clear();
      lcd.setCursor(0, 2);
      lcd.print("Volume: ");
      lcd.setCursor(7, 2);
      lcd.print(dispvol);
      Serial.write(vol);
      serialResVol = false;
      lcdMode(mode);
    }
    elapsed = micros();
  }
  if(key){
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("Volume: ");
    lcd.setCursor(7, 2);
    lcd.print(dispvol);
    lcd.setCursor(0, 0);
    if(conf == 1){
      if(key == '1'){
        lcd.print("Concert Piano");
        mode = 0;
      }
      if(key == '2'){
        lcd.print("Amped Guitar 1");
        mode = 1;
      }
      if(key == '3'){
        lcd.print("Amped Guitar 2");
        mode = 2;
      }
      if(key == '4'){
        lcd.print("Ballad Piano");
        mode = 3;
      }
      if(key == '5'){
        lcd.print("Celtic Harp");
        mode = 4;
      }
      if(key == '6'){
        lcd.print("Cinematic Piano");
        mode = 5;
      }
      if(key == '7'){
        lcd.print("Concert Harp");
        mode = 6;
      }
      if(key == '8'){
        lcd.print("Dreamy Rhodes");
        mode = 7;
      }
      if(key == '9'){
        lcd.print("Just Arcade");
        mode = 8;
      }
      if(key == '*'){
        lcd.print("Mariachi Trumpet");
        mode = 9;
      }
      if(key == '0'){
        lcd.print("Nostalgia");
        mode = 10;
      }
      if(key == '#'){
        lcd.print("Steeldrum");
        mode = 11;
      }
    }
    if(conf == 2){
      if(key == '1'){
        lcd.print("Twinkle Twinkle");
        mode = 0;
      }
      if(key == '2'){
        lcd.print("Tetris");
        mode = 1;
      }
      if(key == '3'){
        lcd.print("Jocelyn Flores");
        mode = 2;
      }
      if(key == '4'){
        lcd.print("Golden Hour");
        mode = 3;
      }
      if(key == '5'){
        lcd.print("After Dark");
        mode = 4;
      }
      if(key == '6'){
        lcd.print("Under The Inf...");
        mode = 5;
      }
      if(key == '7'){
        lcd.print("Aadat");
        mode = 6;
      }
    }

    if(key == 'A'){
      mode = 12;
      conf = 1;
    }
    if(key == 'B'){
      lcd.print("Playing Music");
      conf = 2;
      mode = 13;
    }
    if(key == 'C'){
      mode = 14;
    }
    if(key == 'D'){
      mode = 15;
    }
    sendMode = mode+100;
    Serial.write(sendMode);
    serialResMode = false;
  }
  if(!serialResMode){
    while(Serial.available()==0){
      Serial.write(sendMode);
    }
    serialResMode = true;
  }
  if(!serialResVol){
    while(Serial.available()==0){
      Serial.write(vol);
    }
    serialResVol = true;
  }
  key = keypad.getKey();
}

int lcdMode(int m){
  lcd.setCursor(0,0);
  if(conf == 1){
    if(m == 0){
      lcd.print("Concert Piano");
    }
    if(m == 1){
      lcd.print("Amped Guitar 1");
    }
    if(m == 2){
      lcd.print("Amped Guitar 2");
    }
    if(m == 3){
      lcd.print("Ballad Piano");
    }
    if(m == 4){
      lcd.print("Celtic Harp");
    }
    if(m == 5){
      lcd.print("Cinematic Piano");
    }
    if(m == 6){
      lcd.print("Concert Harp");
    }
    if(m == 7){
      lcd.print("Dreamy Rhodes");
    }
    if(m == 8){
      lcd.print("Just Arcade");
    }
    if(m == 9){
      lcd.print("Mariachi Trumpet");
    }
    if(m == 10){
      lcd.print("Nostalgia");
    }
    if(m == 11){
      lcd.print("Steeldrum");
    }
  }
  if(conf == 2){
    
    if(m == 0){
      lcd.print("Twinkle Twinkle");
    }
    if(m == 1){
      lcd.print("Tetris");
    }
    if(m == 2){
      lcd.print("Jocelyn Flores");
    }
    if(m == 3){
      lcd.print("Golden Hour");
    }
    if(m == 4){
      lcd.print("After Dark");
    }
    if(m == 5){
      lcd.print("Under The Inf...");
    }
    if(m == 6){
      lcd.print("Aadat");
    }
  }
}

#include <SoftwareSerial.h>// import the serial library
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
//#   include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);
int info;
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
bool state,laststate=HIGH;
int count=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial g(0, 1); // RX, TX
char c;
String content="";
int rfid(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
 
  content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
Serial.println(content);
  
  return 1;
}
char d;
void setup() {
  g.begin(9600);
  SPI.begin();
   Serial.begin(9600);
   pinMode(2,INPUT);
   mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
 mfrc522.PCD_DumpVersionToSerial();
}

void loop() {
  state=digitalRead(2);
  if(state==LOW &&  laststate==HIGH)
  count++;
  laststate=state;
//  g.println("enter s to start and b to break:");
  if(g.available())
  {
//    delay(100);
    d=g.read();
      if(d=='s'){
      
      Serial.println(count);
      
      info=0;
int    timestamp=millis();
      while(millis()-timestamp<3000){
        while( info==0 && millis()-timestamp<3000){
              info = rfid();
               
        }
      }
      
    //  g.println("start");
      //rfid code
      
  }
  else
  {
    delay(1);
  }
  }
  
}
   

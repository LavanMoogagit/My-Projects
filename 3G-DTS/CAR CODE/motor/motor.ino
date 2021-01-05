//#include <Servo.h>             //Servo library
 



void forward(){              //moves in forward direction
 // Serial.println("forward");
  digitalWrite(5,HIGH);
  digitalWrite(11,HIGH);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
  
//  analogWrite(11,100);
//   analogWrite(6,0);
//   analogWrite(10,0);
}
void backward(){   //moves in backward direction
 // Serial.println("backward");
//  analogWrite(5,0);
//  analogWrite(11,0);
//  analogWrite(10,255);
//  analogWrite(6,255);

   digitalWrite(5,LOW);
  digitalWrite(11,LOW);
 digitalWrite(6,HIGH);
 digitalWrite(10,HIGH);
 
}
void left(){    // moves in left direction
//  analogWrite(5,100);
//  analogWrite(11,0);
//   analogWrite(6,0);
//   analogWrite(10,0);

    digitalWrite(5,HIGH);
  digitalWrite(11,LOW);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
}
void right(){   // moves in right direction
//  analogWrite(5,0);
//  analogWrite(11,100);
//  analogWrite(6,0);
//   analogWrite(10,0);

    digitalWrite(5,LOW);
  digitalWrite(11,HIGH);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
}
void stop(){  // all motors will stop
  
//  analogWrite(5,0);
//  analogWrite(11,0);
//   analogWrite(6,0);
//   analogWrite(10,0);

    digitalWrite(5,LOW);
  digitalWrite(11,LOW);
 digitalWrite(6,LOW);
 digitalWrite(10,LOW);
}

String c;
void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);   //left motors forwardn
  pinMode(5,OUTPUT);   //left motors reverse
  pinMode(11,OUTPUT);   //right motors forward
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);   //right motors reverse
  pinMode(9,OUTPUT);   //Le
//  digitalWrite(13,HIGH);
//  servo_test1.attach(3);
//  servo_test2.attach(9);
  Serial.begin(9600);
}
int engine=0;
void loop() {
  // put your main code here, to run repeatedly:
//  check_engine();
//digitalWrite(13,LOW);
  if(Serial.available()>0){
    c=Serial.readStringUntil('\n');
    Serial.println(c);
  }
  if(c=="N")
      digitalWrite(13,LOW);
      else if(c=="n")
      digitalWrite(13,HIGH);
    if(c=="X")
    engine=1;
    else if(c=="Y")
    engine=0;
    if(engine==1){
      if(c=="F")
      forward();
      else if(c=="G")
      backward();
      else if(c=="R")
      right();
      else if(c=="L")
      left();
      else if(c=="S")
      stop();
    }
//    else{
//      if(c.startsWith("J")){
//        
//        int angle2=c.substring(1).toInt();
//        servo_test2.write(angle2);
//      }
//      else if(c.startsWith("K")){
//        
//        int angle1=c.substring(1).toInt();
//        servo_test1.write(angle1);
//      }
//      
//    }
//  delay(500);
}

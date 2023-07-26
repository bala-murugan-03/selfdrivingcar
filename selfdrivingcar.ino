const int EnableL=5;   
const int HighL=6;
const int LowL=7;
const int EnableR=10;
const int HighR=8;
const int LowR=9;
char t;
const int led1 = 11;
const int led2 = 12;
const int buzz = 4;
const int red = A0;
unsigned long t1;
unsigned long t2;
int trigpin = 2;
int echopin = 3;
void setup() {
  pinMode(EnableL,OUTPUT);
  pinMode(HighL,OUTPUT);
  pinMode(LowL,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(EnableR,OUTPUT);
  pinMode(HighR,OUTPUT);
  pinMode(LowR,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);  
  Serial.begin(9600);

}
void accelerate(){
  digitalWrite(led2,LOW);
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,255);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,HIGH);
  analogWrite(EnableR,255);
  
}
void reverse(){
  digitalWrite(led2,LOW);
  digitalWrite(HighL,HIGH);
  digitalWrite(LowL,LOW);
  analogWrite(EnableL,255);

  digitalWrite(HighR,HIGH);
  digitalWrite(LowR,LOW);
  analogWrite(EnableR,255);

}
void left(){
  digitalWrite(led2,LOW);
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,255);

  digitalWrite(HighR,HIGH);
  digitalWrite(LowR,LOW);
  analogWrite(EnableR,25);

}
void right(){
  digitalWrite(led2,LOW);
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,HIGH);
  analogWrite(EnableL,25);

  digitalWrite(HighR,HIGH);
  digitalWrite(LowR,LOW);
  analogWrite(EnableR,255);

}
void selfdrive(){
    while(t=='U'||t=='S'){
    while(Serial.available()>0){
        t = Serial.read(); 
        Serial.println(t);
        if(t != 'S'){
          return;
        }
    }
    accelerate();
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin,LOW);
    long duration = pulseIn(echopin,HIGH);
    long distance = 0.017*(duration)+3;
    Serial.println(distance);
    if(distance > 0 && distance <=20)
       if(random(0,2) == 0){
           left();
           delay(3000);
       }
       else{
          right();
          delay(3000);
       } 
     Serial.println("END");   
    }     
}
void headLight(){
    while(t=='W'||t=='S'){
       digitalWrite(led1,HIGH);
    while(Serial.available()>0){
        t = Serial.read(); 
        Serial.println(t);
        if(t == 'W'){
          return;
        }
        else if(t == 'F'){
          digitalWrite(led1,HIGH);
          
           accelerate();
        }
       else if(t == 'B'){
        digitalWrite(led1,HIGH);
           reverse();
        }
       else if(t == 'L'){
        digitalWrite(led1,HIGH);
           left();
        }  
       else if(t == 'R'){
        digitalWrite(led1,HIGH);
           right();
        }   
       else if(t == 'V'){//buzzer
           digitalWrite(buzz,HIGH);   
       }
    
    }  
}
}
void parking(){
    while(t=='X'||t=='S'){
         digitalWrite(led1,HIGH);
         digitalWrite(led2,HIGH);
         delay(1000);
         digitalWrite(led1,LOW);
         digitalWrite(led2,LOW);
         delay(1000);
    while(Serial.available()>0){
        t = Serial.read(); 
        Serial.println(t);
               if (t!='S'){
                  return;
               }
               
        }
    }
       
}
void loop() {
  digitalWrite(led2,LOW);
  digitalWrite(buzz,LOW);     
  while(Serial.available()>0)
 {
  t = Serial.read();
  Serial.println(t);
 }
  if(t=='F'){
    accelerate();
  }
  else if(t=='B'){
    reverse();
  }
  else if(t == 'W'){
     digitalWrite(led1,HIGH);
     headLight();
     digitalWrite(led1,LOW);     
  }
 else if(t == 'V'){//buzzer
    digitalWrite(buzz,HIGH);
 }
 else if(t == 'U'){
      analogWrite(red,255);
      selfdrive();
      analogWrite(red,0);     
 }
 else if(t  == 'X'){
      parking();
 }
 else if(t == 'S'){
  digitalWrite(HighL,LOW);
  digitalWrite(LowL,LOW);
  analogWrite(EnableL,0);

  digitalWrite(HighR,LOW);
  digitalWrite(LowR,LOW);
  analogWrite(EnableR,0);
  digitalWrite(led2,HIGH);
 }
  else if(t=='R'){
    right();
  }
  else if(t=='L'){
    left();
  }
  
}

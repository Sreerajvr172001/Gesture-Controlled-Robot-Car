#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10
#define ml1 5
#define ml2 6
#define mr1 8
#define mr2 7

int pipe = 1234;

RF24 radio(CE_PIN, CSN_PIN);

int data;

void setup()
 {
  Serial.begin(9600);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(ml1,OUTPUT);
  pinMode(ml2,OUTPUT);
  pinMode(mr1,OUTPUT);
  pinMode(mr2,OUTPUT);
 }

void loop()
 {
  if ( radio.available() )
   {
     bool done = false;
     while (!done)
      {
        radio.read( &data, sizeof(data) );
        Serial.println(data);
        if(data==1){
          digitalWrite(ml1,HIGH);
          digitalWrite(ml2,LOW); 
          digitalWrite(mr1,LOW); 
          digitalWrite(mr2,HIGH); 
          }
        else if(data==2){
          digitalWrite(ml1,LOW);
          digitalWrite(ml2,HIGH); 
          digitalWrite(mr1,LOW); 
          digitalWrite(mr2,HIGH);
        }
        else if(data==3){
          digitalWrite(ml1,LOW);
          digitalWrite(ml2,HIGH); 
          digitalWrite(mr1,HIGH); 
          digitalWrite(mr2,LOW);    
        }
        else if(data==4){
          digitalWrite(ml1,HIGH);
          digitalWrite(ml2,LOW); 
          digitalWrite(mr1,HIGH); 
          digitalWrite(mr2,LOW);   
        }
        else{
          digitalWrite(ml1,LOW);
          digitalWrite(ml2,LOW); 
          digitalWrite(mr1,LOW); 
          digitalWrite(mr2,LOW);  
        }
        done=true;
      }
    }
  else
    {
      Serial.println("No radio available");
 
    }
 }

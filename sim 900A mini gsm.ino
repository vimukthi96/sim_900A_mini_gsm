#include <SoftwareSerial.h>
SoftwareSerial gsm(9, 10);
char msg;
void setup() {
  // put your setup code here, to run once:
  gsm.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(7,OUTPUT);
  Serial.println("GSM SIM900A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("s : to send message");
  Serial.println();
  delay(100);
}

void loop(){  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
   
  }
 if (gsm.available()>0)
 Serial.write(gsm.read());
}
 
void ReceiveMessage()
{
  gsm.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (gsm.available()>0)
  {
    msg=gsm.read();
    Serial.print(msg);
    if (msg =="ON"){
      digitalWrite(7,HIGH);
    }
    else if(msg=="OFF"){
      digitalWrite(7,LOW);
    }
  }
}
void SendMessage()
{
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm.println("AT+CMGS=\"+94xxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  gsm.println("hi im automated system");// The SMS text you want to send
  delay(100);
  gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 


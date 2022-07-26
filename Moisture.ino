#include <ESP8266WiFi.h>

#include <Wire.h>

#include <iostream>

using namespace std;


String apiKey = "" ;

const char* ssid = "";  // Enter Wi-fi ID

const char* password = "";   // Enter Wi-fi password

 

const char* server = "";

 

WiFiClient client;

void setup() {    

  Serial.begin(115200);

  pinMode(A0,INPUT);

 

  pinMode(5, OUTPUT);

  delay(10);

  WiFi.begin(ssid, password);

   

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
    Serial.print(WiFi.status());

  }

  Serial.println("");
  Serial.println("WiFi connected");
}

 
 void Delay(){
  for(unsigned int i = 0; i < 15; i++){
      delay(1000);                        
    }                      

 }

void check(int t){
  if(t <250){
              digitalWrite(5, LOW); 
        }
        else{
              digitalWrite(5, HIGH);
          }
          Serial.print("Your plant needs water: ");
  
       Serial.print(t);
  }


int readData(){

    int temp1 = analogRead(A0);
    
    return temp1;
    }
    
 void connection(){
  // display.clear();

  int temp = readData(); 

 

    if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
  
      String postStr = apiKey;
  
             postStr +="&field1=";
  
             postStr += String(temp);
  
             postStr += "\r\n\r\n";
  
       if(postStr != NULL){
       client.print("POST /update HTTP/1.1\n");
  
       client.print("Host: api.thingspeak.com\n");
  
       client.print("Connection: close\n");
  
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  
       client.print("Content-Type: application/x-www-form-urlencoded\n");
  
       client.print("Content-Length: ");
  
       client.print(postStr.length());
  
       client.print("\n\n");
  
       client.print(postStr);
      check(temp);
        Serial.print("Sending value to thingSpeak ");
       }
     
       Serial.println("Data has been sent");

    }
  }

void loop() {

 
  connection();
  
  client.stop();

  Serial.println("Waiting 15 sec to   update...");    

  Delay();                    

}

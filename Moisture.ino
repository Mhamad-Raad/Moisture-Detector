
#include <ESP8266WiFi.h>

#include <Wire.h>

#include <iostream>

using namespace std;





String apiKey = "" // api key here;

const char* ssid = "";  // Enter Wi-fi ID

const char* password = "";   // Enter Wi-fi password

 

const char* server = "api.thingspeak.com";

 

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

  }

  Serial.println("");

  Serial.println("WiFi connected");

 

}

 

 

void loop() {

 // display.clear();

  int temp = analogRead(A0);

 

  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com

    String postStr = apiKey;

           postStr +="&field1=";

           postStr += String(temp);

           postStr += "\r\n\r\n";

 
     client.print("POST /update HTTP/1.1\n");

     client.print("Host: api.thingspeak.com\n");

     client.print("Connection: close\n");

     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");

     client.print("Content-Type: application/x-www-form-urlencoded\n");

     client.print("Content-Length: ");

     client.print(postStr.length());

     client.print("\n\n");

     client.print(postStr);
    if(temp <200){
            digitalWrite(5, LOW); 
      }
      else{
            digitalWrite(5, HIGH);
        }
           

 

     Serial.print("Moisture Sensor Value: ");

     Serial.print(temp);

 

     Serial.println(" send to Thingspeak");



  }

  client.stop();

   

   Serial.println("Waiting...");    



  for(unsigned int i = 0; i < 15; i++)

  {

    delay(1000);                        

  }                      

}

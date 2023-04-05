#include <ESP8266WiFi.h>

String apiKey = "LZVRRDURH564KLC0"; // write your "Write API key"
const char* ssid = "GlobeAtHome_192B1_2.4"; // write your "wifi name"
const char* password = "ub56H8Pa"; // write your "wifi password"
const char* server = "api.thingspeak.com";
WiFiClient client;

//for NodeMCU
const int trigPin1 = D1;
const int echoPin1 = D2;
const int trigPin2 = D3;
const int echoPin2 = D4;
const int trigPin3 = D5;
const int echoPin3 = D6;
const int trigPin4 = D7;
const int echoPin4 = D8;
// defines variables
// long duration;
// int distance;
long duration1, distance1, duration2, distance2, duration3, distance3, duration4, distance4;
void setup() 
{
  Serial.begin(9600);
  Serial.println("Serial Begin");
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin2, INPUT); 
  pinMode(trigPin3, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin3, INPUT); 
  pinMode(trigPin4, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin4, INPUT); 
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
        
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("WiFi connected");
}

void loop() 
{
  ultra();
  delay(1000);
  // we have made changes in program to decrease the latency.
  // but it will take minimum 15 second to post data on Thingspeak channel.
    if (client.connect(server,80))
    {
      fwd_to_Thingspeak();
    }
    client.stop();
    Serial.println("Waiting");
    delay(1000);
}

void ultra()
{
  // Clears the trigPin1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin1 on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(5000);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH) ;
  distance1= duration1*0.034/2;

  
  // Clears the trigPin2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin2 on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(5000);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH) ;
  distance2= duration2*0.034/2;

  
  // Clears the trigPin3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin3 on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(5000);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH) ;
  distance3= duration3*0.034/2;

  
  // Clears the trigPin4
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  // Sets the trigPin4 on HIGH state for 10 micro seconds
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(5000);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH) ;
  distance4= duration4*0.034/2;

  Serial.println("Distance1 =" + String(distance1) + " cm");
  Serial.println("Distance2 =" + String(distance2) + " cm");
  Serial.println("Distance3 =" + String(distance3) + " cm");
  Serial.println("Distance4 =" + String(distance4) + " cm");
}

void fwd_to_Thingspeak()
{
  String postStr = apiKey;
  postStr +="&field1=";
  postStr += String(distance1);  // ultrasonic data
  postStr += "\r\n\r\n";
  
  postStr +="&field2=";
  postStr += String(distance2);  // ultrasonic data
  postStr += "\r\n\r\n";
  
  postStr +="&field3=";
  postStr += String(distance3);  // ultrasonic data
  postStr += "\r\n\r\n";
  
  postStr +="&field4=";
  postStr += String(distance4);  // ultrasonic data
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
         
}

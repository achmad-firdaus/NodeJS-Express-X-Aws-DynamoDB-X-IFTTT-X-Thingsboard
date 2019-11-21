/*
* Achmad Firdaus 
*/
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

IPAddress connecting(192, 168, 43, 23);
 
WiFiClient client;

const char* ssid     = "Your_SSID_WIFI";
const char* password = "Your_PASSWORD_WIFI";

String header;
String outData;
String DKebakaran = "KEBAKARAN";
String DAman = "AMAN";

#define flameSensor3 D0
#define Sound D1
int deteksiSensor3;

void setup() {
  Serial.begin(115200);
  pinMode(Sound,OUTPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
  digitalWrite(Sound,HIGH);
  delay(150);
  digitalWrite(Sound,LOW);
  delay(150);
  digitalWrite(Sound,HIGH);
  delay(150);
  digitalWrite(Sound,LOW);
  delay(150);
}

void loop(){
  client.connect(connecting, 80);
  delay(1000);
  
  digitalWrite(Sound,LOW);   
      deteksiSensor3 = digitalRead(flameSensor3);
        if (deteksiSensor3 == 0){    
//           Serial.println("1");
           client.println("1\r");
           Serial.println("KEBAKARAN");
           digitalWrite(Sound,HIGH);
           delay1();
           }else{
              Serial.println("AMAN");
            }
  client.flush();      
  delay(2000);
}
void delay1(){
  delay(2000);digitalWrite(Sound,LOW);
  delay(500);digitalWrite(Sound,HIGH);
  delay(6000);digitalWrite(Sound,LOW);
  delay(1000);
  }

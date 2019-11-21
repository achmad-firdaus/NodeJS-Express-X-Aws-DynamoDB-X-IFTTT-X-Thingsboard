/*
* Achmad Firdaus 
*/
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

IPAddress Ip(192, 168, 43, 23);
IPAddress Gat(192, 168, 43, 1);
IPAddress Sub(255, 255, 255, 0);
IPAddress Dns(8, 8, 8, 8);

const char* ssid     = "Your_SSID_WIFI";
const char* password = "Your_PASSWORD_WIFI";
const char* deviceName = "1";

// Set web server port 80
WiFiServer server(80);

// Variable HTTP request
String header;
String outData2 = "KEBAKARAN";

unsigned long int a = 1;
unsigned long int outData1;

int deteksiSensor1;
int deteksiSensor2;


void setup() {
  Serial.begin(115200);
  
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(Ip, Gat, Sub, Dns);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  WiFi.mode(WIFI_STA);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  delay(500);
}

void loop(){
  WiFiClient client = server.available();
 if (client) {
    if (client.connected()) {
              String dataMasuk = client.readStringUntil('\r');   
              if(dataMasuk == "1"){
                  outData1 = a++;    
                  delay(500);
                  Serial.println(outData1);
                  delay(1000);
                  String url = "http://192.168.43.208:3000/post?data=";
                  url += outData1;
                  Serial.print("Requesting URL: ");
                  Serial.println(url);
                  HTTPClient http;  //Declare an object of class HTTPClient
                  http.begin(url);  //Specify request destination
                  int httpCode = http.GET();         
                    if (httpCode > 0) { //Check the returning code        
                      String payload = http.getString();   //Get the request response payload
                      Serial.println(payload);                     //Print the response payload
                    }        
                  http.end();   //Close connection
                  delay(10000);  
              }
    delay(1000);
    client.stop();
 }
}

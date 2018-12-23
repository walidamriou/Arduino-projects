/*

- this code display two data i1 and i2 in a url 
- the url is rendom ip address exemple is the ip address of the board is 192.168.1.3  
so you can get the data from http://192.168.1.3:80
- you can change the i1 and i2 by a valures of the sensors so can the i1 change by the valure of A0

developed by Walid Amriou in december 2018

*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
  
 
// Replace with your network credentials
const char* ssid = "Djaweb02928612"; //wifi name
const char* password = "4E248E0909"; //wifi password
int i1,i2; //this valures for test, it like a sensors valures
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = ""; //the webpage valure

void setup(void){
   
delay(1000);
Serial.begin(115200);
WiFi.begin(ssid, password); //begin WiFi connection

Serial.println("");
  
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

server.on("/", [](){
    page = String(i1)+","+String(i2);
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  delay(1000);
  server.handleClient();
  i1++; //for see how the display change when the valure of i1 or i2 change
  i2++;
}

#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include<string>  
ESP8266WebServer server(80);
const char* ssid = "@MBAQBAN";
const char* password = "392417680:AAHGxa8AvSfyHVQ1gCmfTMOw6kXMB5wqu292";
void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);  //Connect to the WiFi network

  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection

    delay(2500);
    Serial.println("Waiting to connect…");

  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP

  server.on("/other", []() {   //Define the handling function for the path

    server.send(200, "text / plain", "Other URL");

  });

  server.on("/", handleRootPath);    //Associate the handler function to the path
  server.on("/reset", handleResetPath);    //Associate the handler function to the path
  server.on("/fragmentation", handleFragPath);    //Associate the handler function to the path
  server.begin();                    //Start the server
  Serial.println("Server listening");

}

void loop() {

  server.handleClient();         //Handling of incoming requests

}
void handleFragPath(){
  String html_page ="<!DOCTYPE html>";
      
  html_page+=      "<html>";
  html_page+=      "<body>";
  html_page+=      "fragmentation : "+String(ESP.getHeapFragmentation())+"</br>";
  html_page+=      "<a href=\"/\">home page</a>";
  html_page+=      "</body>";
  html_page+=      "</html>";

  server.send(200, "text/html",  html_page);

}
void handleResetPath(){

  String html_page ="<!DOCTYPE html>";
      
  html_page+=      "<html>";
  html_page+=      "<body>";
  html_page+=      "rested <a href=\"/\">home page</a>";
  html_page+=      "</body>";
  html_page+=      "</html>";

  server.send(200, "text/html",  html_page);
  delay(1000);
  ESP.restart();
  
}
void handleRootPath() {            //Handler for the rooth path

  String html_page ="<!DOCTYPE html>";
  html_page+=      "<html>";
  html_page+=      "<body>";
  html_page+=      " <h2>commands</h2>";
  html_page+=      " <table style=\"width:100%\">";
  html_page+=          " <tr>";
  html_page+=              " <th></th>";
  html_page+=              " <th></th>";
  html_page+=              " </tr>";
  html_page+=          " <tr>";
  html_page+=              " <td><a href=\"reset\">Reset mudole</a></td>";
  html_page+=              " <td>Heap size : "+String(ESP.getFreeHeap())+"</td>";
  html_page+=              " </tr>";
  html_page+=          " <tr>";
  html_page+=              " <td><a href=\"fragmentation\">Fragmentation</a></td>";
  html_page+=              " <td>Maximum RAM block : "+String( ESP.getMaxFreeBlockSize())+"</td>";
  html_page+=              " </tr>";
  html_page+=          " <tr>";
  html_page+=              " <td>Cheep id : "+String(ESP.getChipId())+"</td>";
  html_page+=              " </tr>";
  html_page+=          " </table>";
  html_page+=      "</body>";
  html_page+=      "</html>";

  server.send(200, "text/html",  html_page);

}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "LittleFS.h";

String ssid = "OMERDEMIRTAS-LA 3167";
String password = "592^06Qy";

ESP8266WebServer server(80);

String getFile(String path)
{
  File file = LittleFS.open(path, "r");
  String data = ""; 

  if(!file){
    Serial.println("Failed to open file for reading");
  }
  else
  {
    while(file.available()){
      data += file.readString();
    }
    file.close();

    return data;
  }
  return data;
}

void setup() {
  Serial.begin(115200);

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("connected..! ");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  //server.on("/", handleOnConnect);
  //server.onNotFound(handleNotFound);
 // Route for root / web page
  server.on("/", HTTP_GET, handleOnConnect);
  server.on("/style.css", HTTP_GET, handleOnStyle);

  
  server.begin();
  
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

void handleOnConnect() {
  server.send(200, "text/html", getFile("/index.html")); 
}

void handleOnStyle() {
  server.send(200, "text/css", getFile("/style.css")); 
}

void handleNotFound(){
  server.send(404, "text/plain", "Not found");
}
 

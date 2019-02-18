/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid = "4A8476";
const char* password = "EVW32C0S00010122";

#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
int senzor = 12;
int senzor2 = 14;
int smoke = A0;


void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(10);
  pinMode (senzor, INPUT);
  pinMode (senzor2, INPUT);
  pinMode(smoke, INPUT);

  
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  int a = digitalRead(senzor);
  int b = digitalRead(senzor2);
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float t = (f-32)*5/9;
  int Sensor = analogRead(smoke);
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  if(client.connected()) {
      Serial.println("Response Sent to Client: A HTML Page");
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html\n");
      client.print("<meta http-equiv=\"refresh\" content=\"2\">");
      client.println("<center><h2>Hello World!!!</h2></center>");
      client.println("<h2>DHT11 ocitanje vlage:</h2>");
      client.println(h);
      client.println("<h2>DHT11 ocitanje temperature:</h2>");
      client.println(t);
      client.println();
      client.print("<h2>Detektor dima: </h2>");
      client.println(Sensor);
      client.println();

      client.println("<h2>Ocitanje ZP01:</h2>");

    if (a == LOW && b == LOW){
      
      client.println("1.slucaj");
      }
    else if((a == HIGH && b == LOW) || (a == LOW && b == HIGH)){
      
      client.println("2.slucaj");
    }
    else if(a == HIGH && b == HIGH){
      
      client.println("3.slucaj");
    }
    
    
  }  
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

#define BLYNK_PRINT Serial

int pin = 0;

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ef8f08b090b545a6a7f20b0b18efd10e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "4A8476";
char pass[] = "EVW32C0S00010122";

void setup() {  
  pinMode(pin, OUTPUT); 

  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

  Blynk.begin("Your auth token key", ssid, pass);

}

void loop(){
    Blynk.run();
}

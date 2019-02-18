
#define BLYNK_PRINT Serial




#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ef8f08b090b545a6a7f20b0b18efd10e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "4A8476";
char pass[] = "EVW32C0S00010122";
int led = 12;
void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  analogWriteFreq(30000);
  pinMode(led, OUTPUT);
}

void loop()
{
  Blynk.run();
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(1000);
}

#include <FastLED.h>
#include <CapacitiveSensor.h>

#define NUM_LEDS 60
#define DATA_PIN 6

CRGB leds[NUM_LEDS];
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4); // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil


const int trigPin = 5;
const int echoPin = 7;
// defines variables
long duration;
int distance;
int ledValue;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 LEDS.setBrightness(150);
    cs_2_4.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example

Serial.begin(9600); // Starts the serial communication
   pinMode(3,OUTPUT);

}
void loop() {
proximity();
traka();

long sensor1 =  cs_2_4.capacitiveSensor(50);

    Serial.println(sensor1);  // print sensor output 
   if(sensor1 >= 1000)
   {
    tone(3,2048);
   }
   else{
    noTone(3);
   }  
}

void proximity()
{

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
}

void traka()
{
  if(distance<=60){
   for(int i=0;i<distance;i++)
 {
  leds[i].setRGB(0,2,253);}
        FastLED.show(); 
        delay(50);
        FastLED.clear();
  }
  else
  FastLED.clear();
  }

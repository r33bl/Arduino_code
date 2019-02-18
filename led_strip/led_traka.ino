#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

int A = 2;
int B = 4;
int i;


void setup()
{
  Serial.begin(9600);
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 LEDS.setBrightness(84);

  pinMode (A, INPUT);
  pinMode (B, INPUT);
  
  }
void loop()
{
    
pic();
delay(500);
}

void pic(){
  int a = digitalRead(A);
  int b = digitalRead(B);
  
  
if(a == LOW && b == LOW){

       for(int i=0;i<NUM_LEDS;i++){
        leds[i].setRGB(0,221,0);}
    
        FastLED.show(); 

      Serial.print("p0.pic=0");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 
       
}

        
if(a == LOW && b == HIGH){

        for(int i=0;i<NUM_LEDS;i++){
        leds[i].setRGB(255,100,0);}
        FastLED.show(); 

      Serial.print("p0.pic=1");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 
       
}


if(a == HIGH && b == LOW){

for(int i=0;i<NUM_LEDS;i++){
        leds[i].setRGB(255,100,0);} 
        FastLED.show(); 

      Serial.print("p0.pic=1");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 
        
}
      


if(a == HIGH && b == HIGH){

for(int i=0;i<NUM_LEDS;i++){
        leds[i].setRGB(255,0,0);}       
        FastLED.show(); 
      Serial.print("p0.pic=2");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 

}

}

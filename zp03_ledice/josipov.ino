int ledPin1 = 9;   
int ledPin2 = 10;
int ledPin3 = 11;
int senzor = 2;
int senzor2 = 4;



void setup()
{
  Serial.begin(9600);

  pinMode (ledPin1, OUTPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (ledPin3, OUTPUT);
  pinMode (senzor, INPUT);
  pinMode (senzor2, INPUT);
}
void loop()
{
  int a = digitalRead(senzor);
  int b = digitalRead(senzor2);
  
  
if (a == LOW && b == LOW){
  
  Serial.print("p0.pic=0");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin2,LOW); 
    digitalWrite(ledPin3,LOW); 

      delay(1000);
       
}

if (a == HIGH && b == LOW){

  Serial.print("p0.pic=1"); 
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,HIGH); 
    digitalWrite(ledPin3,LOW); 
      delay(1000);
        
}
      


if (a == HIGH && b == HIGH){

  Serial.print("p0.pic=2");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff); 
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW); 
    digitalWrite(ledPin3,HIGH); 
      delay(1000);

}
}

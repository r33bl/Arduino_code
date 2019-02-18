



int A = 10 ;
int B = 9;
int r = 5;
int g = 6;
int bl = 7;
int nap=13;



void setup()
{
  Serial.begin(9600);
 

  pinMode (A, INPUT);
  pinMode (B, INPUT);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(bl,OUTPUT);
  pinMode(nap,OUTPUT);


  
  }
void loop()
{ 
   int a = digitalRead(A);
   int b = digitalRead(B);
    digitalWrite(nap,HIGH);
  
if(a == LOW && b == LOW){

      digitalWrite(r,LOW);
        digitalWrite(g,HIGH);
        digitalWrite(bl,LOW);

      Serial.print("p0.pic=0");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 
       
}

        
if(a == LOW && b == HIGH){

        digitalWrite(r,HIGH);
        digitalWrite(g,HIGH);
        digitalWrite(bl,LOW); 

      Serial.print("p0.pic=1");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 
       
}


if(a == HIGH && b == LOW){

        digitalWrite(r,HIGH);
        digitalWrite(g,HIGH);
        digitalWrite(bl,LOW); 

      Serial.print("p0.pic=1");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 
        
}
      


if(a == HIGH && b == HIGH){

        digitalWrite(r,HIGH);
        digitalWrite(g,LOW);
        digitalWrite(bl,LOW);
        
       Serial.print("p0.pic=2");
               Serial.write(0xff);
               Serial.write(0xff);
               Serial.write(0xff); 

}

delay(500);
}

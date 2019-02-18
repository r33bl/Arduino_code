    // On Leonardo/Micro or others with hardware serial, use those!
    // uncomment this line:
    // #define pmsSerial Serial1
     
    // For UNO and others without hardware serial, we must use software serial...
    // pin #2 is IN from sensor (TX pin on sensor), leave pin #3 disconnected
    // comment these two lines if using hardware serial
    #include <SoftwareSerial.h>
    SoftwareSerial pmsSerial(2, 3);
     
    void setup() {
      // our debugging output
      Serial.begin(115200);
     
      // sensor baud rate is 9600
      pmsSerial.begin(9600);
        pinMode (A0, INPUT);
        int sensor_a = 12;
        int sensor_b = 13;
         pinMode (sensor_a, INPUT);
         pinMode (sensor_b, INPUT);
    }
     
    struct pms5003data {
      uint16_t framelen;
      uint16_t pm10_standard, pm25_standard, pm100_standard;
      uint16_t pm10_env, pm25_env, pm100_env;
      uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
      uint16_t unused;
      uint16_t checksum;
    };
     
    struct pms5003data data;
        
    void loop() {

      
/*        
      if (readPMSdata(&pmsSerial)) {
        // reading data was successful!
        //Serial.println();
        //Serial.println("---------------------------------------");
        //Serial.println("Concentration Units (standard)");
        //Serial.print("PM 1.0: "); 
        Serial.print(data.pm10_standard);
        Serial.print(",");
        
        //Serial.print("\t\tPM 2.5: "); 
        Serial.print(data.pm25_standard);
        Serial.print(",");
        
        //Serial.print("\t\tPM 10: "); 
        Serial.print(data.pm100_standard);
        Serial.print(",");
         
        //Serial.println("---------------------------------------");
        //Serial.println("Concentration Units (environmental)");
        //Serial.print("PM 1.0: "); 
        
        Serial.print(data.pm10_env);
        Serial.print(",");
        //Serial.print("\t\tPM 2.5: "); 
        
        Serial.print(data.pm25_env);
        Serial.print(",");        
        //Serial.print("\t\tPM 10: "); 
        Serial.print(data.pm100_env);
        Serial.print(",");
        
        //Serial.println("---------------------------------------");
        //Serial.print("Particles > 0.3um / 0.1L air:"); 
        Serial.print(data.particles_03um);
        Serial.print(",");
        
        //Serial.print("Particles > 0.5um / 0.1L air:"); 
        Serial.print(data.particles_05um);
        Serial.print(",");
        
        //Serial.print("Particles > 1.0um / 0.1L air:"); 
        Serial.print(data.particles_10um);
        Serial.print(",");
        
        //Serial.print("Particles > 2.5um / 0.1L air:"); 
        Serial.print(data.particles_25um);
        Serial.print(",");
        
        //Serial.print("Particles > 5.0um / 0.1L air:"); 
        Serial.print(data.particles_50um);
        Serial.print(",");
                
        //Serial.print("Particles > 10.0 um / 0.1L air:"); 
        Serial.print(data.particles_100um); Serial.print(",");

        
        delay(1000);
        //Serial.println("---------------------------------------");
      }
      
      */
funkcija();
    }
     
    boolean readPMSdata(Stream *s) {
      if (! s->available()) {
        return false;
      }
      
      // Read a byte at a time until we get to the special '0x42' start-byte
      if (s->peek() != 0x42) {
        s->read();
        return false;
      }
     
      // Now read all 32 bytes
      if (s->available() < 32) {
        return false;
      }
        
      uint8_t buffer[32];    
      uint16_t sum = 0;
      s->readBytes(buffer, 32);
     
      // get checksum ready
      for (uint8_t i=0; i<30; i++) {
        sum += buffer[i];
      }
     
      /* debugging
      for (uint8_t i=2; i<32; i++) {
        Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
      }
      Serial.println();
      */
      
      // The data comes in endian'd, this solves it so it works on all platforms
      uint16_t buffer_u16[15];
      for (uint8_t i=0; i<15; i++) {
        buffer_u16[i] = buffer[2 + i*2 + 1];
        buffer_u16[i] += (buffer[2 + i*2] << 8);
      }
     
      // put it into a nice struct :)
      memcpy((void *)&data, (void *)buffer_u16, 30);
     
      if (sum != data.checksum) {
//        Serial.println("Checksum failure");
        return false;
      }
      // success!
      return true;

    }
  void funkcija()
  {
  int c = analogRead(A0);
  int d = c*5/1024;  
  int sensor_a = 12;
  int sensor_b = 13;
  int a = digitalRead(sensor_a);
  int b = digitalRead(sensor_b);

  
    if (readPMSdata(&pmsSerial)) {
        Serial.print(data.pm10_standard);  Serial.print(",");
        Serial.print(data.pm10_standard);  Serial.print(",");

        
        //Serial.print("\t\tPM 2.5: "); 
        Serial.print(data.pm25_standard);  Serial.print(",");

        
        //Serial.print("\t\tPM 10: "); 
        Serial.print(data.pm100_standard);  Serial.print(",");

         
        //Serial.println("---------------------------------------");
        //Serial.println("Concentration Units (environmental)");
        //Serial.print("PM 1.0: "); 
        
        Serial.print(data.pm10_env);  Serial.print(",");
       //Serial.print("\t\tPM 2.5: "); 

        
        Serial.print(data.pm25_env);  Serial.print(",");

        
        //Serial.print("\t\tPM 10: "); 
        Serial.print(data.pm100_env);  Serial.print(",");

        
        //Serial.println("---------------------------------------");
        //Serial.print("Particles > 0.3um / 0.1L air:"); 
        Serial.print(data.particles_03um);    Serial.print(",");

        
        //Serial.print("Particles > 0.5um / 0.1L air:"); 
        Serial.print(data.particles_05um);  Serial.print(",");
        
        //Serial.print("Particles > 1.0um / 0.1L air:"); 
        Serial.print(data.particles_10um);  Serial.print(",");

        
        //Serial.print("Particles > 2.5um / 0.1L air:"); 
        Serial.print(data.particles_25um);  Serial.print(",");

        
        //Serial.print("Particles > 5.0um / 0.1L air:"); 
        Serial.print(data.particles_50um);  Serial.print(",");

        
        //Serial.print("Particles > 10.0 um / 0.1L air:"); 
        Serial.print(data.particles_100um);  Serial.print(",");

        
        delay(1000);
    

  if (a == LOW && b == LOW)
 {
  Serial.print("1,");
  Serial.print(c); Serial.print(",");
  Serial.print(d); Serial.println(",");
  
endNextionCommand();
    }
  if (a == LOW && b == HIGH)
 {
  Serial.print("2,");
  Serial.print(c); Serial.print(",");
  Serial.print(d); Serial.println(",");
  
endNextionCommand();
    }
    
 if (a == HIGH && b == LOW)
 {
  Serial.print("3,");
  Serial.print(c); Serial.print(",");
  Serial.print(d); Serial.println(",");
  
endNextionCommand();
    }
   
 if (a == HIGH && b == HIGH)
 {
  Serial.print("4,");
  Serial.print(c); Serial.print(",");
  Serial.print(d); Serial.println(",");
  
endNextionCommand();
    }
    }
 }
 void endNextionCommand()
  {
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(1000);
  }

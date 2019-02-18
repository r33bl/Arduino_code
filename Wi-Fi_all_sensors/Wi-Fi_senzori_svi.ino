#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(2, 3);

const char* ssid = "4A8476";
const char* password = "EVW32C0S00010122";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
int senzor = 14;
int senzor2 = 16;

void setup() {
  Serial.begin(115200);
  pmsSerial.begin(9600);
  delay(10);
  pinMode (senzor, INPUT);
  pinMode (senzor2, INPUT);

  // prepare GPIO2
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
struct pms5003data {
      uint16_t framelen;
      uint16_t pm10_standard, pm25_standard, pm100_standard;
      uint16_t pm10_env, pm25_env, pm100_env;
      uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
      uint16_t unused;
      uint16_t checksum;
    };
     
    struct pms5003data data;
    String str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12;
    
void loop() {
  int a = digitalRead(senzor);
  int b = digitalRead(senzor2);

        str1 = String(data.pm10_standard);
        str2 = String(data.pm25_standard);
        str3 = String(data.pm100_standard);
        str4 = String(data.pm10_env);
        str5 = String(data.pm10_env);
        str6 = String(data.pm10_env);
        str7 = String(data.particles_03um);
        str8 = String(data.particles_05um);
        str9 = String(data.particles_10um);
        str10 = String(data.particles_25um);
        str11 = String(data.particles_50um);
        str12 = String(data.particles_100um);

        if (readPMSdata(&pmsSerial)) {
        // reading data was successful!
        


        Serial.println();
        Serial.println("---------------------------------------");
        Serial.println("Concentration Units (standard)");
        Serial.print("PM 1.0: "); Serial.print(str1);
        Serial.print("\t\tPM 2.5: "); Serial.print(str2);
        Serial.print("\t\tPM 10: "); Serial.println(str3);
        Serial.println("---------------------------------------");
        Serial.println("Concentration Units (environmental)");
        Serial.print("PM 1.0: "); Serial.print(str4);
        Serial.print("\t\tPM 2.5: "); Serial.print(str5);
        Serial.print("\t\tPM 10: "); Serial.println(str6);
        Serial.println("---------------------------------------");
        Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(str7);
        Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(str8);
        Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(str9);
        Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(str10);
        Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(str11);
        Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(str12);
        Serial.println("---------------------------------------");
      }
      
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
      client.print("<meta http-equiv=\"refresh\" content=\"5\">");
      client.println("<center><h2>Podaci sa senzora</h2></center>");
    if (a == LOW && b == LOW){
      client.println("<h2>Ocitanje ZP01:</h2>");
      client.println("<h2>1.slucaj</h2>");
      }
    else if((a == HIGH && b == LOW) || (a == LOW && b == HIGH)){
      client.println("<center><h2>Ocitanje:</h2></center>");
      client.println("<h2>2.slucaj</h2>");
    }
    else if(a == HIGH && b == HIGH){
      client.println("<center><h2>Ocitanje:</h2></center>");
      client.println("<h2>3.slucaj</h2>");
    }
    
    
   
        client.println();
       client.println("---------------------------------------");
        client.println("<h2>Concentration Units (standard)</h2>");
        client.print("PM 1.0: "); client.print(str1);
        client.print("\t\tPM 2.5: "); client.print(str2);
        client.print("\t\tPM 10: "); client.println(str3);
        client.println("---------------------------------------");
        client.println("<h2>Concentration Units (environmental)</h2>");
        client.print("PM 1.0: "); client.print(str4);
        client.print("\t\tPM 2.5: "); client.print(str5);
        client.print("\t\tPM 10: "); client.println(str6);
        client.println("---------------------------------------");
        client.print("Particles > 0.3um / 0.1L air:"); client.println(str7);
        client.print("Particles > 0.5um / 0.1L air:"); client.println(str8);
        client.print("Particles > 1.0um / 0.1L air:"); client.println(str9);
        client.print("Particles > 2.5um / 0.1L air:"); client.println(str10);
        client.print("Particles > 5.0um / 0.1L air:"); client.println(str11);
        client.print("Particles > 10.0 um / 0.1L air:"); client.println(str12);
       
    
    
  }  
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
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
     

      for (uint8_t i=2; i<32; i++) {
        Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
      }
      Serial.println();
      
      
      // The data comes in endian'd, this solves it so it works on all platforms
      uint16_t buffer_u16[15];
      for (uint8_t i=0; i<15; i++) {
        buffer_u16[i] = buffer[2 + i*2 + 1];
        buffer_u16[i] += (buffer[2 + i*2] << 8);
      }
     
      // put it into a nice struct :)
      memcpy((void *)&data, (void *)buffer_u16, 30);
     
      if (sum != data.checksum) {
        Serial.println("Checksum failure");
        return false;
      }
      // success!
      return true;
    }

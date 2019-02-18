
void setup() {
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int output = digitalRead(0);
  Serial.println(output);

  delay(1000);

}

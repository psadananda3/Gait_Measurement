
void setup() {

  Serial.begin(9600);
}


void loop() {

  int sonic1 = analogRead(A0);
  int pir1 = analogRead(A1);
  int prox1 = analogRead(A2);
  int sonic2 = analogRead(A3);
  int pir2 = analogRead(A4);
  int prox2 = analogRead(A5);
  
  Serial.print(sonic1);
  Serial.print(" ");
  Serial.print(pir1);
  Serial.print(" ");
  Serial.print(prox1);
  Serial.print(" ");
  Serial.print(sonic2);
  Serial.print(" ");
  Serial.print(pir2);
  Serial.print(" ");
  Serial.println(prox2);
  
  delay(50);        
}

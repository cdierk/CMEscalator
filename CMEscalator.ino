// the setup function runs once when you press reset or power the board
//#include <SharpIR.h>
//SharpIR sharp(0, 25, 93, 1080);

void setup() {
  // initialize digital pin 13 as an output
  
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);     // green
  pinMode(10, OUTPUT);     // blue
  pinMode(9, OUTPUT);     // red
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  digitalWrite(5, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
}
 
// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);              // wait for a second

  int dis= analogRead(0);
  analogWrite(5, dis);

  dis= analogRead(1);
  analogWrite(10, dis);
  
  dis= analogRead(2);
  Serial.println(dis);
  analogWrite(9, dis);
  
}


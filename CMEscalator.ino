// the setup function runs once when you press reset or power the board
//#include <SharpIR.h>
//SharpIR sharp(0, 25, 93, 1080);

void setup() {
  // initialize digital pin 13 as an output
  
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);     // green
  pinMode(10, OUTPUT);     // blue
  pinMode(9, OUTPUT);     // red
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
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

  //int dis= map(analogRead(A0), 0, 1023, 0, 255);
  int dis = analogRead(A0);
  int dis2 = analogRead(A1);
  //int dis2= map(analogRead(A1), 0, 1023, 0, 255);
  int dis3= map(analogRead(A2), 0, 1023, 0, 255);

  int linearized = 6787/(dis - 3) - 4;
  int linearized2 = 6787/(dis2 - 3) - 4;
  Serial.print(linearized);
  Serial.print(" ");
  Serial.print(linearized2);
  Serial.print(" ");
  Serial.println(dis3);
//  Serial.println(dis);
//  if (dis > 100){
//    analogWrite(5, HIGH);
//  }
//  else{
//    analogWrite(5,LOW);
//  }
//
//  dis= analogRead(1);
//  if (dis > 100){
//    analogWrite(10, HIGH);
//  }
//  else{
//    analogWrite(10,LOW);
//  }
//  
//  dis= analogRead(2);
//  if (dis > 100){
//    analogWrite(9, HIGH);
//  }
//  else{
//    analogWrite(9,LOW);
//  }

    analogWrite(5, dis);
    analogWrite(10, dis2);
    analogWrite(9, dis3);
}



#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_PIXELS 119
#define DECAY_AMOUNT 50
#define SLOW_DECAY_AMOUNT 3
#define SLOW_DECAY_THRESHOLD 75
#define MAX_PULSES 25
#define PULSE_TIMEOUT 1000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

typedef struct{
  int posIdx;
  int negIdx;
  int r;
  int g;
  int b;
  int alive;
} Pulse;

int R[NUM_PIXELS];
int B[NUM_PIXELS];
int G[NUM_PIXELS];
Pulse pulses[MAX_PULSES];
int numPulses = 0;
unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;
unsigned long timer4 = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void decay(){
  for(int i=0; i<NUM_PIXELS; i++){
    if(R[i] > SLOW_DECAY_THRESHOLD){
      R[i] -= DECAY_AMOUNT; 
    } else {
      R[i] -= SLOW_DECAY_AMOUNT;
    }
    R[i] = R[i] < 0 ? 0 : R[i];
    
    if(G[i] > SLOW_DECAY_THRESHOLD){
      G[i] -= DECAY_AMOUNT; 
    } else {
      G[i] -= SLOW_DECAY_AMOUNT;
    }
    G[i] = G[i] < 0 ? 0 : G[i];
    
    if(B[i] > SLOW_DECAY_THRESHOLD){
      B[i] -= DECAY_AMOUNT; 
    } else {
      B[i] -= SLOW_DECAY_AMOUNT;
    }
    B[i] = B[i] < 0 ? 0 : B[i];
  }
}

void setValues(){
  for(int i=0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, R[i], G[i], B[i]);
  }
  strip.show();
}

void updatePulses(){
  for(int i=0; i<numPulses; i++){
    Pulse p = pulses[i];

    if(p.posIdx < NUM_PIXELS){
      R[p.posIdx] += p.r;
      G[p.posIdx] += p.g;
      B[p.posIdx] += p.b;
      R[p.posIdx] = R[p.posIdx] > 255 ? 255 : R[p.posIdx];
      G[p.posIdx] = G[p.posIdx] > 255 ? 255 : G[p.posIdx];
      B[p.posIdx] = B[p.posIdx] > 255 ? 255 : B[p.posIdx];
      p.posIdx += 1;
    }

    if(p.negIdx >= 0){
      R[p.negIdx] += p.r;
      G[p.negIdx] += p.g;
      B[p.negIdx] += p.b;
      R[p.negIdx] = R[p.negIdx] > 255 ? 255 : R[p.negIdx];
      G[p.negIdx] = G[p.negIdx] > 255 ? 255 : G[p.negIdx];
      B[p.negIdx] = B[p.negIdx] > 255 ? 255 : B[p.negIdx];
      p.negIdx -= 1;
    }
    
    if(p.posIdx >= NUM_PIXELS && p.negIdx < 0){
      p.alive = 0;
    }
    
    pulses[i] = p;
  }
}

void garbageCollect(){
  Pulse newPulses[MAX_PULSES];
  int newIdx = 0;
  //find all the alive pulses and put them in a new array
  for(int i=0; i<numPulses; i++){
    Pulse p = pulses[i];
    if(p.alive == 1){
      newPulses[newIdx] = {p.posIdx, p.negIdx, p.r, p.g, p.b, p.alive};
      newIdx+=1;
    }
  }
  //replace the old array with the new array
  for(int i=0; i<MAX_PULSES; i++){
    pulses[i] = newPulses[i];
  }
  numPulses = newIdx;
}

void createNewPulses(){
  int startLoc[4] = {0, 30, 60, 90};

  int dis = analogRead(A0);
  int dis2 = analogRead(A1);
  int dis3 = analogRead(A2);
  int dis4 = analogRead(A3);

  int linearized = 6787/(dis - 3) - 4;
  int linearized2 = 6787/(dis2 - 3) - 4;
  int linearized3 = 6787/(dis3 - 3) - 4;
  int linearized4 = 6787/(dis4 - 3) - 4;

  if(numPulses < MAX_PULSES && linearized < 10 && millis()-timer1 > PULSE_TIMEOUT){
    pulses[numPulses] = {startLoc[0], startLoc[0], 255, 255, 0, 1};
    numPulses+=1;
    timer1 = millis();
  }
  if(numPulses < MAX_PULSES && linearized2 < 10 && millis()-timer2 > PULSE_TIMEOUT){
    pulses[numPulses] = {startLoc[1], startLoc[1], 0, 255, 255, 1};
    numPulses+=1;
    timer2 = millis();
  }
  if(numPulses < MAX_PULSES && linearized3 < 10 && millis()-timer3 > PULSE_TIMEOUT){
    pulses[numPulses] = {startLoc[2], startLoc[2], 255, 0, 255, 1};
    numPulses+=1;
    timer3 = millis();
  }
  if(numPulses < MAX_PULSES && linearized4 < 10 && millis()-timer4 > PULSE_TIMEOUT){
    pulses[numPulses] = {startLoc[3], startLoc[3], 0, 255, 0, 1};
    numPulses+=1;
    timer4 = millis();
  }
  
  /*int randNum = random(10);
  if(randNum < 2 && numPulses < MAX_PULSES){  // 20% chance to create a new pulse
    randNum = random(3);
    if(randNum == 0){
      pulses[numPulses] = {startLoc[0], startLoc[0], 255, 0, 0, 1};
    }
    else if(randNum == 1){
      pulses[numPulses] = {startLoc[1], startLoc[1], 0, 255, 0, 1};
    }
    else if(randNum == 2){
      pulses[numPulses] = {startLoc[2], startLoc[2], 0, 0, 255, 1};
    }
    numPulses += 1;
  }*/
}

void loop() {
  decay();

  createNewPulses();

  updatePulses();
  
  setValues();

  garbageCollect();
  
  delay(125);
}


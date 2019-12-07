#include "buzzer.h"

#define PIN_BUZZER 6
#define ECHO_PIN 8
#define TRIG_PIN 9

int freqs[] = {31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978};
const int minDist = 10;
int freqCount = sizeof(freqs) / sizeof(freqs[0]);

void setup()
{
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(115200);
}

void loop() {
  float result = readDist();
  Serial.println(result);
  delay(150);

  int freq = getFreq(round(result));
  tone(PIN_BUZZER, freq);
}

int getFreq(int distance)
{
  if(distance < minDist) {return freqs[0];}
  else if(distance > minDist + freqCount) {return freqs[freqCount - 1];}
  else {return freqs[distance - minDist];};
  return 0;
}

float readDist()
{
  const float speedOfSoundMPerSec = 340.0;
  const float speedOfSoundCmPerUs = speedOfSoundMPerSec / 10000.0;
  return readPulse() * speedOfSoundCmPerUs / 2.0;    
}

float readPulse()
{
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  return duration;
}

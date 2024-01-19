#include <SD.h>
#include <TMRpcm.h>

#define SD_CS_PIN 10
#define TRIGGER_PIN 9
#define ECHO_PIN 8

TMRpcm tmrpcm;//code by kushal poudel 

void setup() {
  Serial.begin(9600);
  tmrpcm.speakerPin = 11; // Pin connected to the amplifier module
  tmrpcm.setVolume(5);    // Adjust volume (0 to 7, 0 being the lowest)
  
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  
  distance = duration * 0.034 / 2;
  
  if (distance < 20) { // Adjust this threshold as per your requirement
    playSoundFromSDCard("welcome.wav");
  }
  
  delay(200); // Adjust delay as per your requirement
}

void playSoundFromSDCard(const char* fileName) {
  if (!SD.exists(fileName)) {
    Serial.println("File not found!");
    return;
  }
  
  tmrpcm.setVolume(5); // Adjust volume if necessary
  
  if (!tmrpcm.isPlaying()) {
    tmrpcm.play(fileName);
  }
}

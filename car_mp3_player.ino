// Include required libraries
#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// microSD Card Reader connections
#define SD_CS 5
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK 18

// I2S Connections
#define I2S_DOUT 22 // Pin DIN para I2S
#define I2S_BCLK 26 // Pin BCLK para I2S
#define I2S_LRC 25 // Pin LRCLK para I2S

// Create Audio object
Audio audio;

void setup() {
  // Set microSD Card CS as OUTPUT and set HIGH
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  // Initialize SPI bus for microSD Card
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

  // Start Serial Port
  Serial.begin(115200);

  // Start microSD CArd
  if(!SD.begin(SD_CS)) {
    Serial.println("Error accessing microSD card!");
    while(true);
  }

  // Setup I2S 
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Set Volume
  audio.setVolume(1.0);

  // Open music file
  audio.connecttoFS(SD, "/1.mp3");
}

void loop() {
  audio.loop();
}
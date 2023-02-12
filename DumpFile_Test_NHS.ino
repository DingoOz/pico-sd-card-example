/*
  SD card file dump

  This example displays the contents of a file "datalog.txt" which needs to be
  prepared on the SD card ahead of time.
  Shows how to read a file from the SD card using the
  SD library and send it over the serial port.

  The circuit:
   SD card attached to SPI bus as follows:
   ** MISO      - GPIO 12
   ** CS        - GPIO 13
   ** SCK/CLK   - GPIO 14
   ** MOSI      - GPIO 15

   Chip Select is set directly in the SD.being() routine call. 
   Remaining pins are set via use of Pico SPI1 hardware.
  created  22 December 2010
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe
  modified 12 Feb 2023 
  by Nigel Hungerford-Symes (for pico)

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 9;

void setup() {
    
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  delay(3000);  // Let serial monitor catch up.

  Serial.print("Initializing SD card program...");

  // see if the card is present and can be initialized:
  if (!SD.begin(13,SPI1)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("SD Card initialized. Displaying contents of 'datalog.txt'");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("Error opening datalog.txt");
  }
}

void loop() {
}


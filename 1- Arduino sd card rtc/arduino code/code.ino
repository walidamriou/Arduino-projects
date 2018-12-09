    /*
     *  Arduino Read from the sensors and save it to the SD Card
     *  
     *  by Walid Amriou
     */
    #include <SD.h>
    #include <SPI.h>
    #include <Wire.h>
    #include "RTClib.h"

    //we save the data to text file in the sd care
    File File_txt;
    int pinCS = 10;

    //the sensors 
    int sensor1 = A0;    
    int sensor2 = A1;    
    int sensor3 = A2;    
    int sensor4 = A3;   
    
    int sensorValue1 = 0;  // variable to store the value coming from the sensor1
    int sensorValue2 = 0;  // variable to store the value coming from the sensor2
    int sensorValue3 = 0;  // variable to store the value coming from the sensor3
    int sensorValue4 = 0;  // variable to store the value coming from the sensor4

    /*
    just valures for store the time
    A for year
    B month
    C day
    E hour
    F minute
    G second
    */
    int A,B,C,D;    
    int E,F,G;

    //we use a RTC to get current time
    RTC_DS1307 rtc;

     
    void setup() {
        
      Serial.begin(9600);
      pinMode(pinCS, OUTPUT);
      
      // SD Card Initialization
      if (SD.begin())
      {
        Serial.println("SD card is ready to use.");
      } else
      {
        Serial.println("SD card initialization failed");
        return;
      }

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
      

      
    }
    void loop() {
      // get the data from the sensors
      sensorValue1 = analogRead(sensor1);
      sensorValue2 = analogRead(sensor2);
      sensorValue3 = analogRead(sensor3);
      sensorValue4 = analogRead(sensor4);

    
    DateTime now = rtc.now();
    
    A=now.year();
    B=now.month();
    C=now.day();
    E=now.hour();
    F=now.minute();
    G=now.second();



       // Create/Open file 
      File_txt = SD.open("data2.txt", FILE_WRITE); //open the test.txt as a file for write
      // if the file opened okay, write to it:
      if (File_txt) {
        Serial.println("Writing to file...");
        // Write to file
        File_txt.print(A);
        File_txt.print("/ ");
        File_txt.print(B);
        File_txt.print(" / ");
        File_txt.print(C);
        File_txt.print("   ");
        File_txt.print(", ");



        File_txt.print(E);
        File_txt.print(":");
        File_txt.print(F);
        File_txt.print(":");
        File_txt.print(G);
        File_txt.print("   ");
        File_txt.print(", ");


        File_txt.print((sensorValue1/2)-1);
        File_txt.print(", ");
        File_txt.print((sensorValue2/2)-1);
        File_txt.print(", ");
        File_txt.print((sensorValue3/2)-1);
        File_txt.print(", ");
        File_txt.println((sensorValue4/2)-1);
        
        File_txt.close(); // close the file
        Serial.println("Done.");
      }
      // if the file didn't open, print an error:
      else {
        Serial.println("error opening data2.txt");
      }
      // Reading the file
      File_txt = SD.open("data2.txt");
      if (File_txt) {
        Serial.println("Read:");
        // Reading the whole file
        while (File_txt.available()) {
          Serial.write(File_txt.read());
       }
        File_txt.close();
      }
      else {
        Serial.println("error opening data2.txt");
      }

      delay(5000);
    }

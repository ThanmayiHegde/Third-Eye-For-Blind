//include Tone.h lib, that enables playing diffrent sounds on multiple buzzers by using Tone objects
#ifndef _Tone_h
#define _Tone_h

#include <stdint.h>

/*
|| Public Constants
*/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


/*
|| Definitions
*/

class Tone
{
  public:
    void begin(uint8_t tonePin);
    bool isPlaying();
    void play(uint16_t frequency, uint32_t duration = 0);
    void stop();

  private:
    static uint8_t _tone_pin_count;
    uint8_t _pin;
    int8_t _timer;
};

#endif

//define the pins you want to connect to the sensors and buzzers
//if you want to use more then two sensors, define them the same way as sensor 1 and 2 where defined

//pins, that are connected to "trigger" of ultrasonic sensors
#define TRIGGER1 7
#define TRIGGER2 5

//pins, that are connected to "echo" of ultrasonic sensors
#define ECHO1 6
#define ECHO2 3

// pins, that are connected to "+" pin of buzzers
#define BUZZ1 9
#define BUZZ2 10

//define your global variables

//define one Tone object for every buzzer you want to use
Tone tone1;
Tone tone2;

//define one long for every sensor you want to use and the distance it measures
long distance1=0; 
long distance2=0;

//define one long for every sensor you want to use. Using these make it possible to run the buzzers simultaneously.
long t1=-10000;
long t2=-10000;

//declare the funtions, we'll be using

//checkDistance will check if the given distance is lower then 200 cm. If it is lower then 200 cm, it plays a tone on the buzzer that is connected with the given tone object.
//The length of the tone depends on how close the object is to the sensor.

void checkDistance(long distance, int frequency, long *timer);

//measure will measure and return the distance between the sensor and an object in the way of the sensor in cm. If theres no object within two meter, it will return 0.

long measure(int trigger, int echo);

//setup the pins and connect the tone objects to the buzzers
void setup(){
  pinMode(5, OUTPUT); 
  pinMode(4, INPUT); 
  pinMode(7, OUTPUT); 
  pinMode(6, INPUT);
  Serial.begin(9600);

  
  
}

//constantly measure the distances and checks, if it is necessary to play a tone or not
void loop()
{
  distance2 = measure(5, 4);
  Serial.print(distance2);
  Serial.print("\n");
  distance1 = measure(7, 6);
  Serial.print(distance1);
  checkDistance(distance2, 440, &t1);
  checkDistance(distance1, 440, &t1);
  
  
}


long measure(int trigger, int echo){
  long duration = 0;
  digitalWrite(trigger, LOW);  
  delay(5); 
  digitalWrite(trigger, HIGH); 
  delay(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH,11662); 
  return (duration/2) * 0.03432; 
}

void checkDistance(long distance, int frequency, long *timer){
  if(distance<200&&distance>0){
    if(millis()-*timer > long(5.4*distance-81)||distance<15){
      *timer=millis();
      tone(BUZZ1,220,100);
    }
    
  }
  
}
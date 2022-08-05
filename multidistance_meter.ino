int trigger_pin = 7;
int echo_pin = 6;
int buzzer_pin = 11; 
int time;
int distance; 
void setup() 
{
        Serial.begin (9600); 
        pinMode (trigger_pin, OUTPUT); 
        pinMode (echo_pin, INPUT);
        pinMode (11, OUTPUT);
}
void loop() 
{
    digitalWrite (trigger_pin, HIGH);
    delayMicroseconds (10);
    digitalWrite (trigger_pin, LOW);
    time = pulseIn (echo_pin, HIGH);
    distance = (time * 0.034) / 2;

  if (distance <= 100) 
        {
        Serial.println (" Object is near ");
        Serial.print (" Distance= ");              
        Serial.println (distance);        
        digitalWrite (11, HIGH);
        delay (500);
        }
  else {
        Serial.println (" object is far ");
        Serial.print (" Distance= ");              
        Serial.println (distance);        
        digitalWrite (buzzer_pin, LOW);
        delay (500);        
       } 
}
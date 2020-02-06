#include <HCSR04.h>

HCSR04 hc(26,14);//initialisation class HCSR04 (trig pin , echo pin)  
 //trig = output(sensor send wave) , echo = input (arduino receive so INPUT OF Arduino)

void setup()
{ Serial.begin(9600); }

void loop()
{ Serial.println( hc.dist() ); }//return curent distance in serial

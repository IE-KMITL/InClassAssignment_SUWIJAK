#include <HCSR04.h>
HCSR04 hc(8,9); //initialisation class HCSR04 (trig,echo);
#define ia1 3 //motor 1 เดินหน้า
#define ia2 4 //moter 1 ถอยหลัง
#define ib1 5 //motor 2 เดินหน้า
#define ib2 6 //motor 2 ถอยหลัง
#define S2 11 // Sensor left
#define S3 10 // Sensor right
#define maxSpd 255    // motor max speed


void setup() {
  pinMode(ia1, OUTPUT);
  pinMode(ia2, OUTPUT);
  pinMode(ib1, OUTPUT);
  pinMode(ib2, OUTPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  Serial.begin(9600);
 
 
}

void loop() {
  int speed = maxSpd;
  Sensor1();
  Sensor2();
  Sensor3();


}
void Sensor1() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc.dist() ); //showdistantfromfront
    if((hc.dist()>=5) && (hc.dist()<=10)){
       Slow(speed);}
    else if ((hc.dist()>=3) && (hc.dist()<5)){
        Break();}
    else if ((hc.dist()>=0) && (hc.dist()<3)){
        Reward(speed);}
    else{
        Forward(speed);}
}
void Sensor2(){
    int speed = maxSpd;
  if(digitalRead(S2)==LOW){
        Serial.println("sensor detected object from left side");
        delay(200);   
        Turnleft(speed);} 
   else{
    Forward;
   }
}
void Sensor3(){
    int speed = maxSpd;
  if(digitalRead(S3)==LOW){
        Serial.println("sensor detected object from right side");
        delay(200);   
        TurnRight(speed);} 
        else{
    Forward(speed);
        }
}

void Break() // motor break
{
  digitalWrite(ia1, HIGH);   
  digitalWrite(ia2, HIGH);  
  digitalWrite(ib1, HIGH);   
  digitalWrite(ib2, HIGH);   
}


void Forward(int speed) //goforward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed); 
}
void Slow(int speed) //goforwardwithSlowspeed
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.3);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.3); 
}

void Reward(int speed) //goReward
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed);   
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed);  

}
void Turnleft(int speed) //turnleftandgoforward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.7); //leftforward
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.3);  //rightreward
}
void TurnRight(int speed) //turnrightandgoforward
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed*0.3); //leftreward
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.7);  //rightforward
 
}

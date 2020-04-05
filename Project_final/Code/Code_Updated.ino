#include <HCSR04.h>
HCSR04 hc(8,9); //initialisation class HCSR04 (trig,echo);
#define ia1 3 //motor 1 เดินหน้า
#define ia2 4 //moter 1 ถอยหลัง
#define ib1 5 //motor 2 เดินหน้า
#define ib2 6 //motor 2 ถอยหลัง


#define ls 11 //sensorซ้าย
#define rs 10 //sensorขวา
#define bs 13 //sensorหลัง

#define RED 1
#define YELLOW 2
#define BLACK 3
#define Number_color 0
#define maxSpd 255    // motor max speed



int sensor_color = A0; 

int led1 = D27;
int buttonPin = D29;
int val=0;
int old_val=0;
int state=0;

int color=0;
int getColor() {
  int Number_color = analogRead(sensor_color);                      
  if ((Number_color>2200)&&(Number_color<2500))       //สีแดง
    return RED;
  else if ((Number_color>1900)&&(Number_color<2200))  //สีเหลือง
    return YELLOW;
  else if ((Number_color>3600)&&(Number_color<3900))  //สีดำ
    return BLACK;
  else                                        //ไม่พบสี
    return Number_color;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(bs, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(led1, OUTPUT); 
  pinMode(ia1, OUTPUT);
  pinMode(ia2, OUTPUT);
  pinMode(ib1, OUTPUT);
  pinMode(ib2, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{ 
 color = getColor();
 val = digitalRead(buttonPin);
 if( (val==HIGH) && (old_val==LOW)) 
 {
  state=!state;
 }
 old_val=val;
 if (state==1) //เมื่อกดสวิทซ์ 1 ครั้ง ใช้กลยุทธ์รุก
 {
  digitalWrite(led1, HIGH);
  if(color == Number_color) // sensor ด้านล่างไม่ทำงาน
  {
    if((hc.dist()>10)&&((digitalRead(ls)==HIGH)||(digitalRead(rs)==HIGH)))  // เดินหน้าเมื่อ sensor ด้านหน้า และ ด้านข้าง ไม่ทำงาน
    {
    aForward(maxSpd);
    bForward(maxSpd);
    }
  
    if((hc.dist()<10)&&((digitalRead(ls)==HIGH)||(digitalRead(rs)==HIGH)))  // break เมื่อ sensor ด้านหน้าทำงาน แต่ด้านข้างไม่ทำงาน
    {
    aBreakTime(1000);
    bBreakTime(1000); 
    }

    if((hc.dist()<10)&&((digitalRead(ls)==LOW)||(digitalRead(rs)==LOW)))  // เดินถอยหลัง 3วิ เมื่อ sensor ด้านหน้าและข้างซ้ายขวาทำงาน
    {
    aBackwardTime(3000);
    bBackwardTime(3000);
    }
  }
  
  if(color == RED)  // เดินกลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีแดงได้
  {
  aForwardTime(5000);
  bBackwardTime(5000);
  }

  if(color == YELLOW)  // รถหยุด เมื่อ sensor ด้านล่างตรวจจับเส้นสีเหลืองได้
  {
  aStop();
  bStop();
  }
 }
 else 
 {
  digitalWrite (led1,LOW); // เข้าสู้ฝ่ายรับ ( DEFENDER )
  if(color == Number_color)
  {
    if((hc.dist()<5)&&((digitalRead(ls)==HIGH)||(digitalRead(rs)==HIGH))&&(digitalRead(bs)==HIGH))  // ถอยหลัง ในกรณี sensor ด้านหน้าทำงาน และด้านข้างและด้านหลังไม่ทำงาน
    {
    aBackward(maxSpd);
    bBackward(maxSpd);
   }

    if((hc.dist()>5)&&((digitalRead(ls)==HIGH)||(digitalRead(rs)==HIGH))&&(digitalRead(bs)==LOW)) // เดินหน้าเมื่อ sensor ด้านหลังทำงาน แต่ด้านหน้าและด้านข้างไม่ทำงาน
    {
    aForwardTime(3000); 
    bForwardTime(3000);
    }
  
    if((hc.dist()>5)&&(digitalRead(ls)==LOW)||(digitalRead(rs)==LOW)&&(digitalRead(bs)==HIGH))  // เบรค เมื่อ sensor ด้านข้างซ้ายหรือขวาทำงาน แต่ ด้านหน้าและหลังไม่ทำงาน
    {
    aBreakTime(1000);
    bBreakTime(1000); 
    } 
    if((hc.dist()<5)&&(digitalRead(ls)==LOW)||(digitalRead(rs)==LOW)&&(digitalRead(bs)==HIGH)) // ถอยหลังช้าๆ เมื่อ sensor ด้านขวาหรือซ้ายทำงาน และ ด้านหน้าทำงาน และด้านหลังไม่ทำงาน
    {
      BackwardSlowly(maxSpd);
    }
     if((hc.dist()>5)&&(digitalRead(ls)==LOW)||(digitalRead(rs)==LOW)&&(digitalRead(bs)==LOW)) // เดินหน้าช้าๆ เมื่อ sensor ด้านซ้ายหรือขวาทำงาน และ ด้านหลังทำงาน และด้านหน้าไม่ทำงาน
     {
      ForwardSlowly(maxSpd);
     }
  }
    
  if(color == BLACK)  // กลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีดำได้
  {
  aForwardTime(5000);
  bBackwardTime(5000);
  }
  
  }
  delay(20);
       
}

void aStop()
{
  digitalWrite(ia1, LOW);   // motor stop
  digitalWrite(ia2, LOW);    
}

void aBreak()
{
  digitalWrite(ia1, HIGH);   // motor break
  digitalWrite(ia2, HIGH);    
}

void bStop()
{
  digitalWrite(ib1, LOW);   // motor stop
  digitalWrite(ib2, LOW);    
}

void bBreak()
{
  digitalWrite(ib1, HIGH);   // motor break
  digitalWrite(ib2, HIGH);    
}

void aForward(int speed)
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed);   
}

void bForward(int speed)
{
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed);   
}

void aBackward(int speed)
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed);   
}

void bBackward(int speed)
{
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed);   
}

void aBackwardTime(int time)
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, maxSpd);
  delay (time);   
}

void bBackwardTime(int time)
{
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, maxSpd);
  delay (time);    
}

void aForwardTime(int time)
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, maxSpd);
  delay (time);    
}

void bForwardTime(int time)
{
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, maxSpd);
  delay (time);    
}

void aBreakTime(int time)
{
  digitalWrite(ia1, HIGH);   
  digitalWrite(ia2, HIGH);
  delay (time);    
}

void bBreakTime(int time)
{
  digitalWrite(ib1, HIGH);   
  digitalWrite(ib2, HIGH);
  delay (time);
      
}
void ForwardSlowly(int speed) //goforwardwithSlowspeed
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed*0.3);   
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.3); 
}
void BackwardSlowly(int speed) //gobackwardwithSlowspeed
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.3);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.3); 
}

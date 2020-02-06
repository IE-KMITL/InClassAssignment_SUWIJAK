int led = 19;
int sensor = 13;
int val = 0;
void setup() {
  pinMode(led, OUTPUT);  
  pinMode(sensor, INPUT); 
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sensor);  
  Serial.print("val = "); 
  Serial.println(val); 
  if (val == 0) { 
    digitalWrite(led, HIGH); 
  }
  else {
    digitalWrite(led, LOW); 
  }
  delay(100);
}

/* LED ติดเมื่อตรวจพบกระดาษสีขาวในระยะ 15 cm ดับเมื่อตรวจไม่พบหรือวัตถุอยู่ไกลกว่า 15 cm และเมื่อทดลองกับวัตถุชนิดต่างๆ 5 ชนิดได้แก่ 
 1.เคสไอแพดสีชมพูอ่อนไฟติดในระยะ 12 cm,
 2.เคสไอแพดสีดำติดในระยะ 4 cm
 3.บัตรสีเหลืองไฟติดในระยะ 13 cm
 4.หมวกสีแดงไฟติดในระยะ 11 cm
 5.หนังสือสีส้มไฟติดในระยะ 12 cm */

 

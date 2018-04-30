#include <Servo.h>  // Servo 라이브러리를 불러옵니다.
Servo myservo;  // Servo를 따르는 객체명을 정합니다.

void setup() 
{ 
  myservo.attach(8);  // myservo는 9번핀에 의해 컨트롤 됨을 설정합니다.
}

void loop() 
{ 
    for (int i=0; i<=87; i++) //180도로 돌아감
    {
     myservo.write(i);  // myservo는 i 값만큼의 각도를 갖습니다. 
        delay(1000);
    }
    myservo.write(0);
    delay(3600000);   
}

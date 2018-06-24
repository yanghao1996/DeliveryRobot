
#define encoder0PinA  2
#define encoder0PinB  3
#define encoder0PinA2  18
#define encoder0PinB2  19
#define encoder0PinA3  20
#define encoder0PinB3  21

volatile unsigned int encoder0Pos = 0;
volatile unsigned int encoder0Pos2 = 0;
volatile unsigned int encoder0Pos3 = 0;
volatile unsigned int encoder0Pos4 = 0;
volatile unsigned int encoder0Pos5 = 0;
volatile unsigned int encoder0Pos6 = 0;

volatile unsigned int count = 0;
volatile unsigned int count2 = 0;
volatile unsigned int count3 = 0;
volatile unsigned int count4 = 0;
volatile unsigned int count5 = 0;
volatile unsigned int count6 = 0;


String str;
char isRotate;
char second;
char third;
int steps = 0;
void setup() {
  for (int i = 6; i < 12; i++)
    pinMode(i, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(encoder0PinA2, INPUT);
  pinMode(encoder0PinB2, INPUT);
  pinMode(encoder0PinA3, INPUT);
  pinMode(encoder0PinB3, INPUT);
  Serial.begin(9600);



}

void loop() {
  if (Serial.available() > 0) {
    str = Serial.readStringUntil('\n');
    //Serial.println(11111111);
    //解析串口传来的字符串
    isRotate = str[0];
    second = str[1];
    third = str[2];
    //初始化计数器
    count = count2 = count3 = 0;
    count4 = count5 = count6 = 0;
    encoder0Pos = encoder0Pos2 = encoder0Pos3 = encoder0Pos4 = encoder0Pos5 = encoder0Pos6 = 0;
    //旋转指令
    if (isRotate == '0') {
        //连接外部中断
        attachInterrupt(0, doEncoderA, CHANGE);
        attachInterrupt(2, doEncoderA2, CHANGE);
        attachInterrupt(4, doEncoderA3, CHANGE);

        // encoder pin on interrupt 1 (pin 3)
        attachInterrupt(1, doEncoderB, CHANGE);
        attachInterrupt(3, doEncoderB2, CHANGE);
        attachInterrupt(5, doEncoderB3, CHANGE);
        digitalWrite(13, HIGH);
        analogWrite(6, 20);
        digitalWrite(7, LOW);
        analogWrite(8, 20);
        digitalWrite(9, LOW);
        analogWrite(10, 20);
        digitalWrite(11, LOW);
        delay(1000);
      
    }
    //直行指令
    if (isRotate == '1') {
      if ((second - '0') >= 0 && (second - '0') <= 9) {
        steps += (second - '0') * 16;
      }
      if ((second - 'A') >= 0 && (second - 'A') <= 5) {
        steps += (second - 'A' + 10) * 16;
      }
      if ((third - '0') >= 0 && (third - '0') <= 9) {
        steps += third - '0';
      }
      if ((third - 'A') >= 0 && (third - 'A' <= 5)) {
        steps += third - 'A' + 10;
      }
      goStraight(steps);
    }
  }
}
//直行函数
void goStraight(int steps) {
  digitalWrite(13, HIGH);
  digitalWrite(6, LOW);//一号电机
  digitalWrite(7, LOW);
  analogWrite(9, 50); //三号电机，逆时针
  digitalWrite(8, LOW);
  analogWrite(10, 50); //二号电机,顺时针
  digitalWrite(11, LOW);
  delay(1852 * steps);
  digitalWrite(13, LOW);
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW正转脉冲信号
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW反转脉冲信号
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  if (encoder0Pos >= 200) {
    //digitalWrite(13, LOW);
    encoder0Pos = 0;
    count++;
  }
  if (second == '0') {
    if (third == '0') {
      if ((isRotate == '0') && count == 7) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count == 10) {
        digitalWrite(13, LOW);
      }
    }
  }
  if (second == '1') {
    if (third == '0') {
      if ((isRotate == '0') && count == 35) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count == 30) {
        digitalWrite(13, LOW);
      }
    }
  }

  //Serial.println (encoder0Pos, DEC);
  // use for debugging - remember to comment out
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderA2() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA2) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB2) == LOW) {
      encoder0Pos2 = encoder0Pos2 + 1;         // CW
    }
    else {
      encoder0Pos2 = encoder0Pos2 - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB2) == HIGH) {
      encoder0Pos2 = encoder0Pos2 + 1;          // CW
    }
    else {
      encoder0Pos2 = encoder0Pos2 - 1;          // CCW
    }
  }
  if (encoder0Pos2 >= 200) {
    //digitalWrite(13, LOW);
    encoder0Pos2 = 0;
    count2++;
  }
  if (second == '0') {
    if (third == '0') {
      if ((isRotate == '0') && count2 == 7) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count2 == 10) {
        digitalWrite(13, LOW);
      }
    }
  }
   if (second == '1') {
    if (third == '0') {
      if ((isRotate == '0') && count2 == 35) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count2 == 30) {
        digitalWrite(13, LOW);
      }
    }
  //Serial.println (encoder0Pos2, DEC);
  // use for debugging - remember to comment out
}
}
void doEncoderB2() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB2) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA2) == HIGH) {
      encoder0Pos2 = encoder0Pos2 + 1;         // CW
    }
    else {
      encoder0Pos2 = encoder0Pos2 - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA2) == LOW) {
      encoder0Pos2 = encoder0Pos2 + 1;          // CW
    }
    else {
      encoder0Pos2 = encoder0Pos2 - 1;          // CCW
    }
  }
}
void doEncoderA3() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA3) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB3) == LOW) {
      encoder0Pos3 = encoder0Pos3 + 1;         // CW
    }
    else {
      encoder0Pos3 = encoder0Pos3 - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB3) == HIGH) {
      encoder0Pos3 = encoder0Pos3 + 1;          // CW
    }
    else {
      encoder0Pos3 = encoder0Pos3 - 1;          // CCW
    }
  }
  //Serial.println (encoder0Pos3, DEC);
  if (encoder0Pos3 >= 200) {
    //digitalWrite(13, LOW);
    encoder0Pos3 = 0;
    count3++;
  }
  if (second == '0') {
    if (third == '0') {
      if ((isRotate == '0') && count3 == 7) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count3 == 10) {
        digitalWrite(13, LOW);
      }
    }
  }
   if (second == '1') {
    if (third == '0') {
      if ((isRotate == '0') && count3 == 35) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count3 == 30) {
        digitalWrite(13, LOW);
      }
    }}
  //use for debugging - remember to comment out
}

void doEncoderB3() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB3) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA3) == HIGH) {
      encoder0Pos3 = encoder0Pos3 + 1;         // CW
    }
    else {
      encoder0Pos3 = encoder0Pos3 - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA3) == LOW) {
      encoder0Pos3 = encoder0Pos3 + 1;          // CW
    }
    else {
      encoder0Pos3 = encoder0Pos3 - 1;          // CCW
    }
  }
}
/*
void do_EncoderB() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos4 = encoder0Pos4 + 1;         // CW正转脉冲信号
    }
    else {
      encoder0Pos4 = encoder0Pos4 - 1;         // CCW反转脉冲信号
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos4 = encoder0Pos4 + 1;          // CW
    }
    else {
      encoder0Pos4 = encoder0Pos4 - 1;          // CCW
    }
  }
  if (encoder0Pos4 >= 100) {
    //digitalWrite(13, LOW);
    encoder0Pos4 = 0;
    count4++;
  }
  if (second == '1') {
    if (third == '0') {
      if ((isRotate == '0') && count4 ==14) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count4 == 20) {
        digitalWrite(13, LOW);
      }
    }
  }

  Serial.println (encoder0Pos4, DEC);
  // use for debugging - remember to comment out
}

void do_EncoderA() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos4 = encoder0Pos4 + 1;         // CW
    }
    else {
      encoder0Pos4 = encoder0Pos4 - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos4 = encoder0Pos4 + 1;          // CW
    }
    else {
      encoder0Pos4 = encoder0Pos4 - 1;          // CCW
    }
  }
}

void do_EncoderB2() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA2) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB2) == LOW) {
      encoder0Pos5 = encoder0Pos5 +1;         // CW
    }
    else {
      encoder0Pos5 = encoder0Pos5 - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB2) == HIGH) {
      encoder0Pos5 = encoder0Pos5 + 1;          // CW
    }
    else {
      encoder0Pos5 = encoder0Pos5 - 1;          // CCW
    }
  }
  if (encoder0Pos5 >= 100) {
    //digitalWrite(13, LOW);
    encoder0Pos5 = 0;
    count5++;
  }
  if (second == '1') {
    if (third == '0') {
      if ((isRotate == '0') && count5 == 14) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count5 == 20) {
        digitalWrite(13, LOW);
      }
    }
  }
  Serial.println (encoder0Pos5, DEC);
  // use for debugging - remember to comment out
}

void do_EncoderA2() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB2) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA2) == HIGH) {
      encoder0Pos5 = encoder0Pos5 +1;         // CW
    }
    else {
      encoder0Pos5 = encoder0Pos5 - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA2) == LOW) {
      encoder0Pos5 = encoder0Pos5 + 1;          // CW
    }
    else {
      encoder0Pos5 = encoder0Pos5 - 1;          // CCW
    }
  }
}
void do_EncoderB3() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA3) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB3) == LOW) {
      encoder0Pos6 = encoder0Pos6 + 1;         // CW
    }
    else {
      encoder0Pos6 = encoder0Pos6 - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB3) == HIGH) {
      encoder0Pos6 = encoder0Pos6 + 1;          // CW
    }
    else {
      encoder0Pos6 = encoder0Pos6 - 1;          // CCW
    }
  }
  //Serial.println (encoder0Pos3, DEC);
  if (encoder0Pos6 >= 100) {
    //digitalWrite(13, LOW);
    encoder0Pos6 = 0;
    count6++;
  }

  if (second == '1') {
    if (third == '0') {
      if ((isRotate == '0') && count6 == 14) {
        digitalWrite(13, LOW);
      }
    }
    if (third == '1') {
      if ((isRotate == '0') && count6 == 20) {
        digitalWrite(13, LOW);
      }
    }
  }

  //use for debugging - remember to comment out
}

void do_EncoderA3() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB3) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA3) == HIGH) {
      encoder0Pos6 = encoder0Pos6 + 1;         // CW
    }
    else {
      encoder0Pos6 = encoder0Pos6 - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA3) == LOW) {
      encoder0Pos6 = encoder0Pos6 + 1;          // CW
    }
    else {
      encoder0Pos6 = encoder0Pos6 - 1;          // CCW
    }
  }
}*/


int incomingByte = 0;
#include <SoftwareSerial.h>

#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 2
#define pino_echo 4

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);


int enA = 10;//right motor (robot's right)
int in1 = 9;
int in2 = 8;

int enB = 5;//left motor (robot's left)
int in3 = 7;
int in4 = 6;


int redpin  = A3; //vermelho//define RGB LED pins
int greenpin= A2; // verde
int bluepin = A1; //azul

int speed = 150; //change speed here, can range from 0 to 255.


void setup()
{

  Serial.begin(9600); //Use serial monitor at 9600 for debugging and controlling from computer
  Serial.println("Motor test!");
  Serial.println("Lendo dados do sensor...");

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}


void left()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, speed);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, speed);
}

void right()
{

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, speed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, speed);
}

void forward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, speed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, speed);
}

void backward()
{

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 100);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, 100);
}

void stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void RGB (int R, int G, int B) {

  analogWrite(redpin, R);
  analogWrite(greenpin, G);
  analogWrite(bluepin, B);
}

void loop()
{


  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);


  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  }



  switch (incomingByte)
  {
    case 'S':
        
      { 
        RGB(255, 0, 255); //vermelho
        stop();
        Serial.println("Stop\n");
        incomingByte = '*';
      }

      break;

    case 'F':

      {
        RGB(0, 0, 255); //roxo
        
        Serial.println("Forward\n");
        incomingByte = '*';
        
        Serial.print("Distancia em cm: ");
        Serial.print(cmMsec);

        if (cmMsec >= 15.0) {
          forward();
        }



      }
      break;

    case 'B':

      { 
        backward();
        RGB(255, 0, 0); //roxo
        Serial.println("Backward\n");
        incomingByte = '*';
      }
      break;

    case 'R':

      {
        RGB(0, 255, 0); //verde
        right();
        Serial.println("Rotate Right\n");
        incomingByte = '*';
      }
      break;


    case 'L':

      {
        left();
        RGB(0, 255, 0); //verde
        Serial.println("Rotate Left\n");
        incomingByte = '*';
      }
      break;

    case 'W':

      {
        RGB(255, 0, 0); //red
        Serial.println("Red Eyes");
        incomingByte = '*';
      }
      break;

    case 'V':

      {
        RGB(0, 255, 0); //green
        Serial.println("Green Eyes");
        incomingByte = '*';
      }
      break;
  }

}


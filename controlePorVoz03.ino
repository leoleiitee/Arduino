#include <SoftwareSerial.h>

#include <TimerOne.h>

#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 2
#define pino_echo 4

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

String command;
int incomingByte = 0;


int enA = 10;//robot's right motor
int in1 = 9;
int in2 = 8;

int enB = 5;//robot's left motor
int in3 = 7;
int in4 = 6;

int red = A1; //vermelho//define RGB LED pins
int green= A2; // verde
int blue = A3; //azul

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Timer1.initialize(250000);
  Timer1.attachInterrupt(INT_Timer1);
}

void INT_Timer1() {
  if(rangeSensor() <= 15.0) {
    stop();
  }
}

void loop() {
  //verde amarelo? RGB(0,0,255);
 // ?RGB(0,255,0);
 //branco  RGB(255,0,0);
  //branco RGB(0, 0, 0);
 //azul RGB(255, 255, 0);
  //verde RGB(255, 0, 255);
  // red RGB(0, 255, 255);

  bluetooth();
  
   if (command.length() > 0) {
    Serial.println(command);
    if (command == "avançar") {
      forward();
    }  else if (command == "recuar") {
      backward();
    } else if (command == "direita") {
      right();
    }else if(command == "esquerda") {
      left();
    }else if (command == "parar") {
      stop();
    }
    command = "";
  }

}

void bluetooth() {
  
  while (Serial.available()) {
    delay(10);
    char instruction = Serial.read();
    if (instruction == '#') {
      break;
    }
    command = command + instruction;
  }
}
float rangeSensor() {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  
  return cmMsec;
}


void stop() {
  RGB(0, 255, 255); //vermelho
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void forward() {
    if(rangeSensor() >= 15.0) {
    RGB(255, 255, 0); //azul
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    analogWrite(enA, 255);//change speeds here 0-255

    digitalWrite(in3, HIGH);  
    digitalWrite(in4, LOW);

    analogWrite(enB, 255);//change speeds here 0-255
  }
  delay(10);
}


void backward() {
  RGB(255, 0, 255); //verde
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 255);//change speeds here 0-255

  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);

  analogWrite(enB, 255); //change speeds here 0-255

  delay(3000);
  stop();
}

void left() {
  RGB(0, 0, 0); //branco
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enA, 230);//change speeds here 0-255

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enB, 230);//change speeds here 0-255

  delay(350);
  stop();
}

void right() {
  RGB(0, 0, 0); //branco
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 230);//change speeds here 0-255

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, 230);//change speeds here 0-255

  delay(350);
  stop();
}

void RGB(int R, int G, int B) {
  analogWrite(red, R);
  analogWrite(green, G);
  analogWrite(blue, B);
}

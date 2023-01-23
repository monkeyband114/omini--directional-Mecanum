#define BLYNK_TEMPLATE_ID "TMPL7FT3_tTt"
#define BLYNK_DEVICE_NAME "mecanum2 "
#define BLYNK_AUTH_TOKEN "mo5YmTlDV_xfKziFhtKrOY1PFhxsDglO"

// #define BLYNK_PRINT Serial

#include <AFMotor.h>
// #define BLYNK_PRINT Serial
#include <ESP8266_Lib.h> // insert this library 
#include <BlynkSimpleShieldEsp8266.h>
#include <Servo.h>
#include <EEPROM.h>


int lion1 = 22;
int lion2 = 24;
int lion3 = 26;
int lion4 = 28;
int addr[128];
char position[] = {};
int j = 0;



int stop, left, right, sidwayslf, 
sidwaysrt, armup, armdown, clawopen, 
clawclose, front, back, Speed, store, rotate, replay;


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MichaelsA32";
char pass[] = "288dtyzx5";
#define EspSerial Serial3
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
BlynkTimer timer;
uint8_t i;
AF_DCMotor motor(1);

AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);

  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

   Blynk.begin(auth, wifi, ssid, pass);                          //Reguler server
  // Blynk.begin(auth, wifi, ssid, pass, "192,168,1,100", 8080);   //Local server

  motor.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  servo1.attach(lion1);
  servo2.attach(lion2);
  servo3.attach(lion3);
  servo4.attach(lion4);
    servo1.write(0);         //close cap on power on
    delay(100);
    servo2.write(0);         //close cap on power on
    delay(100);
    servo3.write(0);         //close cap on power on
    delay(100);
    servo4.write(0);         //close cap on power on
    delay(100);
    
}


// Get the joystick values
BLYNK_WRITE(V17) {
  front = param.asInt();
}
BLYNK_WRITE(V18) {
  back = param.asInt();
}
BLYNK_WRITE(V19) {
  sidwaysrt = param.asInt();
}
BLYNK_WRITE(V20) {
  sidwayslf = param.asInt();
}
BLYNK_WRITE(V5) {
  rotate = param.asInt();
}
BLYNK_WRITE(V6) {
  armup = param.asInt();
}
BLYNK_WRITE(V16) {
  armdown = param.asInt();
}
BLYNK_WRITE(V15) {
  clawopen = param.asInt();
}
BLYNK_WRITE(V21) {
  store = param.asInt();
}
BLYNK_WRITE(V14) {
  replay = param.asInt();
}
BLYNK_WRITE(V13) {
  stop = param.asInt();
}
BLYNK_WRITE(V22) {
  right = param.asInt();
}
BLYNK_WRITE(V23) {
  clawclose = param.asInt();
}
//Get the slider values


// 

void rePlay () {
   Forward_mov();
   delay(1000);
   sidwaysLT_mov();
   delay(1000);
   Forward_mov();
   delay(1500);
   sidwaysRT_mov();
   delay(1000);
   rotatelt();
   delay(1000);
   armUp();
   delay(1000);
   sidwaysLT_mov();
   delay(1000);
   backward_mov();
   delay(1000);
   sidwaysRT_mov();
   delay(1000);
   backward_mov();
   delay(1000);
   armDown();
   delay(1000);
}



void smartcar() {
  if (replay == 11) {
    rePlay();
  }
  if (front == 3) {
    Forward_mov();
    Serial.println("carForward");
  } else if (back == 4) {
    backward_mov();
    Serial.println("carBackward");
  } else if ( sidwayslf == 6) {
    sidwaysLT_mov();
    Serial.println("carLeft");
  } else if (sidwaysrt == 5) {
    sidwaysRT_mov();
    Serial.println("carRight");

  } else if (armup == 8) {
    armUp();
    Serial.println("ArmPush");
  } else if (armdown == 9) {
    armDown();
    Serial.println("ArmPull");
  } else if (clawopen == 10) {
    openClaw();
    Serial.println("ArmClaw");
  } else if (clawclose == 16) {
     closeClaw();
     Serial.println("Clawclose");
  } else if (rotate == 7) {
     rotateArm();
    Serial.println("RotateBase");
  } else if (store == 13) {
    
  } else if (right == 15) {
     rotatelt();
  } else if (replay == 11) {
     rePlay();
  } else if (right == LOW && front == LOW && back == HIGH && sidwayslf == HIGH) {
    carStop();
    Serial.println("carstop");

  }
}


void loop() {
  Blynk.run();
  smartcar();
  if ( Serial3.available() )   {
    Serial.write( Serial3.read() );
  }
  if ( Serial.available() )       {
    Serial3.write( Serial.read() );
  }

}


void Forward_mov () {

  // Turn on motor
  motor.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  // Accelerate from zero to maximum speed
  motor.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
  // Decelerate from maximum spee1d to zero
  for (i = 255; i != 0; i--)
  {
    motor.setSpeed(i);
    motor2.setSpeed(i);
    motor3.setSpeed(i);
    motor4.setSpeed(i);
    delay(10);
  }
  // Now turn off motor
  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}


void backward_mov () {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  // Accelerate from zero to maximum speed

  motor.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);

  // Decelerate from maximum speed to zero
  for (i = 255; i != 0; i--)
  {
    motor.setSpeed(i);
    motor2.setSpeed(i);
    motor3.setSpeed(i);
    motor4.setSpeed(i);
    delay(10);
  }
  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void diagonal_mov () {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  motor2.setSpeed(255);
  motor.setSpeed(255);
  delay(2000);

  motor.run(RELEASE);
  motor2.run(RELEASE);
  delay(500);
}


void sidwaysRT_mov () {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
  delay(250);

  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(500);
}

void sidwaysLT_mov () {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  motor.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
  delay(250);

  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(500);
}
void robotarm1 (){
   servo1.write(150);    
   delay(1000);    
  }
void robotarm2 (){    
   servo2.write(90);    
   delay(1000);    
  }
void robotarm3 (){       
   servo3.write(90);    
   delay(1000);
       
  }
  void robotarm4 (){  
   servo4.write(90);    
   delay(1000);   
  }

void deattach (){
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();
}

void armUp () {
  robotarm3();
  robotarm2();
}


void armDown() {
  servo2.attach(lion2);
  delay(1);
  servo2.write(0);
  delay(1000);
}

void rotateArm () {
  robotarm4();
}
void openClaw () {
  robotarm1();
}

void closeClaw () {
  delay(1);
  servo1.write(-75);
}


void rotatelt() {
  servo4.write(-45);    
   delay(1000);
}

void carStop() {
  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(500);
}



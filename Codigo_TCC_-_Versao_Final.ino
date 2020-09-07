#include <SPI.h>
#include <MFRC522.h>   // Identificação de Radiofrequência
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();   // Inicia a biblioteca

#define SS_PIN 10
#define RST_PIN 9
#define SERVOMIN  100   // Minimum pulse length count out of 4096
#define SERVOMAX  400   // Maximum pulse length count out of 4096

int servoNo = 16;   // Define um contador para os servos

void moveServo(int servo_port, int angle)
{
  int desired_angle = map(angle, 0, 180, 100, 2200);
  pwm.setPWM(servo_port, 0, desired_angle);
}

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria a instância MFRC522

void setup()
{
  Serial.begin(9600);   // Inicia a conexão serial com taxa de 9600 bauds
  
  SPI.begin();          // Inicia o SPI
  mfrc522.PCD_Init();   // Inicia o MFRC522
    
  pwm.begin();          // Envia sinais PWM
  pwm.setPWMFreq(60);   // Faz com que os servos funcionem na taxa de 60 Hz
  
  Serial.println("Coloque o seu cartão sobre o leitor...");
  Serial.println();
  
  delay(20);
}

void loop() 
{
// Procure por novos cartões
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return; 
  }
  
// Selecione um dos cartões
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  
// Mostra o UID no monitor serial
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem: ");
  content.toUpperCase();

//__________DOG__________  
  if (content.substring(1) == "69 B2 D5 2A")   // Altere aqui o UID do(s) cartão(ões) que você deseja dar acesso
  {
    Serial.println("Acesso Autorizado");
    Serial.println();
    delay(500);

// 1ª Cela Braille    
   moveServo(0, 11); 
    delay(1000);
   moveServo(2, 9);
    delay(1000);       
   moveServo(1, 13);
    delay(1000);

// 2ª Cela Braille
   moveServo(6, 13);
    delay(1000);
   moveServo(9, 34);
    delay(1000);
   moveServo(10, 8);
    delay(1000);    

// 3ª Cela Braille
   moveServo(12, 10);
    delay(1000);
   moveServo(13, 21);
    delay(1000);
   moveServo(5, 17);
    delay(1000);     
   moveServo(14, 21);
    delay(1000);

//******************************
delay(10000);
// 1ª Cela Braille - Retorno    
   moveServo(0, 6);
    delay(1000);
   moveServo(2, 13);
    delay(1000);
   moveServo(1, 5);
    delay(1000);

// 2ª Cela Braille - Retorno
   moveServo(6, 9);
    delay(1000);
   moveServo(9, 28);
    delay(1000);
   moveServo(10, 13);
    delay(1000);

// 3ª Cela Braille - Retorno
   moveServo(12, 4);
    delay(1000);
   moveServo(13, 18);  
    delay(1000);
   moveServo(5, 10);
    delay(1000);
   moveServo(14, 13);
    delay(1000);
  }

//__________OWL__________  
if (content.substring(1) == "D6 F4 20 F8")   
  {
    Serial.println("Acesso Autorizado");
    Serial.println();
    delay(500);

// 1ª Cela Braille    
   moveServo(0, 11); 
    delay(1000);
   moveServo(1, 13);
    delay(1000);
   moveServo(3, 7);
    delay(1000);
     
// 2ª Cela Braille
   moveServo(7, 3);  
    delay(1000);
   moveServo(8, 4); 
    delay(1000);
   moveServo(9, 34);
    delay(1000);
   moveServo(11, 7);
    delay(1000);
    
// 3ª Cela Braille
   moveServo(12, 10);
    delay(1000);
   moveServo(5, 17);
    delay(1000);   
   moveServo(15, 18);
    delay(1000);       

//******************************
delay(10000);
// 1ª Cela Braille - Retorno
   moveServo(0, 6);
    delay(1000);
   moveServo(1, 5);
    delay(1000);
   moveServo(3, 13);
     delay(1000);
     
// 2ª Cela Braille - Retorno
   moveServo(7, 7);  
    delay(1000);
   moveServo(8, 8);
    delay(1000);
   moveServo(9, 28);
    delay(1000);
   moveServo(11, 11);
    delay(1000); 

// 3ª Cela Braille - Retorno
   moveServo(12, 4);
    delay(1000);
   moveServo(5, 10);
    delay(1000);
   moveServo(15, 25); 
    delay(1000);
}

else
{
  Serial.println("Acesso Recusado!");
   Serial.println();
   delay(1000);
  Serial.println("Informe uma das Tag's cadastradas: ");
   Serial.println();
   delay(1000);
}
}

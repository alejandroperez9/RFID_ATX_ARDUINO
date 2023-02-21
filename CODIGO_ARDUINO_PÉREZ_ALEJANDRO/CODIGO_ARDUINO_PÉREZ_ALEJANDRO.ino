/*
ACTIVAR UNA FUENTE DE ALIMENTACIÓN MEDIANTE UN SENSOR RFID Y EN CASO DE NO FUNCIONAR
SE ACTIVARÁ EL PROCESO DE CONTRASEÑA MEDIANTE POTENCIOMETRO, IGUALANDOLO A UN VALOR.

RELAIZAD POR: ALEJANDRO PÉREZ ARANDA.
*/

#include <Wire.h>                 
#include <SPI.h>               
#include <MFRC522.h>   
#include <LiquidCrystal_I2C.h>         

#define rele 8     
#define RST  9              
#define SS   10     

MFRC522 mfrc522(SS, RST); 

byte LecturaUID[4];                             
byte Usuario1[4] = { 0x73, 0x3B, 0xD4, 0x0B} ;  
byte Usuario2[4] = {0x05, 0X76, 0XF5, 0XBE } ; 

const int analogPin = A0;
int valor;
int posicion;

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {

  Serial.begin(9600);                   
  SPI.begin();                          
  mfrc522.PCD_Init();                  
  pinMode(rele, OUTPUT);              

  pinMode(5, OUTPUT);
  digitalWrite(rele, LOW);  

  pinMode(A0, INPUT);

  lcd.init();
  lcd.backlight();

  pantalla_inicio();

}


boolean comparaUID(byte lectura[], byte usuario[]){

  for (byte i = 0; i < mfrc522.uid.size; i++){  

    if (lectura[i] != usuario[i]){
      return (false);
    }  

  }

  return (true);  

}


void loop(){

  if ( ! mfrc522.PICC_IsNewCardPresent()){  
    return;
  }                                

  if ( ! mfrc522.PICC_ReadCardSerial()){     
    return;             
  }                   

  for (byte i = 0; i < mfrc522.uid.size; i++){    

      LecturaUID[i] = mfrc522.uid.uidByte[i];    

  }


  if (comparaUID(LecturaUID, Usuario1)){  

    digitalWrite(rele, !digitalRead(rele)); 
    pantalla_autoriazado();


  }else if (comparaUID(LecturaUID, Usuario2)){

    digitalWrite(rele, !digitalRead(rele));
    pantalla_autoriazado();   

  }else {

    pantalla_denegado();
    manual();

  }

  mfrc522.PICC_HaltA(); 

}


void manual(){

  valor = analogRead(A0);
  valor = map( valor, 0, 1023, 0, 100);

  Serial.println(valor);  

  lcd.setCursor(0, 1);
  lcd.print(valor);

  if (valor == 13){

    digitalWrite(rele, !digitalRead(rele));
    pantalla_autoriazado();
    return(false);
  }

  return(manual());

}


void pantalla_inicio(){

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Identifiquese: ");
  delay(1000);

}

void pantalla_autoriazado(){

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("ACCESO");
  lcd.setCursor(3, 1);
  lcd.print("AUTORIZADO");
  delay(2000);
  lcd.clear();
  lcd.print("Identifiquese: ");

}


void pantalla_denegado(){

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("ACCESO");
  lcd.setCursor(4, 1);
  lcd.print("DENEGADO");
  delay(1000);

  digitalWrite(5, HIGH);
  delay(5000);
  digitalWrite(5, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clave: ");

}

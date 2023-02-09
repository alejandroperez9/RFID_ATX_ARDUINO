#include <Keypad.h>
 
const byte filas = 4;
const byte columnas = 4;
 
char keys[filas][columnas] = {
  
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }

};
 
const byte rowPins[filas] = { 8, 7, 6, 5 };
const byte columnPins[columnas] = { 4, 3, 2, 1 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, filas, columnas);
 
void setup() {

   Serial.begin(9600);

}
 

void loop() {

   char key = keypad.getKey();
 
   if (key) {
      Serial.println(key);
   }
}
#include <Keypad.h>   


const byte filas = 4;    
const byte columnas = 4;    

char keys[filas][columnas] ={    

  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  
};


byte pinesFilas[filas] = {8, 7, 6, 5};   
byte pinesColumnas[columnas] = {4, 3, 2, 1}; 


Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, filas, columnas); 


char tecla;       
char clave[7];        
char clave_maestra[7] = "123456";  //CONTRASEÑA.

byte indice = 0;

  
void setup(){
  
 Serial.begin(9600);

}


void loop(){
  
  tecla = teclado.getKey(); 
  
  if (tecla){       
    clave[indice] = tecla; 
    indice++;
    Serial.print(tecla);
  }

  if(indice == 6){

    if(!strcmp(clave, clave_maestra))
      Serial.println(" Correcta"); 
    else
      Serial.println(" Incorrecta");

    indice = 0;

  }
}
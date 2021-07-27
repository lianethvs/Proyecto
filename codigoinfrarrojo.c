#include <IRremote.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>


/*
# define  _DEBUG_
# define  DISABLE_TLS
# include  <ESP8266WiFi.h>
# include  <ThingerESP8266.h>

# define  USUARIO  "  "
# define  ID  "  "
# define  CREDENCIAL  "  "

# define   NOMBRE_DE_WIFI  " nombre_wifi "
# define  CONTRASEÑA  " contraseña wifi "

*/

int entrada_infraroja= 4;
int n = 10;
int receptor = 13;
IRrecv irrecv(receptor);
decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
 
void setup()
{
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // INICIA LA RECEPCIÓN
  pinMode(entrada_infraroja, INPUT);
  lcd.begin(16, 2);
  // MOVER EL CURSOR A LA PRIMERA POSICION DE LA PANTALLA (0, 0)
  lcd.home();
}
 
void loop()
{
 int value_entrada = digitalRead(entrada_infraroja);
 while (irrecv.decode(&codigo))
 {
      Serial.println(codigo.value, HEX);

      if (codigo.value==0xFF30CF)//CÓDIGO DEL NÚMERO UNO PARA El MODO UNO GUARDAR LA INFORMACIÓN 
      {
         if(value_entrada==0){
            comunicacion();
            lcd.print("Abierto");
            delay(10000);
         }
         else{
            lcd.print("Cerrado");
            delay(1000);
         }
      }

      if (codigo.value==0xFF30CF)//CÓDIGO DEL NÚMERO 2 PARA ENVIAR UN CORREO SOBRE LA INFORMACIÓN
      {
        if(value_entrada==0){
          comunicacion();
          lcd.print("Abierto");
          //sendemail();
          delay(1000);
        }

        else{
          lcd.print("Cerrado");
          delay(1000);
        }
      }

      if (codigo.value==0xFF30CF)//CÓDIGO DEL NÚMERO 2 PARA ENVIAR UN CORREO SOBRE LA INFORMACIÓN
      {
         if(value_entrada==0){
          comunicacion();
          //sendemail();
          cuenta_regresiva();
          delay(1000);
         }
         else{
          lcd.print("Cerrado");
          delay(1000);
         }
      }
    
    
delay(500);
irrecv.resume();

 }
}

/*
void sendemail(){
  thing.handle ();
      //El siguiente comando se utiliza para indicar el msj que recibirá el usuario.
  thing.call_endpoint ( " El presente correo le notifica que la puerta de su hogar ha sido abierta, tome las acciones necesarias. " );
      //Se indica el valor de retraso, no es mucho tiempo que tarda en enviar el correo.
      //Se le pone delay para que el arduino tenga tiempo de procesar los datos.
  delay ( 5000 );
}
*/
void comunicacion(){
Serial.println("Se abrío la puerta a las:" );
time_t t = now();

Serial.print(day(t));
Serial.print(+ "/") ;
Serial.print(month(t));
Serial.print(+ "/") ;
Serial.print(year(t)); 
Serial.print( " ") ;
Serial.print(hour(t));  
Serial.print(+ ":") ;
Serial.print(minute(t));
Serial.print(":") ;
Serial.println(second(t));;

delay(10000);
}

void cuenta_regresiva(){
  lcd.begin(16, 2);
  // MOVER EL CURSOR A LA PRIMERA POSICION DE LA PANTALLA (0, 0)
  lcd.home();
  while(n=!0){
    lcd.setCursor(0,1); // Se mueve el cursor a la segunda fila
    lcd.print(n);
    Serial.println(n);
    n--;
  }
}



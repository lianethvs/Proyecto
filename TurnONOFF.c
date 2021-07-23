#include <IRremote.h>
#include <LiquidCrystal.h>

#define PIN_RECEIVER 2   // Signal Pin of IR receiver
#define code1  162   // code received from button 1
#define code2  <>   // code received from button 2
#define code3     // code received from "power button"

IRrecv receiver(PIN_RECEIVER);
decode_results results;

int app1 = 3; //PIN where the infrared is connected
//We can add more <int app# = PIN> if we required additional code to be added based on the configuration
int status[] = {0,0,0,0};

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2); //Start the LCD
  lcd.print("<press a button>");
  receiver.enableIRIn(); // Start the receiver

  pinMode(app1, OUTPUT);

}

void loop()
{
  // Checks received an IR signal
  if (receiver.decode()) {
    unsigned int value = results.value;
    switch(value) {
     
       case code1:
         if(status[1] == 1) {           // if first app is ON then
            digitalWrite(app1, LOW);      // turn it off when button is pressed
            status[1] = 0;              // and set its state as off
            lcd.setCursor(10,0);      //printing status on LCD
            lcd.print("OFF");
          }
    }
  }
}
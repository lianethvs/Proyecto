int entrada_infraroja= 2;
int led= 13;
void setup() {
pinMode(entrada_infraroja, INPUT);
pinMode(led, OUTPUT);
}

void loop() {
int counter;

int value_entrada = digitalRead(entrada_infraroja);
if(value_entrada==1){
  digitalWrite(led,1);
}
else{
  digitalWrite(led,0);
}
}





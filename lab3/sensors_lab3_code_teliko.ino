int LedOut = 13; 
int light_pin = A0; 
int temp_pin = A1; 
int move_pin = 8;
float brightness=-227.00;
const float night=0;
float analog_value;
unsigned long previous1=0;
unsigned long previous2=0;
float step=10;



void temperature_level(){ 
   int temp_value = analogRead(temp_pin);    
   float temp = temp_value*5000.0/1024.0;
   float temp_C = (temp-500)/10.0; //turn to celcius
   Serial.print("Temp = "); 
   Serial.print(temp_C);
   Serial.println("C");
}

void movement() {
  bool movement = digitalRead(move_pin);
  //Serial.println(movement);
  if(movement == HIGH){
      Serial.println("Movement detected");
  }
}

 
void setup() {
  pinMode(move_pin, INPUT);
  pinMode(LedOut, OUTPUT);
  Serial.begin(9600); 
}

void loop(){
  if(millis() >= previous1){
    float value=analogRead(light_pin);
    analog_value=map(value,512,1023,0,255); //-228 ws 230
    Serial.print("Brightness value is = ");
    Serial.println(analog_value);
    previous1 = millis() + 1000; //kathe 10 sec metrisi
  }
  if(analog_value<night){ //when we have insufficient light i.e when analog_value <-150
      analogWrite(LedOut,brightness); //move previous brightness value to led 
      if(brightness<=-228.0){ //add delay when we reach minimum led value
        delay(2000);
      }
      if(brightness>=230.0){ //delay for max led value
        delay(3000);
      }
      brightness = brightness + step; 
      Serial.println(brightness);
      if (brightness <= -228.0 || brightness >= 230.0){ //change mode from increasing brightness to decreasing(and vice versa)
        step = -step;
 }
  }

      
  if(millis() >= previous2){
       temperature_level(); 
       previous2 = millis()+2000; //kathe 20 sec metrisi
} 
  movement();
}
 

     
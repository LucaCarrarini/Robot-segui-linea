#include "sensori_attuatori.h"
void check_battery();

void setup() {
  inizializza_pin();
  Serial.begin(9600);
  inizializza_motori();
  check_battery();
  check_button();
  delay(1000);
}

void loop() {
  
}

void check_battery(){
  int val = read_battery_level();
  switch(val){
    case 0:{
      accendi_led_r();
      spegni_led_v();
    }
    case 1:{
      accendi_led_r();
      accendi_led_v();
    }
    case 2:{
      accendi_led_v();
      spegni_led_r();
    }
  }
}
  

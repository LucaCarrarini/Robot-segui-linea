#include <Arduino.h>
#include "sensors_actuators_library.h"

void check_battery();
void block();
void forward();
void turn_left();
void turn_right();
void check_distance();
void check_button();

void block(){
  digitalWrite(13, HIGH);
  stop_l();
  stop_r(); 
}

void forward(){
  forward_r();
  forward_l();
}

void turn_left(){
  forward_r();
  reverse_l();
}

void turn_right(){
  forward_l();
  reverse_r();
}

void check_battery(){
  int val = read_battery_level();
  switch(val){
    case 0:{
      turnOn_led_r();
      turnOff_led_g();
      while(1) block();
    }
    case 1:{
      turnOn_led_r();
      turnOn_led_g();
    }
    case 2:{
      turnOn_led_g();
      turnOff_led_r();
    }
  }
}

void check_distance(){
  while(read_distance()){
    block();
  }
  digitalWrite(13,LOW);
}

void check_button(){
  while(1){
    if(!read_button()){
      delay(100);                //Antirimbalzo
      if(read_button())
        break;
    }
  }
}

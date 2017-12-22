#include "actions.h"

void setup(){
  init_pin();
  init_motor();
  check_battery();
  check_button();
  delay(1000);
}

void loop() {
  check_battery();
  check_distance();
  if(is_r_black())
    if(is_l_black())
      //entrambi i sensori leggono scuro
      block();
    else turn_right();
  else if(is_l_black())
          turn_left();
       else forward();
}

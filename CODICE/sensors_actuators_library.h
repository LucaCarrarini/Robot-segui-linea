#include <Arduino.h>

//Pin analogici
#define light_r A1  //pin lettura sensore di luminosità destro
#define light_l A0  //pin lettura sensore di luminosità sinistro
#define battery A2  //pin monitoraggio livello carica della batteria

//Pin digitali
#define mot1_r 5   //pin pilotaggio motore destro
#define mot2_r 6  //
#define mot1_l 3   //pin pilotaggio motore sinistro
#define mot2_l 11  //
#define echo 8      //pin echo sensore distanza
#define trig 7      //pin trig sensore distanza
#define led_r 4     //pin led rosso (red) per livello batteria
#define led_g 9     //pin led verde (green)
#define button 12    //il bottone va collegato a massa
#define speed_value 180 //segnale PWM che regola la velocità dei motori
#define light_threshold 650 //soglia per distinguere chiaro e scuro. Valore trovato tramite test

boolean read_button();
boolean is_r_black();
boolean is_l_black();
int read_battery_level();
boolean read_distance();
void forward_r();
void forward_l();
void reverse_r();
void reverse_l();
void stop_l();
void stop_r();
void turnOn_led_r();
void turnOn_led_g();
void turnOff_led_r();
void turnOff_led_g();
void init_motor();
void init_pin();

boolean read_button(){
  return digitalRead(button);
}

//restituisce alto se è buio, basso se è luce
boolean is_r_black(){
  int value = analogRead(light_r);
  if(value>light_threshold) return true;
  else return false;
}

boolean is_l_black(){
  int value = analogRead(light_l);
  if(value>light_threshold) return true;
  else return false;
}
  
int read_battery_level(){
  int value = map(analogRead(battery), 0, 1023, 0, 3);
  return value;
}

boolean read_distance(){
  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  double t = pulseIn(echo, HIGH, 1200);  //CONTROLLA LIMITE 25000
  double s = (0.034 * t)/2 ;
  if((s!=0) && (s<10)) return true ;
  else return false ;
}

//avanti     1 PWM
//indietro   PWM 1 
void forward_r(){
  digitalWrite(mot1_r, HIGH);
  analogWrite(mot2_r, speed_value);
}

void forward_l(){
  digitalWrite(mot1_l, HIGH);
  analogWrite(mot2_l, speed_value);
}

void reverse_r(){
  analogWrite(mot1_r, speed_value);
  digitalWrite(mot2_r, HIGH);
}

void reverse_l(){
  analogWrite(mot1_l, speed_value);
  digitalWrite(mot2_l, HIGH);
}

void stop_l(){
  digitalWrite(mot1_l, LOW);
  digitalWrite(mot2_l, LOW);
}
void stop_r(){
  digitalWrite(mot1_r, LOW);
  digitalWrite(mot2_r, LOW);
}

void turnOn_led_r(){
  digitalWrite(led_r, HIGH);
}
void turnOn_led_g(){
  digitalWrite(led_g, HIGH);
}

void turnOff_led_r(){
  digitalWrite(led_r, LOW);
}

void turnOff_led_g(){
  digitalWrite(led_g, LOW);
}

//inizializzazione motori da fermi -> da mettere nel setup
void init_motor(){
  digitalWrite(mot1_r, HIGH);
  digitalWrite(mot2_r, HIGH);
  digitalWrite(mot1_l, HIGH);
  digitalWrite(mot2_l, HIGH);
}  

void init_pin(){
  pinMode(mot1_r, OUTPUT);
  pinMode(mot2_r, OUTPUT);
  pinMode(mot1_l, OUTPUT);
  pinMode(mot2_l, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(led_r, OUTPUT);
  digitalWrite(led_r, LOW);
  pinMode(led_g, OUTPUT);
  digitalWrite(led_g, LOW);
  pinMode(13, OUTPUT);//led del pin 13 per comunicare se c'è un ostacolo
  digitalWrite(13, LOW);
  pinMode(button, INPUT_PULLUP);
}

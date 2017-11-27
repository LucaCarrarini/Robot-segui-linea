#include <Arduino.h>
#define luce_dx A0  //pin lettura sensore di luminosità destro
#define luce_sx A1  //                                  sinistro
#define battery A2  //pin monitoraggio livello carica della batteria

#define mot1_dx 3   //pin pilotaggio motore destro
#define mot2_dx 11  //
#define mot1_sx 9   //pin pilotaggio motore sinistro
#define mot2_sx 10  //
#define echo 4      //pin echo sensore distanza
#define trig 5      //pin trig sensore distanza
#define led_r 6     //pin led rosso per livello batteria
#define led_v 7     //pin led verde 
#define button 2    //il bottone va collegato a massa

bool read_lum_dx();
bool read_lum_sx();
int read_battery_level();
bool read_distance();
void avanti_dx();
void avanti_sx();
void indietro_dx();
void indietro_sx();
void accendi_led_r();
void accendi_led_v();
void spegni_led_r();
void spegni_led_v();
void inizializza_motori();
void check_button();

//restituisce alto se è buio, basso se è luce
bool read_lum_dx(){
  int value = analogRead(luce_dx);
  if(value>512) return true;
  else return false;
}

bool read_lum_sx(){
  int value = analogRead(luce_sx);
  if(value>512) return true;
  else return false;
}
  
int read_battery_level(){
  int value = map(analogRead(battery), 0, 1023, 0, 3);
  return value;
}

bool read_distance(){
  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  double t = pulseIn(echo, HIGH, 25000);  //CONTROLLA LIMITE 25000
  double s = (0.034 * t)/2 ;
  if(s<10) return true ;
  else return false ;
}

//avanti veloce    PWM 0
//indietro veloce  0 PWM 
void avanti_dx(){
  digitalWrite(mot1_dx, HIGH);
  digitalWrite(mot2_dx, LOW);
}

void avanti_sx(){
  digitalWrite(mot1_sx, HIGH);
  digitalWrite(mot2_sx, LOW);
}

void indietro_dx(){
  digitalWrite(mot1_dx, LOW);
  digitalWrite(mot2_dx, HIGH);
}

void indietro_sx(){
  digitalWrite(mot1_sx, LOW);
  digitalWrite(mot2_sx, HIGH);
}

void accendi_led_r(){
  digitalWrite(led_r, HIGH);
}
void accendi_led_v(){
  digitalWrite(led_v, HIGH);
}

void spegni_led_r(){
  digitalWrite(led_r, LOW);
}

void spegni_led_v(){
  digitalWrite(led_v, LOW);
}

//inizializzazione motori da fermi -> da mettere nel setup
void inizializza_motori(){
  digitalWrite(mot1_dx, HIGH);
  digitalWrite(mot2_dx, HIGH);
  digitalWrite(mot1_sx, HIGH);
  digitalWrite(mot2_sx, HIGH);
}  

//FAI PINMODE
void inizializza_pin(){
  pinMode(mot1_dx, OUTPUT);
  pinMode(mot2_dx, OUTPUT);
  pinMode(mot1_Sx, OUTPUT);
  pinMode(mot1_dx, OUTPUT);
  pinMode();
  pinMode();
  pinMode();
  pinMode();
  pinMode(13, OUTPUT);//led del pin 13 per comunicare se c'è un ostacolo
  pinMode(button, INPUT_PULLUP);
}

void check_button(){
  while(1){
    if(digitalRead(button)){
      delay(10);                //Antirimbalzo
      if(!digitalRead(button))
        break;
    }
  }
}

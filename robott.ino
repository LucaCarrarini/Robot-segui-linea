const int trig_pin = 9;
const int echo_pin = 10;

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delay(10);
  //impulso di durata 10us sul trigger come da datasheet
  digitalWrite(trig_pin, HIGH);
  delay(10);
  digitalWrite(trig_pin, LOW);
    
  //OSS:oltre i 20cm il sensore risulta poco preciso allora pongo come tempo limite 1200 microsecondi, iin modo che più o meno oltre i 20 cm risulti fuori portata e non valori poco precisi
  //echo rimane in HIGH per tutto il tempo di durata del viaggio delle onde
  //v=343 m/s -> v=0,0343 cm/micros
  //s[cm]=0,0343 [cm/micros] * t [micros] * 1/2
  long t = pulseIn(echo_pin, HIGH, 50000);
  long s = (0.0343)*(t)*(0.5);
  Serial.print(s);
  if(t==0){
    Serial.println("Fuori portata");
  }
  else{
    Serial.println("distanza[cm]:");
    Serial.println(s);
  }
}

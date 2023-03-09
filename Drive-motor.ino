int relay = 3;
int relay2 = 4;
int timeMaxMotor = 4000;
int sizeMaxMotor = 40;
int timeMotorPush = 0;

void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  //actionMotor(10); -> ajuster la hauteur de l'antivol pour un vélo ayant un rayon de 10cm
  //resetMotor(); -> Remettre le verrain à 0
}



void loop()
{
  
}

void actionMotor(int bicicleSize){
  int sizeMotorPush = sizeMaxMotor - bicicleSize;
  timeMotorPush = timeMaxMotor/sizeMaxMotor*sizeMotorPush;
  digitalWrite(relay2, HIGH);
  digitalWrite(relay, LOW);
  delay(timeMotorPush);
  digitalWrite(relay2, LOW);
  digitalWrite(relay, LOW);
}

void resetMotor(){
  digitalWrite(relay2, LOW);
  digitalWrite(relay, HIGH);
  delay(timeMotorPush);
  digitalWrite(relay2, LOW);
  digitalWrite(relay, LOW);
}

int relay = 3;
int relay2 = 4;
int timeMaxMotor = 4000;
int sizeMaxMotor = 40;

void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  actionMotor(10);
}



void loop()
{
  
}

void actionMotor(int bicicleSize){
  int sizeMotorPush = sizeMaxMotor - bicicleSize;
  int timeMotorPush = timeMaxMotor/sizeMaxMotor*sizeMotorPush;
  digitalWrite(relay2, HIGH);
  digitalWrite(relay, LOW);
  delay(timeMotorPush);
  digitalWrite(relay2, LOW);
  digitalWrite(relay, LOW);
}

int pressCount_B1;
int prevState_B1;

int pressCount_B2;
int prevState_B2;

void setup()
{
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  
  Serial.begin(9600);
  
  pressCount_B1 = 0;
  pressCount_B2 = 0;
  prevState_B1 = digitalRead(2);
  prevState_B2 = digitalRead(3);
}

void loop()
{
  int currState_B1 = digitalRead(2);
  int currState_B2 = digitalRead(3);
  int potVal = analogRead(A0);
  
  if(currState_B1==1 && prevState_B1==0)
  {
    pressCount_B1+=1;
  }

  if(currState_B2==1 && prevState_B2==0)
  {
    pressCount_B2+=1;
  }
  
  prevState_B1 = currState_B1;
  prevState_B2 = currState_B2;

  if(pressCount_B1>=5 && pressCount_B2>=5)
  {
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
  }
  else
  {
    digitalWrite(8,LOW);
    digitalWrite(7,HIGH);
  }

  Serial.print(currState_B1);
  Serial.println(pressCount_B1);
  Serial.print(currState_B2);
  Serial.println(pressCount_B2);
  Serial.print(potVal);

  delay(50);
}

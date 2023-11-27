int prevState_B1;
int prevState_B2;

int stepCount;
int correctSequence;
int correct_flag;

int potVal;

void setup()
{
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);

  Serial.begin(9600);
  
  stepCount = 0;
  correctSequence = 0;

  prevState_B1 = digitalRead(2);
  prevState_B2 = digitalRead(3);
}

void loop()
{
  int currState_B1 = digitalRead(2);
  int currState_B2 = digitalRead(3);

  if(stepCount==0)
  {
    delay(8000);
    potVal = analogRead(A0);
    
    if(potVal==4095) //step 1
    {
      stepCount++;
      correct_flag = 1;
    }
    else if(potVal<=4090)
    {
      stepCount++;
      correct_flag = 0;
    }
    else if((currState_B1==1 && prevState_B1==0) || (currState_B2==1 && prevState_B2==0))
    {
      stepCount++;
      correct_flag = 0;
    }
  }
  else if(stepCount==1)
  {
    if(currState_B1==1 && prevState_B1==0) //step 2
    {
      stepCount++;
      if(correct_flag==1) //checking whether sequence is correct till now
      {
        correct_flag = 1;
      }
    }
    else if(currState_B2==1 && prevState_B2==0)
    {
      stepCount++;
      correct_flag = 0;
    }
  }
  else if(stepCount==2)
  {
    if(currState_B2==1 && prevState_B2==0) //step 3
    {
      stepCount++;
      if(correct_flag==1) //checking whether sequence is correct till now
      {
        correct_flag = 1;
      }
    }
    else if(currState_B1==1 && prevState_B1==0)
    {
      //increase step but reset the sequence
      stepCount++;
      correct_flag = 0;
    }
  }
  else if(stepCount==3)
  {
    if((currState_B2==1 && prevState_B2==0)) //step 4
    {
      stepCount++;
      if(correct_flag==1) //checking whether sequence is correct till now
      {
        correct_flag = 1;
      }
    }
    else if(currState_B1==1 && prevState_B1==0)
    {
      //increase step but reset the sequence
      stepCount++;
      correct_flag = 0;
    }
  }
  else if(stepCount==4)
  {
    if((currState_B1==1 && prevState_B1==0)) //step 5
    {
      stepCount++;
      if(correct_flag==1) //checking whether sequence is correct till now
      {
        correct_flag = 1;
      }
    }
    else if(currState_B2==1 && prevState_B2==0)
    {
      //increase step but reset the sequence
      stepCount++;
      correct_flag = 0;
    }
  }

  prevState_B1 = currState_B1;
  prevState_B2 = currState_B2;

  //lighting up LED based on sequence status
  if(stepCount==5)
  {
    if(correct_flag==1)
    {
      digitalWrite(7,LOW); //red LED
      digitalWrite(8,HIGH); //green LED
    }
    else if(correct_flag==0)
    {
      digitalWrite(7,HIGH); //red LED
      digitalWrite(8,LOW); //green LED
    }
  }

  Serial.println(potVal);  
  Serial.println(stepCount);
  Serial.println(correct_flag);

  delay(50);
}

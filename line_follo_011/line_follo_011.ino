#define in1 8
#define in2 9
#define ena 3
#define in2 10
#define in3 11
#define enb 4


int sensor[6]={0, 0, 0, 0, 0,0};

void setup()
{
 pinMode(3,OUTPUT); //PWM Pin 1 left 
 pinMode(5,OUTPUT); //PWM Pin 2 right
 pinMode(8,OUTPUT); //Left Motor Pin 1
 pinMode(9,OUTPUT); //Left Motor Pin 2
 pinMode(10,OUTPUT); //Right Motor Pin 1
 pinMode(11,OUTPUT);  //Right Motor Pin 2
 Serial.begin(9600); //Enable Serial Communications

  pinMode(A0, INPUT);  //Initializing pin as input from sensor
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop()
{
  sensor[0]=digitalRead(A0);
  sensor[1]=digitalRead(A1);
  sensor[2]=digitalRead(A2);
  sensor[3]=digitalRead(A3);
  sensor[4]=digitalRead(A4);
  sensor[5]=digitalRead(A5);


  if(((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0))&&((sensor[4]==1)||(sensor[5]==1))){
  //error=4;
  left();
  Serial.println("left");
  }
  else if(((sensor[4]==0)&&(sensor[5]==0)&&(sensor[0]==0)&&(sensor[1]==0))&&((sensor[2]==1)||(sensor[3]==1))){
  //error=3;
  forward();
  Serial.println("forward");
  }
  else if(((sensor[4]==0)&&(sensor[5]==0)&&(sensor[2]==0)&&(sensor[3]==0))&&((sensor[0]==1)||(sensor[1]==1))){
  //error=2;
  right();
  Serial.println("right");
  }
    else if(((sensor[2]==0)&&(sensor[5]==0)&&(sensor[1]==0)&&(sensor[0]==0))&&((sensor[3]==1)||(sensor[4]==1))){
  //error=2;
  //left_correct();
  forward();
  Serial.println(" correction left");
  }
    else if(((sensor[0]==0)&&(sensor[5]==0)&&(sensor[4]==0)&&(sensor[3]==0))&&((sensor[1]==1)||(sensor[2]==1))){
  //error=2;
  //right_correct();
  forward();
  Serial.println(" correction right");
  }
   else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
    stopp();
   }
  
  else{
    Serial.println("else condition");
    stopp();
  }

    Serial.print(sensor[0]); // print sensor values on arduino serial monitor  
  Serial.print("    ");
  Serial.print(sensor[1]);
  Serial.print("    ");
  Serial.print(sensor[2]);
  Serial.print("    ");
  Serial.print(sensor[3]);
  Serial.print("    ");
  Serial.print(sensor[4]);
  Serial.print("    ");
  Serial.print(sensor[5]);
  Serial.println("    ");
}

void forward()
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  analogWrite(3,100);

  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  analogWrite(5,100);
}

void right()
{
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,100);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
}

void left()
{
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,0);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,100);
}


void left_correct()
{
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,100);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
}


void right_correct()
{
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,100);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
}



void stopp()
{
 analogWrite(3,0);
 analogWrite(5,0);
}

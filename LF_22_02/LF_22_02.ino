#define in1 8
#define in2 9
#define ena 3
#define in2 10
#define in3 11
#define enb 5

int l1=80;
int l2=90;
int l3=130;
int l4=150;
int l5=150;

int r1=80;
int r2=90;
int r3=130;
int r4=150;
int r5=150;

int flag = 0;

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

  display();


  //1
  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)){
  forward();
  Serial.println("forward");
  }

  //2
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  right1();
  Serial.println("Right +");
  }

  //3
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  right2();
  Serial.println("Right ++");
  }

  //4
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  right3();
  Serial.println("Right +++");
  }
  
  //5
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  right4();
  Serial.println("Right ++++");
  }

  //6
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  right5();
  Serial.println("Right +++++");
  }


  //7
  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)){
  left1();
  Serial.println("Left+");
  }

  //8
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)){
  left2();
  Serial.println("Left ++");
  }

  //9
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==0)){
  left3();
  Serial.println("Left +++");
  }

  //10
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)){
  left4();
  Serial.println("Left ++++");
  }
  
  //11
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)){
  left5();
  Serial.println("Left +++++");
  }

  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  stopp();
  Serial.println("Stop");
  backword();
  }

  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)){
  Serial.println("plus ...go straight");
  forward();
  }


  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)){
  Serial.println("plus ...sharp1 left");
  left();
  }

  else if((sensor[0]==1)&&(sensor[1]==1)&&((sensor[2]==1)||(sensor[3]==1))&&(sensor[4]==0)&&(sensor[5]==0)){
  Serial.println("plus ...sharp2 left");
  left();
  }

   else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)){
  Serial.println("plus ...sharp1 left");
  right();
  }

  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)){
  Serial.println("plus ...sharp2 left");
  right();
  }

  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)){
  Serial.println("plus ...sharp2 left");
  forward_L();
  }

  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)){
  Serial.println("plus ...sharp2 left");
  forward_L();
  }
  
  else{
    Serial.println("else condition");
    //stopp();
   backword();
  }

}

void display(){

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
  analogWrite(3,150);

  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  analogWrite(5,150);
}

void right()
{
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,150);

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
 analogWrite(5,150);
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

void backword(){
   digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  analogWrite(3,90);

  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  analogWrite(5,90);
  
}


void stopp()
{
 analogWrite(3,0);
 analogWrite(5,0);
}

//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void right1(){
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,r1);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
  }
  
void right2(){
  digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,r2);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
 }
 
void right3(){
  digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,r3);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
 }
 
void right4(){
  digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,r4);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
 }
 
void right5(){
  digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,r5);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,0);
 }

void left1(){
   digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,0);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,l1);
 }

 
void left2(){
   digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,0);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,l2);
 }
 
void left3(){
   digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,0);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,l3);
 }
 
void left4(){
   digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,0);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,l4);
 }
 
void left5(){
   digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,0);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,l5);
 }

 void strict_forward(){
 digitalWrite(8,HIGH);
 digitalWrite(9,LOW);
 analogWrite(3,100);

 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
 analogWrite(5,113);
  
 }
void forward_L(){

 }
 

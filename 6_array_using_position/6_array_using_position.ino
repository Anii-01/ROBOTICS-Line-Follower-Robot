int d1=A5;
int d2=A4;
int d3=A3;
int d4=A2;
int d5=A1;
int d6=A0;


int m1 =8;
int m2 =9;
int m3 =10;
int m4 =11;
int enA =3;
int enB =5;
int Amotor_speed=100;
int Bmotor_speed=100;
int motor_speed=100;
int cor=3;
int pos=0;
char r = 'u';
void setup() {
  // put your setup code here, to run once:
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);
  pinMode(d4,INPUT);
  pinMode(d5,INPUT);
  pinMode(d6,INPUT);

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    Amotor_speed=100;
    Bmotor_speed=100;
    motor_speed=60;
    pos=0;
  int a1=digitalRead(d1);
  int a2=digitalRead(d2);
  int a3=digitalRead(d3);
  int a4=digitalRead(d4);
  int a5=digitalRead(d5);
  int a6=digitalRead(d6);

  Serial.print(a1);
  Serial.print(a2);
  Serial.print(a3);
  Serial.print(a4);
  Serial.print(a5);
  Serial.println(a6);


  //corner sensor
  if(a1==1){
    cor=0;
  }
  if(a6==1){
    cor=1;
  }


  if(a1==0 && a2==0 && a3==0 && a4==0 && a5==0&& a6==0){
      if(cor==1){
      Amotor_speed=100;
      Bmotor_speed=100;
      motor_speed=60;
      right();
      }
      else if(cor==0){
      Amotor_speed=100;
      Bmotor_speed=100;
      motor_speed=60;
      left();
      }
      else if(cor==3){forward();}
    
  }
  else{
    if(a4==1){
      pos+=100;
    }
    if(a5==1){
      pos+=110;
    }
    if(a6==1){
      pos+=120;
    }

    if(a1==1){
      pos-=120;
    }
    if(a2==1){
      pos-=110;
    }
    if(a3==1){
      pos-=100;
    }
    Serial.println(pos);
    if(pos==0){
      forward();
    }
    else if(pos>=0){
      
          Bmotor_speed-=pos/12;
          Amotor_speed+=pos/12;
          Serial.print(Amotor_speed);
          Serial.println(Bmotor_speed);
          adjust(Amotor_speed,Bmotor_speed);
          Serial.print("right");          
    }
    else if(pos<=0){
          pos=pos*-1;
          Amotor_speed-=pos/12;
          Bmotor_speed+=pos/12;
          Serial.print(Amotor_speed);
          Serial.println(Bmotor_speed);
          adjust(Amotor_speed,Bmotor_speed);
          Serial.print("left");
      

      
          
    }




    
  }
  
}




void forward(){
  analogWrite(enA,motor_speed);
  analogWrite(enB,motor_speed);
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("forward");
  //delay(200);
}
void forwardcn(int Amotor_speed,int Bmotor_speed){
  analogWrite(enA,Amotor_speed);
  analogWrite(enB,Bmotor_speed);
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("forwards"+r);
  //delay(200);
}

void right(){
  analogWrite(enA,motor_speed);
  analogWrite(enB,0);
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
  Serial.println("right t");
}
void rights(){
  analogWrite(enA,70);
  analogWrite(enB,0);
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
  Serial.println("right s");
}
void rightu(){
  analogWrite(enA,motor_speed);
  analogWrite(enB,motor_speed);
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
  Serial.println("right U");
}

void left(){
  analogWrite(enA,0);
  analogWrite(enB,motor_speed);
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("left t");
}
void lefts(){
  analogWrite(enA,0);
  analogWrite(enB,70);
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("left s");
}
void leftu(){
  analogWrite(enA,motor_speed);
  analogWrite(enB,motor_speed);
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("left U");
}

void adjust(int a, int b){
  analogWrite(enA,a);
  analogWrite(enB,b);
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("adjust");
}

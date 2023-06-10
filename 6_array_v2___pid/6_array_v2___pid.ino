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
const uint8_t basespeeda=80;
const uint8_t basespeedb=80;
char r = 'u';
      

float Kp = 0.5;
float Ki = 0.00001;
float Kd = 0.5;

int P;
int I;
int D;

int lastError = 0;

void setup() {
 
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
//    motor_speed=100;
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
  

//else{
    if(a4==1){
      pos+=200;
    }
    if(a5==1){
      pos+=400;
      
    }
    if(a6==1){
      pos+=600;

    }

    if(a1==1){
      pos-=600;
      
    }
    if(a2==1){
      pos-=400;

    }
    if(a3==1){
      pos-=200;
    }
    Serial.print("position=");
    Serial.print(pos);


  int error=pos;
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  int motorspeed = P*Kp + I*Ki + D*Kd; //calculate the correction
                                       //needed to be applied to the speed
  
  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;
  Serial.print(motorspeeda);
  Serial.println(motorspeedb);
  
  if (motorspeeda > 250) {
    motorspeeda = 250;
  }
  if (motorspeedb > 250) {
    motorspeedb = 250;
  }
  if (motorspeeda < 0) {
    motorspeeda =0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  } 
  adjust(motorspeeda,motorspeedb); 
//}

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
      motor_speed=70;
       if(a4!=1){
        rightu();}
        }
        else if(a4==1){leftu();}
      else if(cor==0){
      Amotor_speed=100;
      Bmotor_speed=100;
      motor_speed=70;
      
      if(a3!=1){leftu();}
      }
      else if(a3==1){rightu();}
      
      else if(cor==3){}
    
  }
  else if(a1==1 && a2==1 && a3==1 && a4==1 && a5==1&& a6==1){
    forward();
  }

}

void forward(){
  analogWrite(enA,motor_speed);
  analogWrite(enB,motor_speed);
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("forward");
  //delay(200);
}


void right(){
  analogWrite(enA,90);
  analogWrite(enB,0);
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
  Serial.println("right t");
  delay(100);
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
  analogWrite(enA,120);
  analogWrite(enB,120);
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
  Serial.println("right U");
}

void left(){
  analogWrite(enA,0);
  analogWrite(enB,90);
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("left t");
  delay(100);
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
  analogWrite(enA,120);
  analogWrite(enB,120);
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
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

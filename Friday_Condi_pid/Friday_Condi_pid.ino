int S1=A0;
int S2=A1;
int S3=A3;
int S4=A4;
int S5=A5;
int S6=A6;

int m1 =8;
int m2 =9;
int enA =3;
int m3 =10;
int m4 =11;
int enB =5;

 int sen1;
 int sen2;
 int sen3;
 int sen4;
 int sen5;
 int sen6;

// **********************for pid**********************

int R_motor_speed=100;
int L_motor_speed=100;
int motor_speed = 100;

int point_sens = 3;

int pos=0;
int basespeed = 125;

float Kp = 0.05;
float Ki = 0.00001;
float Kd = 0.8;

int P;
int I;
int D;
int lastError = 0;

void adjust(int motorspeeda,int motorspeedb);
void forward();
void rightu();
void leftu();


// **********************for pid**********************

void setup() {
  // put your setup code here, to run once:
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);

  Serial.begin(9600);
  
}

void loop(){
  R_motor_speed = 100;
  L_motor_speed = 100;
  motor_speed = 100;
  pos = 0;

   sen1=digitalRead(S1);
   sen2=digitalRead(S2);
   sen3=digitalRead(S3);
   sen4=digitalRead(S4);
   sen5=digitalRead(S5);
   sen6=digitalRead(S6);

  //S1,S2,S3,S4,S5,S6

  if(S4==1){pos=pos+500;}
  if(S5==1){pos=pos+1000;}
  if(S6==1){pos=pos+1500;}

  if(S1==1){pos=pos-500;}
  if(S2==1){pos=pos-1000;}
  if(S3==1){pos=pos-1500;}

  Serial.println(pos);

  int error=pos;

  //**************** PID*************

  I = I + error;
  
  D = error - lastError;
  
  lastError = error;
  
  int motorspeed = P*Kp + I*Ki + D*Kd; 
  
  int motorspeeda = basespeed + motorspeed;
  int motorspeedb = basespeed - motorspeed;
  
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


  if(S1==1){
    point_sens=0;
  }
  if(S6==1){
    point_sens=1;
  }

 if(S1==0 && S2==0 && S3==0 && S4==0 && S5==0&& S6==0){
      if(point_sens==1){
          motor_speed=100;
          if(S4!=1){
            rightu();
            }
      }
         
           else if(S4==1){
             leftu();
            }

           else if(point_sens==0){
         
           R_motor_speed=100;
           L_motor_speed=100;
           motor_speed=100;

          if(S3!=1){
            leftu();
            }
         }
           else if(S3==1){
            rightu();
            }
           else if(point_sens==3){
            forward();}
}
else if(S1==1 && S2==1 && S3==1 && S4==1 && S5==1&& S6==1){
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


        
        


//***************** Functions **********************


void display_sensor_value(){
  Serial.print(sen1);
  Serial.print(sen2);
  Serial.print(sen3);
  Serial.print(sen4);
  Serial.print(sen5);
  Serial.println(sen6);

}

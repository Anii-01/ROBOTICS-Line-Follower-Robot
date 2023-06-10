#define in1 8
#define in2 9
#define ena 3
#define in3 10
#define in4 11
#define enb 5

int speeed = 100;
void setup() {
  // put your setup code here, to run once:
  pinMode(in1,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(ena,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(in3,OUTPUT);
  pinMode(enb,OUTPUT);  
  Serial.begin(9600); 

}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  

}

void forward()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena,speeed);

  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb,speeed + 20);
}

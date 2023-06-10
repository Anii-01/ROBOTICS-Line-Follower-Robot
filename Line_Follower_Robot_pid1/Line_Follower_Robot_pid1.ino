// IR Sensors
int sensor1 = A0;    
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;     
int sensor5 = A4;
int sensor6 = A5;


// Initial Values of Sensors
int sensor[6] = {0, 0, 0, 0, 0,0};

// Motor Variables
int ENA = 3;
int motorInput1 = 8;
int motorInput2 = 9;
int motorInput3 = 10;
int motorInput4 = 11;
int ENB = 5;

//Initial Speed of Motor

int initial_motor_speed = 100;  //140

int sensor_pos=0;





// PID Constants
float Kp = 25;
float Ki = 0;
float Kd = 15;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

 

  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  delay(500);
  Serial.println("Started !!");
  delay(1000);
}
void loop()
{

 
    sensor_pos=0;
  
  read_sensor_values();
  sensor_value_display();
  Serial.print(error);
  
  if (error == 100){               // Make left turn untill it detects straight path
    Serial.print("\t");
    Serial.println("Left");
    do {
      read_sensor_values();
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      sharpLeftTurn();
    } while (error != 0);

  } else if (error == 101) {          // Make right turn in case of it detects only right path (it will go into forward direction in case of staright and right "|--")
                                      // untill it detects straight path.
    Serial.print("\t");
    Serial.println("Right");
    analogWrite(ENA, 110); //Left Motor Speed
    analogWrite(ENB, 90); //Right Motor Speed
    forward();
    delay(200);
    stop_bot();
  
    read_sensor_values();
    
    if (error == 102) {
      do {
        analogWrite(ENA, 110); //Left Motor Speed
        analogWrite(ENB, 90); //Right Motor Speed
        sharpRightTurn();
        read_sensor_values();
      } while (error != 0);
    }
  } else if (error == 102) {        // Make left turn untill it detects straight path
    //Serial.print("\t");
    //Serial.println("Sharp Left Turn");
    do {
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      sharpLeftTurn();
      read_sensor_values();
      if (error == 0) {
        stop_bot();
        delay(200);
      }
    } while (error != 0);
    
  } else if (error == 103) {        // Make left turn untill it detects straight path or stop if dead end reached.
    if (flag == 0) {
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      forward();
      delay(200);
      stop_bot();
      read_sensor_values();
      if (error == 103) {     /**** Dead End Reached, Stop! ****/
        stop_bot();
     
        flag = 1;
      }
      else {        /**** Move Left ****/
        analogWrite(ENA, 110); //Left Motor Speed
        analogWrite(ENB, 90); //Right Motor Speed
        sharpLeftTurn();
        delay(200);
        do {
          //Serial.print("\t");
          //Serial.println("Left Here");
          read_sensor_values();
          analogWrite(ENA, 110); //Left Motor Speed
          analogWrite(ENB, 90); //Right Motor Speed
          sharpLeftTurn();
        } while (error != 0);
      }
    }
  } 
  else {
    calculate_pid();
    motor_control();
  }
}

void read_sensor_values()
{
  sensor[0] = digitalRead(sensor1);
  sensor[1] = digitalRead(sensor2);
  sensor[2] = digitalRead(sensor3);
  sensor[3] = digitalRead(sensor4);
  sensor[4] = digitalRead(sensor5);
  sensor[5] = digitalRead(sensor6);

  /*
    Serial.print(sensor[0]);
    Serial.print(" ");
    Serial.print(sensor[1]);
    Serial.print(" ");
    Serial.print(sensor[2]);
    Serial.print(" ");
    Serial.println(sensor[3]);
    Serial.print(" ");
    Serial.print(sensor[4]);
    Serial.print(" ");
    Serial.print(sensor[5]);
    Serial.print(" ");
   */ 

   
  /*  

  if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1)&&(sensor[4] == 0) && (sensor[5] == 0)){
    error = 0;
  }
   else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)&&(sensor[4] == 0) && (sensor[5] == 0))
    error = 1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)&&(sensor[4] == 1) && (sensor[5] == 0))
    error = 2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)&&(sensor[4] == 1) && (sensor[5] == 1))
    error = 3;
    
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0)&&(sensor[4] == 0) && (sensor[5] == 0))
    error = -1;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)&&(sensor[4] == 0) && (sensor[5] == 0))
    error = -2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)&&(sensor[4] == 0) && (sensor[5] == 0))
    error = -3;

   else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)&&(sensor[4] == 0) && (sensor[5] == 0))
    stop_bot();

   else {
    stop_bot();
   }

   */
   

  if(sensor[0] == 1){sensor_pos=sensor_pos-1;}
  if(sensor[1] == 1){sensor_pos=sensor_pos-1;}
  if(sensor[2] == 1){sensor_pos=sensor_pos-1;}

  if(sensor[3] == 1){sensor_pos=sensor_pos+1;}
  if(sensor[4] == 1){sensor_pos=sensor_pos+1;}
  if(sensor[5] == 1){sensor_pos=sensor_pos+1;}

  //if(sensor[3] == 1){sensor_pos=100+1;}
  //if(sensor[4] == 1){sensor_pos=100+1;}
  //if(sensor[5] == 1){sensor_pos=100+1;}

  Serial.println(sensor_pos);

  error = sensor_pos;

  

  /*
    
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)&&(sensor[4] == 0) && (sensor[5] == 1)) // Turn robot left side
    error = 100;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)&&(sensor[4] == 0) && (sensor[5] == 1)) // Turn robot right side
    error = 101;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&&(sensor[4] == 0) && (sensor[5] == 1)) // Make U turn
    error = 102;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&&(sensor[4] == 1) && (sensor[5] == 0)) // Turn left side or stop
    error = 103;

   */
}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  Serial.print(PID_value);
    Serial.print("\t");
    Serial.print(left_motor_speed);
    Serial.print("\t");
    Serial.println(right_motor_speed);

  analogWrite(ENA, left_motor_speed); //Left Motor Speed
  analogWrite(ENB, right_motor_speed); //Right Motor Speed

  //following lines of code are to make the bot move forward

  forward();

  /*
  if(sensor_pos==0){
  forward();
  Serial.println("forward");
  }

  else if(sensor_pos==1){
   right(); 
  Serial.println("right");
  }
  else if(sensor_pos==2){
   right();
  Serial.println("right"); 
  }
   else if(sensor_pos==3){
   sharpRightTurn(); 
   Serial.println("sharpRightTurn");
  }

   else if(sensor_pos==-1){
   left(); 
   Serial.println("left");
   
   
  }
   else if(sensor_pos==-2){
   left(); 
   Serial.println("left");
  }
   else if(sensor_pos==-3){
   sharpRightTurn(); 
   Serial.println("sharpRightTurn");
  }

  
 
 */
 
 }
 

void forward()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
   Serial.println("forward");
}
void reverse()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
   Serial.println("REVERSE");
}
void right()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
   Serial.println("RIGHT");
}
void left()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
   Serial.println("LEFT");
}
void sharpRightTurn() {
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
   Serial.println("SHARP RIGHT TURN");
}
void sharpLeftTurn() {
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
   Serial.println("SHARP LEFT TURN");
}
void stop_bot()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
   Serial.println("STOP");
}


void sensor_value_display()
{
   Serial.print("    ");
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
//Macros for Arduino Mega pins definition
#define sensor_left A9         //one of 3 sensors used for line follower
#define sensor_middle A8       //one of 3 sensors used for line follower
#define sensor_right A10       //one of 3 sensors used for line follower
#define threshold 500          //the threshold used to digitized the analog value of sensors

//Variables
float Duty_Cycle = 0.7;
int motor_right_up=15;
int motor_right_down=16;
int motor_left_up=4;
int motor_left_down=5;
int pwm_Left=11, pwm_Right=13;

/**
 * Reads analog sensor data than returns boolean number if the read value exceeds the threshold variable.
 * @param pin (integer) Sensor pin.
 * @return (boolean) sensor state
 */
int Read_One_Sensor(int pin)
{
  if(analogRead(pin)>threshold)
        return(1); 
  else 
        return(0);
}

/**
 * Reads all analog sensors than returns boolean payload where each bit represents a sensor state.
 * @return (integer) payload.
 */
int Read_All_Sensors()
{
  return (Read_One_Sensor(sensor_left)*100+Read_One_Sensor(sensor_middle)*10+Read_One_Sensor(sensor_right));
}

/**
 * @brief Set DAC value to stop motors.
 * @return (void)
 */
void Stop_Motors () 
{
  analogWrite(pwm_Left,0);
  digitalWrite(motor_left_up,LOW);
  digitalWrite(motor_left_down,LOW);
  analogWrite(pwm_Right,0);
  digitalWrite(motor_right_up,LOW);
  digitalWrite(motor_right_down,LOW);
}

/**
 * @brief Set DAC value to turn the robot left.
 * @return (void)
 */
void Turn_Left () 
{   
  analogWrite (pwm_Right, Duty_Cycle * 255); 
  digitalWrite(motor_right_up, HIGH);
  digitalWrite(motor_right_down, LOW);
  analogWrite (pwm_Left, 0.5 * Duty_Cycle * 255); 
  digitalWrite(motor_left_up, LOW);
  digitalWrite(motor_left_down, HIGH);
}

/**
 * @brief Set DAC value to turn the robot right.
 * @return (void)
 */
void Turn_Right () 
{ 
  analogWrite (pwm_Left, Duty_Cycle * 255); 
  digitalWrite(motor_left_up, HIGH);
  digitalWrite(motor_left_down, LOW);
  analogWrite (pwm_Right, 0.5 * Duty_Cycle * 255); 
  digitalWrite(motor_right_up, LOW);
  digitalWrite(motor_right_down, HIGH);
}

/**
 * @brief Going forward function
 * 
 * @return (void)
 * */
void Going_Forward ()    
{
  while( Read_All_Sensors() == 010 )
  { 
    analogWrite (pwm_Right, Duty_Cycle*255); 
    digitalWrite(motor_right_up, HIGH);
    digitalWrite(motor_right_down, LOW);
    analogWrite (pwm_Left, Duty_Cycle*255); 
    digitalWrite(motor_left_up, HIGH);
    digitalWrite(motor_left_down, LOW);
  }
}

//setup mode
void  setup(){

    //Motors configuration
    pinMode(motor_left_up, OUTPUT);
    pinMode(motor_left_down, OUTPUT);
    pinMode(motor_right_up, OUTPUT);
    pinMode(motor_right_down, OUTPUT);
    pinMode(pwm_Right, OUTPUT);
    pinMode(pwm_Left, OUTPUT);

    //Sensors configuration
    pinMode(sensor_left,INPUT);
    pinMode(sensor_middle,INPUT);
    pinMode(sensor_right,INPUT);
}

//loop mode
void loop() 
{  
  switch(Read_All_Sensors())
  {
    case(010):
       {
          Going_Forward();
          break;
       }
    case(001):
       {
          Turn_Right();
          break;
       }
    case(011):
       {
          Turn_Right();
          break;
       }
    case(100):
       {
          Turn_Left();
          break;
       }
    case(110):
       {
          Turn_Left();
          break;
       }
  }  
}

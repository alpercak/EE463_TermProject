/*Bu code 330V-140V arası voltajı 24Vta çevirmek için tasarlanmış Buckconverterın 
PID control ile 2A civarı output current vermesini sağlamak için
Duty cycle controlü yapacaktır*/

#include <PID_v1.h>    //This library include PID functions thats are used in our code
#include <PWM.h>

#define PIN_INPUT 0              // anaog input pin from current sence resistor
#define PIN_OUTPUT 3             // PWM output pin for duty cycle

int32_t frequency = 50000;  //frequency (in Hz)

/* duty cyle will change with PID feedback but initially it has smallest Value
 *  that appear at input voltage 330V  that is  %7.2 for 16 bit wise 4765
*/

int Duty = 4765;
int Duty_With_Feedback;
/*setpoint for PID control. We are using 0.01 ohm current sence resistor and desired voltage = 0.02V
 analogread has 4095 resulution for 5 volts so for our case setpoint = 15.384; */
double Setpoint;               


double PID_Input; 
double PID_Output;


//PID parameters
double Kp=2, Ki=5, Kd=1;  
PID myPID(&PID_Input, &PID_Output, &Setpoint, Kp, Ki, Kd, DIRECT);  //creating PID object

void setup() {
  Serial.begin(9600);

  //PWM setup
  InitTimersSafe(); //set timers
  bool success = SetPinFrequencySafe(PIN_OUTPUT,frequency);  // set output PWM frequency



 // PID setup
  PID_Input = analogRead(PIN_INPUT);   //initialize the variables we're linked to
  Setpoint = 15.384;
  myPID.SetSampleTime(1);  //since our system is not contunious PID have sample time and it setted 1 ms
  myPID.SetMode(AUTOMATIC);  //turn the PID on
}

/* This loop countuniously get current sence resistors voltage and make PID calculation 
 *  then set new PWM dutyvalue 
*/
void loop() {
   PID_Input = analogRead(PIN_INPUT);
   myPID.Compute();
   Duty_With_Feedback = (int)PID_Output + Duty ;
   pwmWriteHR(PIN_OUTPUT, (uint16_t)Duty_With_Feedback);
   delay(1);

}

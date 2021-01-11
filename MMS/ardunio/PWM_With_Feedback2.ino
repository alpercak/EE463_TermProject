/*Bu code 330V-140V arası voltajı 24Vta çevirmek için tasarlanmış Buckconverterın 
PID control ile 2A civarı output current vermesini sağlamak için
Duty cycle controlü yapacaktır*/
#include <PWM.h>
#define PIN_INPUT 14              // anaog input pin from current sence resistor
#define PIN_OUTPUT 3             // PWM output pin for duty cycle

int32_t frequency = 50000;  //frequency (in Hz)

/* duty cyle will change with PID feedback but initially it has smallest Value
 *  that appear at input voltage 330V  that is  %7.2 for 16 bit wise 4765
*/

double Duty = 4765;
double Duty_With_Feedback = 0;
/*setpoint for PID control. We are using 0.01 ohm current sence resistor and desired voltage = 0.02V
 analogread has 1024 resulution for Vref volts so for our case Vref = 5/11 V setpoint = (0.02/Vref)*1024 = 45.055999999999999999999999999994 ; */
         
double Setpoint =45.056; 

double PID_Input_Value =0; 
double PID_Output_Value = 0;
double error = 0;
double integrated_error = 0;
double proportional_error = 0;
//PID parameters
double Kp=10, Ki=10;  

void setup() {
Serial.begin(9600);


  //PWM setup
  InitTimersSafe(); //set timers
  bool success = SetPinFrequencySafe(PIN_OUTPUT,frequency);  // set output PWM frequency
}

/* This loop countuniously get current sence resistors voltage and make PID calculation 
 *  then set new PWM dutyvalue 
*/

void loop() {
   PID_Input_Value = analogRead(PIN_INPUT);
   error = Setpoint - (double)PID_Input_Value;
   integrated_error = integrated_error + Ki * error;
   proportional_error = Kp * error;
   PID_Output_Value = proportional_error + integrated_error;
   Duty_With_Feedback = Duty + PID_Output_Value; 
   if(Duty_With_Feedback > 65535.0){Duty_With_Feedback = 65535.0;}
   if(Duty_With_Feedback < 0){Duty_With_Feedback = 1;}
   Serial.println(Duty_With_Feedback/65535.0);    
   pwmWriteHR(PIN_OUTPUT, (uint16_t)Duty_With_Feedback);
delay(1);

   /*
   Serial.println("-------------------------------- ");
   Serial.println("PID_Input_Value ");
   Serial.println(PID_Input_Value);
   Serial.println("error ");
   Serial.println(error);
   Serial.println("Duty_With_Feedback ");
   Serial.println(Duty_With_Feedback );
   delay(100);
   */
}

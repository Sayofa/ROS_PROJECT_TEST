#include <ros.h>
#include <geometry_msgs/Point32.h> //For sending encoder msg
#include<geometry_msgs/Twist.h> //For cmd_vel subscription
#include <Encoder.h> //Encoder library




//------------------------------------------ DC Motor definitions------------

///////////////////// Pin variables for motors.////////////////////////



const int LM1_FW = 22;
const int LM1_BW = 23;
const int LM1_PWM = 4;

const int RM1_FW = 24;
const int RM1_BW = 25;
const int RM1_PWM = 5;




const int LM2_FW = 26;
const int LM2_BW = 27;
const int LM2_PWM = 6;

const int RM2_FW = 28;
const int RM2_BW = 29;
const int RM2_PWM = 7;



const int LM3_FW = 30;
const int LM3_BW = 31;
const int LM3_PWM = 8;


const int RM3_FW = 32;
const int RM3_BW = 33;
const int RM3_PWM = 9;
 //-----------------------------------------Robot parameters definition------------ 


#define L 0.33
#define R 0.05

//----------------------------------------------Encoder definitions------------------



Encoder R_enc(19, 18); //right motor encoder goes for pins 19 18
Encoder L_enc(21, 20); //left motor encoder goes for pins 21 20
long RoldPosition  = -999;
long LoldPosition  = -999;




//--------------------------------Motors VARS-----------------------------------

// initializing variables
float vel=0.0; //as Twist msgs depend on Vector3 which is float64
float omega=0.0;
float VR,VL;


//-----------------------------------------------------------------------------------------
ros::NodeHandle  nh;



void MoveStop() {

  analogWrite(LM1_PWM, 0);
  analogWrite(RM1_PWM, 0);
  analogWrite(LM2_PWM, 0);
  analogWrite(RM2_PWM, 0);
  analogWrite(LM3_PWM, 0);
  analogWrite(RM3_PWM, 0);
}



//------------------------------Publish init----------------------------------------------
geometry_msgs::Point32 Point_msg;

ros::Publisher enc_pub("/encoder", &Point_msg); 


//-----------------------------------DC Motors Callback subscribers

void motors_cb(const geometry_msgs::Twist& msg)
{
 
    vel=msg.linear.x;    
    omega=msg.angular.z;  
    
     
    VR=(2*vel+omega*L)/(2*R); 
    VL=(2*vel-omega*L)/(2*R); 

    //-----right motor------

    if (VR<0)
    {
        digitalWrite(RM1_FW, LOW);
        digitalWrite(RM1_BW, HIGH);
        analogWrite(RM1_PWM, abs(VR));
        
        digitalWrite(RM2_FW, LOW);
        digitalWrite(RM2_BW, HIGH);
        analogWrite(RM2_PWM, abs(VR));
        
        digitalWrite(RM3_FW, LOW);
        digitalWrite(RM3_BW, HIGH);
        analogWrite(RM3_PWM, abs(VR));

    }

    else 
    {
        digitalWrite(RM1_FW, HIGH);
        digitalWrite(RM1_BW, LOW);
        analogWrite(RM1_PWM, abs(VR));
        
        digitalWrite(RM2_FW, HIGH);
        digitalWrite(RM2_BW, LOW);
        analogWrite(RM2_PWM, abs(VR));
        
        digitalWrite(RM3_FW, HIGH);
        digitalWrite(RM3_BW, LOW);
        analogWrite(RM3_PWM, abs(VR));
        
    }

    //-----left motor------

     if (VL<0)
    {


        digitalWrite(LM1_FW, LOW);
        digitalWrite(LM1_BW, HIGH);
        analogWrite(LM1_PWM, abs(VL));
        
        digitalWrite(LM2_FW, LOW);
        digitalWrite(LM2_BW, HIGH);
        analogWrite(LM2_PWM, abs(VL));
        
        digitalWrite(LM3_FW, LOW);
        digitalWrite(LM3_BW, HIGH);
        analogWrite(LM3_PWM, abs(VL)); 
    }

    else 
    {
      
        digitalWrite(LM1_FW, HIGH);
        digitalWrite(LM1_BW, LOW);
        analogWrite(LM1_PWM, abs(VL));
        
        digitalWrite(LM2_FW, HIGH);
        digitalWrite(LM2_BW, LOW);
        analogWrite(LM2_PWM, abs(VL));
        
        digitalWrite(LM3_FW, HIGH);
        digitalWrite(LM3_BW, LOW);
        analogWrite(LM3_PWM, abs(VL));
        
    }

 if (VR == 0){
      MoveStop();
  }

}

//--------------------subscribers---------------------------
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &motors_cb);


void setup() {
  // put your setup code here, to run once:


  Serial.begin (57600);    


  pinMode(LM1_FW, OUTPUT);    // sets the digital pin 13 as output
  pinMode(LM1_BW, OUTPUT);
  pinMode(LM1_PWM, OUTPUT);
  
  pinMode(RM1_FW, OUTPUT);    
  pinMode(RM1_BW, OUTPUT);
  pinMode(RM1_PWM, OUTPUT);

  pinMode(LM2_FW, OUTPUT);    
  pinMode(LM2_BW, OUTPUT);
  pinMode(LM2_PWM, OUTPUT);
  
  pinMode(RM2_FW, OUTPUT);    
  pinMode(RM2_BW, OUTPUT);
  pinMode(RM2_PWM, OUTPUT);
  
  pinMode(LM3_FW, OUTPUT);    
  pinMode(LM3_BW, OUTPUT);
  pinMode(LM3_PWM, OUTPUT);
  
  pinMode(RM3_FW, OUTPUT);    
  pinMode(RM3_BW, OUTPUT);
  pinMode(RM3_PWM, OUTPUT);
  
 

  
  // Set initial values for directions. Set both to forward.
        digitalWrite(RM1_FW, HIGH);
        digitalWrite(RM1_BW, LOW);
        digitalWrite(RM2_FW, HIGH);
        digitalWrite(RM2_BW, LOW);
        digitalWrite(RM3_FW, HIGH);
        digitalWrite(RM3_BW, LOW);

        digitalWrite(LM1_FW, HIGH);
        digitalWrite(LM1_BW, LOW);
        digitalWrite(LM2_FW, HIGH);
        digitalWrite(LM2_BW, LOW);
        digitalWrite(LM3_FW, HIGH);
        digitalWrite(LM3_BW, LOW);
        

  
 
  
  
  

  // Send forward command.
  analogWrite(LM1_PWM, 200);
  analogWrite(LM2_PWM, 200);
  analogWrite(LM3_PWM, 200);

  analogWrite(RM1_PWM, 200);
  analogWrite(RM2_PWM, 200);
  analogWrite(RM3_PWM, 200);


  

  delay(500);
  MoveStop();






}

void loop() {
  // put your main code here, to run repeatedly:

 //Right Encoder
     long RnewPosition = R_enc.read();
     if (RnewPosition != RoldPosition) {
          RoldPosition = RnewPosition; 

          
          Serial.println(RnewPosition);
        } 
        
  //----left encoder
  long LnewPosition = L_enc.read();
  if (LnewPosition != LoldPosition) {
      LoldPosition = LnewPosition; //update positions
      Serial.println(LnewPosition);
      }  
//-------end of encoder

//-----------------------ROS publishing  
        Point_msg.x=RnewPosition;
        Point_msg.y=LnewPosition;
        enc_pub.publish(&Point_msg);
//-------------        
      nh.spinOnce(); 
      delay(10);

}

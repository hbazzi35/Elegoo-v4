// ---------------------Begin v4 -----------------------------------------

//    The direction of the car's movement TB6612 (v4)
//  PWMA   PWMB   AIN_1   BIN_1   STBY      Description  
//  PWM    PWM    HIGH    HIGH    HIGH      Car is running forward
//  PWM    PWM    LOW     LOW     HIGH      Car is running back
//  PMW    PWM    HIGH    LOW     HIGH      Car is turning left
//  PWM    PWM    LOW     HIGH    HIGH      Car is turning right
//  0      0      N/A     N/A     LOW       Car is stopped (direction_void)

//define TB6612 module IO Pins
#define STBY 3 //STBY
#define ENA 5 //PWMA
#define ENB 6 //PWMB
#define AIN_1 7 //AIN_1
#define BIN_1 8 //BIN_1

#define LT_R A0
#define LT_M A1
#define LT_L A2

#define carSpeed 100 //Set value 0-255, 8-bit 

//If the value read by the photoelectric sensor is within 250 ~ 850,
//the photoelectric sensor is in the black line.
uint16_t TrackingDetection_S = 500;
uint16_t TrackingDetection_E = 750;

void forward(){ 
  analogWrite(ENA,carSpeed); //enable A channel
  analogWrite(ENB,carSpeed); //enable B channel
  digitalWrite(AIN_1,HIGH); //set AIN_1 high level
  digitalWrite(BIN_1,HIGH);  //set BIN_1 high level
  digitalWrite(STBY,HIGH);  //set STBY high level
  Serial.println("Forward");//send message to serial monitor
}

void back(){
  analogWrite(ENA,carSpeed); //enable A channel
  analogWrite(ENB,carSpeed); //enable B channel
  digitalWrite(AIN_1,LOW); //set AIN_1 low level
  digitalWrite(BIN_1,LOW);  //set BIN_1 low level
  digitalWrite(STBY,HIGH);  //set STBY high level
  Serial.println("Back");
}

void left(){
  analogWrite(ENA,carSpeed); //enable A channel
  analogWrite(ENB,carSpeed); //enable B channel
  digitalWrite(AIN_1, HIGH); //set AIN_1 low level
  digitalWrite(BIN_1,LOW);  //set BIN_1 low level
  digitalWrite(STBY,HIGH);  //set STBY high level
  Serial.println("Left");
}

void right(){
  analogWrite(ENA,carSpeed); //enable A channel
  analogWrite(ENB,carSpeed); //enable B channel
  digitalWrite(AIN_1, LOW); //set AIN_1 low level
  digitalWrite(BIN_1,HIGH);  //set BIN_1 low level
  digitalWrite(STBY,HIGH);  //set STBY high level
  Serial.println("Right");
}

void stopCar(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   digitalWrite(STBY,LOW);  //set STBY low level
   Serial.println("Stop!");
}

//before execute loop() function, 
//setup() function will execute first and only execute once
void setup() {
  pinMode(AIN_1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(BIN_1,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(LT_L, INPUT);
  pinMode(LT_M, INPUT);
  pinMode(LT_R, INPUT);
  Serial.begin(9600);//open serial and set the baudrate`
}

//Repeat execution
//Analog value needs to be read and determine a threshold value for detection, usually between 250 & 850
//If the value detected is between these, then the line is detected and follow the logic

int i = 0;

void loop() {
  
  // Test algorithm to output to serial monitor
  // Check and see if values are between 250 & 850 when detecting a line
  Serial.print("ITR20001_getAnaloguexxx_L=");
  Serial.println(analogRead(LT_L));
  Serial.print("ITR20001_getAnaloguexxx_M=");
  Serial.println(analogRead(LT_M));
  Serial.print("ITR20001_getAnaloguexxx_R=");
  Serial.println(analogRead(LT_R));
  
#define M (TrackingDetection_S <= analogRead(LT_M) && analogRead(LT_M) <= TrackingDetection_E)
#define L (TrackingDetection_S <= analogRead(LT_L) && analogRead(LT_L) <= TrackingDetection_E)
#define R (TrackingDetection_S <= analogRead(LT_R) && analogRead(LT_R) <= TrackingDetection_E)
  while(true){   
    if(i == 4){
      stopCar();
      break;
    }else{
      if(M && L && R){
        forward();
        delay(500);
        i++;
      }
      else if(M && !L && !R){
        forward();
      }
      else if(!M && L && !R){
        left();
      }
      else if(!M && !L && R){
        right();
      }
    }
 }
  exit(0);
}
  

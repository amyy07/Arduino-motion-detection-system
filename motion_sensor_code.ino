#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

//for the time
int startHour;
int startMinute;
int startSecond;

unsigned long startMillis;

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;


/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    Serial.println("Enter current time as HH MM SS");
    while (Serial.available() == 0) {
      // Wait for user input
    }

    startHour = Serial.parseInt();
    startMinute = Serial.parseInt();
    startSecond = Serial.parseInt();

    startMillis = millis();

    Serial.print("Time set to: ");
    Serial.print(startHour);
    Serial.print(":");
    Serial.print(startMinute);
    Serial.print(":");
    Serial.println(startSecond);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Sensor Ready");

  
  }

////////////////////////////
//LOOP
void loop(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         unsigned long elapsedSeconds = (millis() - startMillis) / 1000;


        //calculating time
        int currentSecond = startSecond + elapsedSeconds;
        int currentMinute = startMinute + currentSecond / 60;
        int currentHour = startHour + currentMinute / 60;

        currentSecond %= 60;
        currentMinute %= 60;
        currentHour %= 24;
         delay(50);
        
        //outputting to LCD display
        lcd.setCursor(0,0);
        lcd.print("Last motion at:");

        lcd.setCursor(3,1);
        if (currentHour < 10)
            lcd.print("0");
        lcd.print(currentHour);

        lcd.print(":");

        if (currentMinute < 10)
            lcd.print("0");
        lcd.print(currentMinute);

        lcd.print(":");

        if (currentSecond < 10)
            lcd.print("0");
        lcd.print(currentSecond);

        lcd.print(" H");
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }
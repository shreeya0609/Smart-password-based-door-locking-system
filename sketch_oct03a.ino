 #include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include<EEPROM.h>
#include <SoftwareSerial.h>

Servo servo_Motor;
char input;
int pos=0;
char* password = "111";
int position = 0;
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPin[ROWS] = { 8, 7, 6, 9 };
byte colPin[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPin, colPin, ROWS, COLS );
int redPin = 12;
int greenPin = 13;

int buzzer = 10;
int wrong = 0;
int state = 0;
int total = 0; 
int inc = 0;
void setup()
{
  Serial.begin(9600);
  
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(buzzer,OUTPUT);
 
lcd.begin(16,2);
lcd.print("SHREEYA");
lcd.setCursor(0,2);

lcd.clear();
servo_Motor.attach(11);
setLocked(true);




}

void loop()
{
  
  lcd.clear();
    
  lcd.print("SHREEYA");
  lcd.setCursor(0,2);
  lcd.print("Enter Password:");
  delay(100);
  
 char pressed=keypad.getKey();
 String key[3];
 
  
 if(pressed) 
 {
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(5);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }

    else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != password[position] )
      {
          wrong++;
          position ++;
      }

    if(position == 3)
      {
          if( wrong >0) 
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.print("WRONG");
                lcd.setCursor(5,2);
                lcd.print("PASSWORD");
                digitalWrite(buzzer,HIGH);
                delay(1000);
                setLocked(true);
                digitalWrite(buzzer,LOW);
            }

          else if(position == 3 && wrong == 0)
            {
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.print("PASSWORD");
                lcd.setCursor(6,2);
                lcd.print("ACCEPTED");
                delay(2000);
                lcd.clear();
                lcd.print("DOOR OPENED");
                setLocked(false);
                delay(10000);
                lcd.clear();
                lcd.print("DOOR CLOSED");
                delay(1000);
                lcd.clear();
                setLocked(true);
                
               
            }

          if(total ==3)
            {
                total=0;
                digitalWrite(buzzer,HIGH);
                digitalWrite(redPin,HIGH);
                digitalWrite(greenPin,HIGH);
                delay(1000);
                digitalWrite(buzzer,LOW);
                digitalWrite(greenPin,LOW);
            }

        }

   }

if(Serial.available() > 0)  
  {
    inc = Serial.read();      
    Serial.print(inc);        
    Serial.print("\n");        
    if(inc == '1') {            
      digitalWrite(greenPin, HIGH); 
      digitalWrite(redPin, LOW);
      
       lcd.clear();
                lcd.print("PASSWORD");
                lcd.setCursor(6,2);
                lcd.print("ACCEPTED");
                delay(2000);
                lcd.clear();
                lcd.print("DOOR OPENED");
                setLocked(false);
                delay(10000);
                lcd.clear();
                lcd.print("DOOR CLOSED");
                delay(1000);
                lcd.clear();
                setLocked(true);
      Serial.println("off"); }
    else {      
      digitalWrite(greenPin, LOW);
       lcd.clear();
                lcd.print("WRONG");
                lcd.setCursor(5,2);
                lcd.print("PASSWORD");
                digitalWrite(buzzer,HIGH);
                delay(1000);
                setLocked(true);
                digitalWrite(buzzer,LOW);
                servo_Motor.write(11);} 
  }             
}

void setLocked(int locked)
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
         servo_Motor.write(11);
         
   
        
      }
    else
      {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
         digitalWrite(buzzer,LOW);
          servo_Motor.write(90);
          
         
         
      }
  }

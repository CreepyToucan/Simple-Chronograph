#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensorStartPin_1 = 6;
const int sensorStartPin_2 = 5;
const int sensorEndPin_1 = 4;
const int sensorEndPin_2 = 3;
const int buttonPin = 8;
const int buzzerPin = 7;

volatile bool select = false; 
volatile bool started = false;
volatile bool finished = false;

unsigned long startTime = 0;
unsigned long endTime = 0;

float distance_cm = 4.0;
int selection = 1;  // 1(m/s) 2(ft/s)


void setup() {
  pinMode(sensorStartPin_1, INPUT_PULLUP);
  pinMode(sensorStartPin_2, INPUT_PULLUP);

  pinMode(sensorEndPin_1, INPUT_PULLUP);
  pinMode(sensorEndPin_2, INPUT_PULLUP);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not available"));
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(35, 0);
  display.setTextSize(2);
  display.print("Setup");

  display.setCursor(20,28);
  display.print("|");
  display.setCursor(30, 28);
  display.print("1. m/s");
  
  display.setCursor(30, 50);
  display.print("2. ft/s");
  display.display();
  
  mainMenu();

}

void loop() {

 if(digitalRead(sensorStartPin_1) != HIGH || digitalRead(sensorStartPin_2) != HIGH){
   startTime = micros();
   started = true;
  
   while(digitalRead(sensorEndPin_1) == HIGH && digitalRead(sensorEndPin_2) == HIGH){//do nothing};
   endTime = micros();
   finished = true;
  
  }
  
  if (started && finished) {

    unsigned long elapsedTime = endTime - startTime;
    float elapsedSeconds = elapsedTime / 1000000.0;
    
    switch(selection){
      case 1:{
          float velocita_m_s = (distance_cm/100) / elapsedSeconds;

          display.clearDisplay();
          display.setTextSize(2);
          display.setCursor(30,0);
          display.print("Values");
          display.setTextSize(1);
          display.setCursor(20,30);
          display.print("Time: ");
          display.print(elapsedSeconds, 4);
          display.println(" s");
          display.setCursor(20,45);
          display.print("Speed: ");
          display.print(velocita_m_s, 4);
          display.println(" m/s");
          display.display();
          break;
      }

      case 2:{
          float velocita_ft_s = ((distance_cm/100)*3.281) / elapsedSeconds;

          display.clearDisplay();
          display.setTextSize(2);
          display.setCursor(30,0);
          display.print("Values");
          display.setTextSize(1);
          display.setCursor(15,30);
          display.print("Time: ");
          display.print(elapsedSeconds, 4);
          display.println(" s");
          display.setCursor(15,45);
          display.print("Speed: ");
          display.print(velocita_ft_s, 4);
          display.println(" ft/s");
          display.display();
          break;
      }
       
    }

    tone(buzzerPin, 2000, 200);  // Beep
    delay(200);

    // Reset
    started = false;
    finished = false;
    
    }
 
  }

  if(digitalRead(buttonPin) == HIGH){
    select = false;
    selection = 1;
    mainMenu();
    }
}


void mainMenu(){
   while(select != true){
    if(digitalRead(buttonPin) == HIGH){
    startTime = millis();
    while(digitalRead(buttonPin) == HIGH){}
    endTime = millis();

    if((endTime - startTime) >= 1000){
      select = true; 
     }
     else{
      if(selection == 1){
          display.clearDisplay();
          display.setTextColor(SSD1306_WHITE);
          
          display.setCursor(35, 0);
          display.setTextSize(2);
          display.print("Setup");
          
          display.setCursor(30,28);
          display.print("1. m/s");
          
          display.setCursor(20,50);
          display.print("|");
          display.setCursor(30, 50);
          display.print("2. ft/s");
          display.display();

          selection = 2;
          }

        else if(selection == 2)
        {
          display.clearDisplay();
          display.setTextColor(SSD1306_WHITE);
          
          display.setCursor(35, 0);
          display.setTextSize(2);
          display.print("Setup");

          display.setCursor(20,28);
          display.print("|");
          display.setCursor(30,28);
          display.print("1. m/s");
          
          display.setCursor(30, 50);
          display.print("2. ft/s");
          display.display();

          selection = 1;
        } 
    }
   }
 }


  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,30);
  display.setTextSize(2);
  display.print("Completed!");
  display.display();

}

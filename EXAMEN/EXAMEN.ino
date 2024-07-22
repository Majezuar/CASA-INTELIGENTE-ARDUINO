#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

// GLOBAL VRAIABLE SWITCH
int option;

// DISTANCE SENSOR VARIABLES
int trigger = 10, echo = 9;
long time, distance;

// TEMPERATURE SENSOR VARIABLES
int sensorPin = A0;
float temperature, sensorValue, voltage;

// LDR SENSOR VARIABLES
int sensorPinLdr = A1, sensorValueLdr;

void setup()
{
  Serial.begin(9600);

  // LCD CONFIGURATION

  lcd.init();
  lcd.backlight();
  lcd.clear();

  // DISTANCE SENSOR CONFIGURATION

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  // LED QUEUE CONFIGURATION

  pinMode(11, OUTPUT); // First White LED
  pinMode(12, OUTPUT); // Second White LED

  pinMode(2, OUTPUT); // Blue LED

  pinMode(3, OUTPUT); // First Green LED
  pinMode(4, OUTPUT); // Second Green LED

  pinMode(5, OUTPUT); // First Yellow LED
  pinMode(6, OUTPUT); // Second Yellow LED

  pinMode(7, OUTPUT); // First Red LED
  pinMode(8, OUTPUT); // Second Red LED 
}



void loop()
{
  // ERASE
  lcd.clear();
  Serial.flush();

  // LCD OPTION MENU
  lcd.setCursor(0, 0);
  lcd.print("Choose:");

  lcd.setCursor(8, 0);
  lcd.print("1)Lights");

  lcd.setCursor(0, 1);
  lcd.print("2)W.level");

  lcd.setCursor(10, 1);
  lcd.print("3)Temp");

  Serial.println("Type your option (1-3): ");
  while (Serial.available() == 0)
  {
  }
  option = Serial.parseInt(); 

  switch (option)
  {
  case 1: // LIGHTS CASE
    int optionExit;
    do
    {
      Serial.flush();
      lcd.clear();

      Serial.println("Type (1) to exit.");

      lcd.setCursor(10, 1);
      lcd.print("1)Exit");
      String statusLights;

      while (Serial.available() == 0)
      {

        // MAIN CODE LDR
        sensorValueLdr = analogRead(sensorPinLdr);

        /*
          // OUTPUT ON SERIAL MONITOR

        Serial.println(sensorValueLdr);
        delay(1000);

        */

        if (sensorValueLdr <= 500)
        {
          digitalWrite(11, HIGH);
          digitalWrite(12, HIGH);
          lcd.setCursor(0, 0);
          statusLights = "Lights ON ";
        }
        else
        {

          digitalWrite(11, LOW);
          digitalWrite(12, LOW);
          lcd.setCursor(0, 0);
          statusLights = "Lights OFF";
        }

        lcd.print(statusLights);
      }

      digitalWrite(11, LOW);
      digitalWrite(12, LOW);

      optionExit = Serial.read() - 48;
      // Serial.print(optionExit);

    } while (optionExit != 1);

    break;

  case 2: // WATER LEVEL CASE
    int optionExit_2;
    do
    {
      Serial.flush();
      lcd.clear();

      Serial.println("Type (1) to exit.");

      lcd.setCursor(10, 1);
      lcd.print("1)Exit");
      String statusWater;

      while (Serial.available() == 0)
      {

        // MAIN CODE DISTANCE SENSOR

        // SHOOTING PULSE

        digitalWrite(trigger, LOW);
        delayMicroseconds(2);

        digitalWrite(trigger, HIGH);
        delayMicroseconds(10);

        digitalWrite(trigger, LOW);

        // HEARING PULSE

        time = pulseIn(echo, HIGH);
        distance = (time / 2) / 29; // CALCULATING DISTANCE IN CENTIMETERS

        if (distance < 100)
        {
          digitalWrite(2, HIGH);
          lcd.setCursor(0, 0);
          statusWater = "W. level: FULL ";
        }
        else
        {
          digitalWrite(2, LOW);
        }

        if (distance >= 100 && distance < 150)
        {
          digitalWrite(4, HIGH);
          digitalWrite(3, HIGH);
          lcd.setCursor(0, 0);
          statusWater = "W. level: 75 % ";
        }
        else
        {
          digitalWrite(4, LOW);
          digitalWrite(3, LOW);
        }

        if (distance >= 150 && distance < 250)
        {
          digitalWrite(6, HIGH);
          digitalWrite(5, HIGH);
          lcd.setCursor(0, 0);
          statusWater = "W. level: 50 % ";
        }
        else
        {
          digitalWrite(6, LOW);
          digitalWrite(5, LOW);
        }

        if (distance >= 250)
        {
          digitalWrite(8, HIGH);
          digitalWrite(7, HIGH);
          lcd.setCursor(0, 0);
          statusWater = "W. level: EMPTY  ";
        }
        else
        {
          digitalWrite(8, LOW);
          digitalWrite(7, LOW);
        }

        /*
            // OUTPUT ON SERIAL MONITOR
          Serial.print("Distance: ");
          Serial.print(distance);
          Serial.println(" cm");

          delay(1000);
          */
        lcd.print(statusWater);
      }

      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);

      optionExit_2 = Serial.read() - 48;
      // Serial.print(optionExit_2);

    } while (optionExit_2 != 1);

    break;

  case 3: // TEMPERATURE CASE
    int optionExit_3;
    do
    {
      Serial.flush();
      lcd.clear();

      Serial.println("Type (1) to exit.");

      lcd.setCursor(10, 1);
      lcd.print("1)Exit");

      while (Serial.available() == 0)
      {

        // MAIN CODE TMP36

        sensorValue = analogRead(sensorPin);   // Reading Sensor value
        temperature = (sensorValue - 105) / 2; // Converting voltage to celsius degrees

        /*
          // OUTPUT ON SERIAL MONITOR

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" degrees celsius");
        delay(1000);

        */

        if (temperature < 15.00)
        {
          digitalWrite(2, HIGH);
        }
        else
        {
          digitalWrite(2, LOW);
        }

        if (temperature >= 16.00 && temperature < 20.00)
        {
          digitalWrite(3, HIGH);
        }
        else
        {
          digitalWrite(3, LOW);
        }

        if (temperature >= 21.00 && temperature < 30.00)
        {
          digitalWrite(4, HIGH);
        }
        else
        {
          digitalWrite(4, LOW);
        }

        if (temperature >= 31.00 && temperature < 40.00)
        {
          digitalWrite(5, HIGH);
        }
        else
        {
          digitalWrite(5, LOW);
        }

        if (temperature >= 41.00 && temperature < 50.00)
        {
          digitalWrite(6, HIGH);
        }
        else
        {
          digitalWrite(6, LOW);
        }

        if (temperature >= 51.00 && temperature < 60.00)
        {
          digitalWrite(7, HIGH);
        }
        else
        {
          digitalWrite(7, LOW);
        }

        if (temperature >= 61.00)
        {
          digitalWrite(8, HIGH);
        }
        else
        {
          digitalWrite(8, LOW);
        }

        lcd.setCursor(0, 0);
        lcd.print("Temp: ");

        lcd.setCursor(6, 0);
        lcd.print(temperature);

        lcd.setCursor(12, 0);
        lcd.print(" D.C");
      }

      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);

      optionExit_3 = Serial.read() - 48;
      // Serial.print(optionExit_3);

    } while (optionExit_3 != 1);

    break;

  default: // DEFAULT CASE
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choose a valid");
    lcd.setCursor(0, 1);
    lcd.print("option, please");
    delay(2000);
    break;
  }
}

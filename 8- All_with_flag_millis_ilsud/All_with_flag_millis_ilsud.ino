#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int ir = 12;
const int buzzer = 13;
const int ldr = 14;
const int bulb = 27;
const int Switch = 19;
const int switch_LED = 23;
const int trig = 16;
const int echo = 17;
const int red = 18;
const int green = 5;
const int blue = 15;
const int dhtPin = 26;

int irState;
int ldrState;
int switchState;
long duration;
float distance = 400; // i put 400 to safe in start
//I made 2 flags to avoid intrupt with ultra sonic millis
bool irAlarm;
bool distanceAlarm;
float humidity;
float temperature;
unsigned long previousMillisDHT = 0;
const long dhtInterval = 2000;
unsigned long previousMillisUltrasonic = 0;
const long ultrasonicInterval = 100;

DHT dht(dhtPin, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  pinMode(ir, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(bulb, OUTPUT);
  pinMode(Switch, INPUT_PULLUP);
  pinMode(switch_LED, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  irState = digitalRead(ir);
  ldrState = digitalRead(ldr);
  switchState = digitalRead(Switch);

  irAlarm = false;

  if (switchState == LOW) {
    digitalWrite(switch_LED, LOW);
    if (irState == LOW) {
      irAlarm = true;
    }
    if (ldrState == HIGH) {
      digitalWrite(bulb, HIGH);
    } else {
      digitalWrite(bulb, LOW);
    }
  } else {
    digitalWrite(switch_LED, HIGH);
    digitalWrite(bulb, LOW);
  }
  if (currentMillis - previousMillisUltrasonic >= ultrasonicInterval) {
    previousMillisUltrasonic = currentMillis;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH, 30000);
    if (duration == 0) {
      distance = 400;
    } else {
      distance = (duration * 0.034) / 2;
    }

    if (distance <= 15) {
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      distanceAlarm = true;
    } else if (distance > 15 && distance <= 30) {
      digitalWrite(blue, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      distanceAlarm = false;
    } else {
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      distanceAlarm = false;
    }

    Serial.print("distance = ");
    Serial.print(distance);
    Serial.println(" Cm");
  }

  if (irAlarm || distanceAlarm) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

//I used millis to avoid wait latency for all code with delay
  if (currentMillis - previousMillisDHT >= dhtInterval) {
    previousMillisDHT = currentMillis;

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      lcd.setCursor(0, 0);
      lcd.print("sensor error!  ");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(temperature, 1);
      lcd.write(223);
      lcd.print("C   ");

      lcd.setCursor(0, 1);
      lcd.print("Humidity: ");
      lcd.print(humidity, 0);
      lcd.print("%   ");
    }
    Serial.print("Temp: ");
    Serial.print(temperature, 1);
    Serial.println("C   ");
    Serial.print("Humidity: ");
    Serial.print(humidity, 0);
    Serial.println("%   ");
  }  
}

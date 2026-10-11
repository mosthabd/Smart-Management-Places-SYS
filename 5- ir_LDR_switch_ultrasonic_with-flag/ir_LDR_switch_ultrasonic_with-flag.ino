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

int irState;
int ldrState;
int switchState;
long duration;
float distance;
bool buzzerAlarm;


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

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  irState = digitalRead(ir);
  ldrState = digitalRead(ldr);
  switchState = digitalRead(Switch);

  buzzerAlarm = false;

  if (switchState == LOW) {
    digitalWrite(switch_LED, LOW);
    if (irState == LOW) {
    buzzerAlarm = true;
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
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 30000);
  distance = (duration * 0.034) / 2;

  if (distance > 0 && distance <= 15) {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    buzzerAlarm = true;
  } else if (distance > 15 && distance <= 30) {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  } else if (distance > 30) {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
  } else {
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }

  if (buzzerAlarm){
    digitalWrite(buzzer, HIGH);
  }else{
    digitalWrite(buzzer, LOW);
  }

  Serial.print("distance = ");
  Serial.print(distance);
  Serial.println(" Cm");
  delay(100);
}

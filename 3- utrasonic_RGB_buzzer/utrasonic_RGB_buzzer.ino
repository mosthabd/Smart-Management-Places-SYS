const int trig = 16;
const int echo = 17;
const int red = 18;
const int green = 5;
const int blue = 15;

long duration;
float distance;


void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 30000);
  distance = (duration * 0.034) / 2;

  if (distance > 0 && distance <= 15) {
    digitalWrite(red, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  } else if (distance > 15 && distance <= 30) {
    digitalWrite(blue, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  } else if (distance > 30) {
    digitalWrite(green, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
  }else{
    digitalWrite(13, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }
  Serial.print("distance = ");
  Serial.print(distance);
  Serial.println(" Cm");
  delay(100);
}
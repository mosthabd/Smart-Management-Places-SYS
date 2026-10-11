const int ir = 12;
const int buzzer = 13;

int irState;


void setup() {
  // put your setup code here, to run once:
  pinMode(ir, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  irState = digitalRead(ir);

  if (irState == LOW) {
    digitalWrite(buzzer, HIGH);
  }else{
    digitalWrite(buzzer, LOW);
  }
}

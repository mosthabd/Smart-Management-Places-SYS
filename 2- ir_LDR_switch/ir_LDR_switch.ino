const int ir = 12;
const int buzzer = 13;
const int ldr = 14;
const int bulb = 27;
const int Switch = 19;
const int switch_LED = 23;

int irState;
int ldrState;
int switchState;


void setup() {
  // put your setup code here, to run once:
  pinMode(ir, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(bulb, OUTPUT);
  pinMode(Switch, INPUT_PULLUP);
  pinMode(switch_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  irState = digitalRead(ir);
  ldrState = digitalRead(ldr);
  switchState = digitalRead(Switch);

  if (switchState == LOW) {
    digitalWrite(switch_LED, LOW);
    if (irState == LOW) {
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }
    if (ldrState == HIGH) {
      digitalWrite(bulb, HIGH);
    } else {
      digitalWrite(bulb, LOW);
    }
  }else{
    digitalWrite(switch_LED, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(bulb, LOW);
  }
}

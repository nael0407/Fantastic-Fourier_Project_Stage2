#define LDR_PIN 4
#define LED_LAMP 19

#define TRIG_PIN 26
#define ECHO_PIN 25

#define PERSON_DISTANCE 50
#define LIGHT_THRESHOLD 2000

void setup() {
  Serial.begin(115200);

  pinMode(LDR_PIN, INPUT);
  pinMode(LED_LAMP, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("Nilai LDR: ");
  Serial.println(ldrValue);

  bool isDark = (ldrValue > LIGHT_THRESHOLD);

  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  bool personDetected = (distance <= PERSON_DISTANCE);

  if (personDetected) {
    digitalWrite(LED_LAMP, HIGH);
    Serial.println("Ada orang → LED ON");
  }
  else if (isDark) {
    digitalWrite(LED_LAMP, HIGH);
    Serial.println("Cahaya redup → LED ON");
  }
  else {
    digitalWrite(LED_LAMP, LOW);
    Serial.println("Cahaya terang → LED OFF");
  }

  Serial.println("---------------------------");
  delay(800);
}

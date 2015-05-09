Servo myServo;

int servoPin = D0;

void setup() {
  Spark.function("servo", servoControl);
  pinMode(servoPin, OUTPUT);
  digitalWrite(servoPin, LOW);
  myServo.attach(servoPin);
}

void loop() {

}

int servoControl(String angle) {
  int servoAngle = angle.toInt();
  if (servoAngle < 0 || servoAngle > 179) {
    return -42;
  }
  myServo.write(servoAngle);
  return 1;
}

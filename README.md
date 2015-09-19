#A proof of concept wifi controlled deadbolt lock using a Spark Core

### Supplies Needed
* Spark Core
* Servo Motor
* Breadboard or two
* Wires
* Capacitor (maybe)
* Deadbolt Lock
* Lots and lots of duct tape

### Instructions
I'm going to assume knowledge of basic circuits. I worked through 6 or 7 of the exercises in an Arduino starter kit before attempting to build this. 

Wire up the servo motor connecting the control to one of the GPIO pins of the core (I used D0). My motor recommended using a 5V power source, but the Spark Core only provides 3.3V and I didn't have a 3.3V to 5V converter handy, so I used an Arduino Uno as a 5V power source in my circuit. Depending on what motor is used, you might be able to power it directly from the 3.3V provided by the Core. Again, depending on your motor a capacitor might be required to smooth out the voltage across the heads of the servo motor.

![alt text](https://github.com/KarlParkinson/wifiLock/blob/master/circuit-overhead.jpg)

Tape the arms of the servo motor to the deadbolt. Make sure that the motor is oriented correctly so that it will turn the deadbolt when told to rotate.

![alt text](https://raw.githubusercontent.com/KarlParkinson/wifiLock/master/arms-tapped.jpg)

Almost done. Finally, we need to secure the servo motor to the lock itself. If this is not done, the motor will rotate instead of the arms. I had a screwdriver and an old allen key lying around and used these as well as some duct tape to hold the motor in place.

![alt text](https://github.com/KarlParkinson/wifiLock/blob/master/servo-secure.jpg)

Flash the servoControl.cpp firmware code to your Core.

```C++
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
```

Test it out using curl (or really anything that can make an http request). I found that setting the motor to 35 degrees to lock and 175 degress to unlock worked best. Your numbers may vary.

```
curl https://api.particle.io/v1/devices/{device_id}/servo -d access_token={access_token} -d params={angle}
```

<a href="https://www.youtube.com/watch?feature=player_embedded&v=_kh5756qUSU" target="_blank"><img src="http://img.youtube.com/vi/_kh5756qUSU/0.jpg" border="10" /></a>

That's it! For fun, extend this with a web or mobile frontend.

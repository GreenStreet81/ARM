#include <Servo.h>

Servo Arm;  
int pos = 157;    // variable to store the servo position
// defines pins numbers
const int trigPin = 10;
const int echoPin = 11;

// defines variables
long duration;
int distance;

void setup() {  
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  int d = movmentSensor(); 
//  Serial.print(d);
//  delay(1000);

  if (d > 1 && d < 20){
    MoveArm(Arm.read(), 5); //Open
    Serial.print(Arm.read());
    delay(1000);
  }
   if (d > 20 ) {
    MoveArm(Arm.read(), 157); //Close
    Serial.print(Arm.read());
  }                         
}

void MoveArm(int current, int target){
    if (current > target && current != target) 
      {
          Arm.attach(9);
          for (int p = current; p >= target; p -= 1) { // goes from 0 degrees to 180 degrees
          Arm.write(p);              // tell servo to go to position in variable 'pos'
          delay(2);                       // waits 15ms for the servo to reach the position;
          }
          target = 157;
          current = Arm.read();
          Serial.print("Waiting  ");
          Serial.print(current);
          Serial.print("  -->  ");
          Serial.print(target);
          delay(2000);
    }  
    if (current < target && current != target){
          for (int p = current; p <= target; p += 1) { // goes from 0 degrees to 180 degrees
          Arm.write(p);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position;
//          int d = movmentSensor(); 
//          if (d < 20) {p = target;}
          }
          Arm.attach(3);
    }
}

int movmentSensor(){
      // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    return distance;
}


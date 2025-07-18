#include <Keypad.h> //install library and access keypad using header file
#include <Servo.h> // header file to control servo motot
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myservo;
int buzzerPin = 13;
int numAttempts = 0;
const int trigPin = 11;
const int echoPin = 12;
const int maxAttempts = 3; // maximum number of attempts before alarm is
activated
const String masterPassword = "9876"; // master password to stop the buzzer
String password = "1234"; // change this to your desired password
String enteredPassword = "";
int pos = 90; // current position of the servo motor
int unlockPos =0; // position to unlock the locker
int lockPos = 90; // position to lock the locker
bool locked = true;
int distance = 0;
bool buzzerOn = false;
void setup() {
Serial.begin(9600);
myservo.attach(10);
myservo.write(lockPos); // start with the locker locked
pinMode(buzzerPin, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
myservo.write(lockPos); // turn the servo to unlock position when power is
applied
// return the servo to lock position
}
void buzz() {
digitalWrite(buzzerPin, HIGH);
buzzerOn = true;
}
void buzz(int duration) {
digitalWrite(buzzerPin, HIGH);
delay(duration);
digitalWrite(buzzerPin, LOW);
buzzerOn = false;
}
void stopbuzz() {
digitalWrite(buzzerPin, LOW);
buzzerOn = false;
}
void loop() {
char key = keypad.getKey();
if (key != NO_KEY) {
if (key == '*' || key == '#') {
if (enteredPassword == password && distance > 0 && distance < 30) {
myservo.write(unlockPos);
enteredPassword = "";
locked = false;
Serial.println("Locker unlocked");
buzz(500);
pos = unlockPos; // set the current position of the servo to the
unlocked position
locked = false;
Serial.println("Locker unlocked");
numAttempts = 0;
} else if (!locked) {
myservo.write(lockPos);
locked = true;
pos = lockPos; // set the current position of the servo to the locked
position
Serial.println("Locker locked");
buzz(500);
} else {
enteredPassword = "";
numAttempts++;
Serial.println("Incorrect password");
if (numAttempts == maxAttempts) {
buzz();
numAttempts = 0;
}
}
} else if (enteredPassword.length() < 4) {
enteredPassword += key;
}
}
if (key == 'B' && buzzerOn) {
stopbuzz();
}
if (enteredPassword == masterPassword) {
stopbuzz();
enteredPassword = "";
Serial.println("Buzzer stopped by master password");
}
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
distance = pulseIn(echoPin, HIGH) / 58;
}
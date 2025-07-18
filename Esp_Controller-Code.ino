#include <ESP8266WiFi.h> //library for esp wifi header file
#include <WiFiClient.h> //library to establish connection
#include <ESP8266WebServer.h> //library for creating webserver
#include <Servo.h>
// WiFi credentials
const char* ssid = "vivo 1819";
const char* password = "1234567890";
// Web server username and password
const char* httpUsername = "Naruto";
const char* httpPassword = "1234";
// Initialize the web server
ESP8266WebServer server(80);
// Initialize the servo object
Servo myservo;
int unlockPos = 90; // position to unlock the locker
int lockPos = 0; // position to lock the locker
bool locked = true;
// Initialize the buzzer pin
int buzzerPin = 13;
void setup() {
// Start serial communication
Serial.begin(9600);
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi...");
}
Serial.println("Connected to WiFi");
// Print the IP address
Serial.print("Server IP address: ");
Serial.println(WiFi.localIP());
// Start the web server
server.begin();
// Map the web server routes
server.on("/", handleRoot);
server.on("/open", handleOpen);
server.on("/close", handleClose);
server.on("/alarm/on", handleAlarmOn);
server.on("/alarm/off", handleAlarmOff);
// Attach the servo
myservo.attach(D4);
myservo.write(lockPos); // start with the locker locked
pinMode(buzzerPin, OUTPUT);
}
void loop() {
server.handleClient();
}
void handleRoot() {
// Check for authentication
if (!isAuthenticated()) {
requestAuthentication();
return;
}
String html = R"html(
<!DOCTYPE html>
<html>
<head>
<style>
body {
text-align: center;
background-color: #f2f2f2;
}
h1 {
background-color: orange;
padding: 10px;
color: white;
font-family: Arial, sans-serif;
}
button {
padding: 10px 20px;
font-size: 16px;
background-color: #4CAF50;
color: white;
border: none;
cursor: pointer;
margin: 5px;
}
button:hover {
background-color: #45a049;
}
</style>
</head>
<body>
<h1>Locker Control</h1>
<p>Click the buttons below to control the locker:</p>
<button onclick="location.href='/open'">Open Locker</button>
<button onclick="location.href='/close'">Close Locker</button>
<br/><br/>
<p>Alarm:</p>
<button onclick="location.href='/alarm/on'">Turn On</button>
<button onclick="location.href='/alarm/off'">Turn Off</button>
</body>
</html>
)html";
server.send(200, "text/html", html);
}
void handleOpen() {
// Check for authentication
if (!isAuthenticated()) {
requestAuthentication();
return;
}
if (!locked) {
server.send(200, "text/plain", "Locker is already open");
} else {
myservo.write(unlockPos);
locked = false;
digitalWrite(buzzerPin, HIGH); // Buzz the buzzer
delay(500);
digitalWrite(buzzerPin, LOW);
server.send(200, "text/plain", "Locker opened");
}
}
void handleClose() {
// Check for authentication
if (!isAuthenticated()) {
requestAuthentication();
return;
}
if (locked) {
server.send(200, "text/plain", "Locker is already closed");
} else {
myservo.write(lockPos);
locked = true;
digitalWrite(buzzerPin, HIGH); // Buzz the buzzer
delay(500);
digitalWrite(buzzerPin, LOW);
server.send(200, "text/plain", "Locker closed");
}
}
void handleAlarmOn() {
// Check for authentication
if (!isAuthenticated()) {
requestAuthentication();
return;
}
digitalWrite(buzzerPin, HIGH);
server.send(200, "text/plain", "Alarm turned on");
}
void handleAlarmOff() {
// Check for authentication
if (!isAuthenticated()) {
requestAuthentication();
return;
}
digitalWrite(buzzerPin, LOW);
server.send(200, "text/plain", "Alarm turned off");
}
bool isAuthenticated() {
// Check if the client provided the correct username and password
return server.authenticate(httpUsername, httpPassword);
}
void requestAuthentication() {
// Request authentication from the client
server.requestAuthentication();
}
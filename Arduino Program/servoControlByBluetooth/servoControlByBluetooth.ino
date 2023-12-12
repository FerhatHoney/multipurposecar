#include <ESP32Servo.h>
#include <BluetoothSerial.h>

Servo myServo;  // Create a Servo object to control the servo motor
BluetoothSerial SerialBT;  // Create an object for Bluetooth communication

int servoPin = 9;  // Signal pin of the servo motor
int angle = 90;    // Initial angle of the servo motor

void setup() {
  Serial.begin(115200);  // Start serial communication
  SerialBT.begin("ESP32_BT");  // Start Bluetooth connection, specify the device name as ESP32_BT
  myServo.attach(servoPin);  // Attach the servo motor
  myServo.write(angle);  // Set the servo motor to the initial angle
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();  // Read the incoming command
    
    // Control the servo motor based on the incoming command
    if (command == 'L') {
      angle -= 10;
      if (angle < 0) angle = 0;
    } else if (command == 'R') {
      angle += 10;
      if (angle > 180) angle = 180;
    }
    
    // Set the servo motor to the specified angle
    myServo.write(angle);
    
    // Print the angle to the serial monitor
    Serial.print("Angle: ");
    Serial.println(angle);
  }
  delay(50);
}

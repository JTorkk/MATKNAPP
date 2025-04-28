// Include libraries for Bluetooth communication and stepper motor control
#include <SoftwareSerial.h>
#include <AccelStepper.h>

// Setup Bluetooth communication using pins 10 (RX - receive) and 11 (TX - transmit)
SoftwareSerial BT(10, 11);

// Define pins for controlling the stepper motor
const int dirPin = 2;  // Direction pin
const int stepPin = 3; // Step pin

// Define the type of motor interface (1 indicates a simple step/dir driver)
#define motorInterfaceType 1

// Create a stepper motor object using the defined pins and motor interface
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

// Define the number of steps the motor should move upon receiving a button press
const int stepAmount = 1200;

// The setup function runs once when Arduino is powered on or reset
void setup()
{
    // Initialize serial communication with the computer
    Serial.begin(9600);

    // Initialize Bluetooth communication
    BT.begin(9600);

    // Configure stepper motor parameters
    myStepper.setMaxSpeed(2000);     // Maximum speed (steps per second)
    myStepper.setAcceleration(1000); // Acceleration (steps per second squared)
    myStepper.setSpeed(1500);        // Current speed setting

    // Indicate setup completion
    Serial.println("Dispenser ready.");
}

// The loop function runs continuously
void loop()
{
    // Continuously move stepper motor if a movement is queued
    if (myStepper.distanceToGo() != 0)
    {
        myStepper.run();
    }

    // Check if a Bluetooth message has been received
    if (BT.available())
    {
        // Read the received message until a newline character
        String msg = BT.readStringUntil('\n');
        msg.trim(); // Remove any whitespace or newline characters

        // Display the received message on serial monitor
        Serial.print("Received: ");
        Serial.println(msg);

        // If the received message indicates the button was pressed
        if (msg == "BTN_PRESSED")
        {
            Serial.print("Moving stepper ");
            Serial.print(stepAmount);
            Serial.println(" steps...");
            // Command the stepper motor to move stepAmount steps from current position
            myStepper.moveTo(myStepper.currentPosition() + stepAmount);
        }
    }
}

// Include the SoftwareSerial library, which allows communication with other devices
#include <SoftwareSerial.h>

// Initialize Bluetooth serial communication on pins 10 (RX - receive) and 11 (TX - transmit)
SoftwareSerial BT(10, 11);

// Define the pin number connected to the button
const int buttonPin = 7;

// Variable to store the previous state of the button (pressed or not pressed)
bool lastState = HIGH;

// Setup function runs once when the Arduino is powered on or reset
void setup()
{
    // Set buttonPin as input and use Arduino's internal pull-up resistor
    pinMode(buttonPin, INPUT_PULLUP);

    // Begin serial communication with the computer at a baud rate of 9600
    Serial.begin(9600);

    // Begin Bluetooth communication at a baud rate of 9600
    BT.begin(9600);

    // Print a message indicating the Arduino is ready
    Serial.println("Slave ready.");
}

// Loop function runs continuously after setup()
void loop()
{
    // Read the current state of the button (pressed or not pressed)
    bool currentState = digitalRead(buttonPin);

    // Check if the button was just pressed (state changes from not pressed to pressed)
    if (lastState == HIGH && currentState == LOW)
    {
        // Inform via serial monitor that the button has been pressed
        Serial.println("Button pressed!");

        // Send a message over Bluetooth indicating the button was pressed
        BT.println("BTN_PRESSED");

        // Short delay to avoid bouncing effect (prevents accidental multiple detections)
        delay(200);
    }

    // Update the button state for next loop iteration
    lastState = currentState;
}

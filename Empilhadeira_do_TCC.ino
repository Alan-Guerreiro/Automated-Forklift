#include <Wire.h>
#include <Servo.h>

// ======================================================
// PINS
// ======================================================

// Drive Motor
const byte DRIVE_IN1 = 1;
const byte DRIVE_IN2 = 2;

// Lift Motor
const byte LIFT_IN1 = 4;
const byte LIFT_IN2 = 5;

// Limit Switch
const byte LIMIT_TOP = 6;
const byte LIMIT_BOTTOM = 7;

// Servo
const byte SERVO_PIN = 9;

// ======================================================
// BLUETOOTH COMMANDS
// ======================================================

const char CMD_FORWARD      = 'F';
const char CMD_BACKWARD     = 'B';
const char CMD_STOP_DRIVE   = 'X';

const char CMD_LIFT_UP      = 'U';
const char CMD_LIFT_DOWN    = 'D';
const char CMD_STOP_LIFT    = 'Y';

const char CMD_SERVO_RIGHT  = 'R';
const char CMD_SERVO_LEFT   = 'L';

const char CMD_SERVO_STOP_RIGHT = 'r';
const char CMD_SERVO_STOP_LEFT  = 'l';

// ======================================================
// SERVO
// ======================================================

Servo steeringServo;

int servoPosition = 90;

bool moveRight = false;
bool moveLeft  = false;

unsigned long previousServoTime = 0;
const byte SERVO_SPEED = 15;

// ======================================================
// LIFT CONTROL
// ======================================================

enum LiftState
{
    LIFT_STOPPED,
    LIFT_MOVING_UP,
    LIFT_MOVING_DOWN
};

LiftState liftState = LIFT_STOPPED;

// ======================================================
// DRIVE MOTOR
// ======================================================

void driveForward()
{
    digitalWrite(DRIVE_IN1, LOW);
    digitalWrite(DRIVE_IN2, HIGH);
}

void driveBackward()
{
    digitalWrite(DRIVE_IN1, HIGH);
    digitalWrite(DRIVE_IN2, LOW);
}

void stopDrive()
{
    digitalWrite(DRIVE_IN1, LOW);
    digitalWrite(DRIVE_IN2, LOW);
}

// ======================================================
// LIFT MOTOR
// ======================================================

void liftUp()
{
    digitalWrite(LIFT_IN1, HIGH);
    digitalWrite(LIFT_IN2, LOW);
}

void liftDown()
{
    digitalWrite(LIFT_IN1, LOW);
    digitalWrite(LIFT_IN2, HIGH);
}

void stopLift()
{
    digitalWrite(LIFT_IN1, LOW);
    digitalWrite(LIFT_IN2, LOW);
}

// ======================================================
// LIMIT SWITCHES
// ======================================================

bool topLimitPressed()
{
    return digitalRead(LIMIT_TOP) == LOW;
}

bool bottomLimitPressed()
{
    return digitalRead(LIMIT_BOTTOM) == LOW;
}

// ======================================================
// SETUP
// ======================================================

void setup()
{
    pinMode(DRIVE_IN1, OUTPUT);
    pinMode(DRIVE_IN2, OUTPUT);

    pinMode(LIFT_IN1, OUTPUT);
    pinMode(LIFT_IN2, OUTPUT);

    pinMode(LIMIT_TOP, INPUT_PULLUP);
    pinMode(LIMIT_BOTTOM, INPUT_PULLUP);

    stopDrive();
    stopLift();

    Wire.begin();
    Serial.begin(9600);

    steeringServo.attach(SERVO_PIN);
    steeringServo.write(servoPosition);
}

// ======================================================
// COMMAND PROCESSING
// ======================================================

void processCommand(char command)
{
    switch (command)
    {
        case CMD_FORWARD:
            driveForward();
            break;

        case CMD_BACKWARD:
            driveBackward();
            break;

        case CMD_STOP_DRIVE:
            stopDrive();
            break;

        case CMD_LIFT_UP:
            liftState = LIFT_MOVING_UP;
            break;

        case CMD_LIFT_DOWN:
            liftState = LIFT_MOVING_DOWN;
            break;

        case CMD_STOP_LIFT:
            liftState = LIFT_STOPPED;
            break;

        case CMD_SERVO_RIGHT:
            moveRight = true;
            moveLeft = false;
            break;

        case CMD_SERVO_STOP_RIGHT:
            moveRight = false;
            break;

        case CMD_SERVO_LEFT:
            moveLeft = true;
            moveRight = false;
            break;

        case CMD_SERVO_STOP_LEFT:
            moveLeft = false;
            break;
    }
}

// ======================================================
// SERVO CONTROL
// ======================================================

void updateServo()
{
    if (millis() - previousServoTime < SERVO_SPEED)
        return;

    previousServoTime = millis();

    if (moveRight && servoPosition < 180)
    {
        servoPosition++;
        steeringServo.write(servoPosition);
    }

    else if (moveLeft && servoPosition > 0)
    {
        servoPosition--;
        steeringServo.write(servoPosition);
    }
}

// ======================================================
// LIFT CONTROL
// ======================================================

void updateLift()
{
    switch (liftState)
    {
        case LIFT_MOVING_UP:

            if (topLimitPressed())
            {
                stopLift();
                liftState = LIFT_STOPPED;
            }
            else
            {
                liftUp();
            }

            break;

        case LIFT_MOVING_DOWN:

            if (bottomLimitPressed())
            {
                stopLift();
                liftState = LIFT_STOPPED;
            }
            else
            {
                liftDown();
            }

            break;

        case LIFT_STOPPED:

            stopLift();
            break;
    }
}

// ======================================================
// LOOP
// ======================================================

void loop()
{
    while (Serial.available())
    {
        processCommand(Serial.read());
    }

    updateServo();
    updateLift();
}
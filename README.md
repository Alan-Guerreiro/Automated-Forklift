# Automated-Forklift

Arduino-based electric forklift prototype developed as a Technical Course Final Project (TCC) in Mechatronics at ETEC Lauro Gomes.

## Overview

This project presents the development of a small-scale electric forklift prototype designed to simulate material handling operations in industrial environments.

The main objective was to apply mechanical, electrical, and programming concepts acquired throughout the Mechatronics course by building a remotely controlled forklift capable of moving, steering, and lifting loads.

The forklift is controlled wirelessly through a Bluetooth mobile application, allowing real-time operation of the driving system and lifting mechanism.

## Features

- Bluetooth remote control (HC-05)
- Forward and reverse movement
- Left and right steering using a servo motor
- Fork lifting and lowering system
- DC motor drive with dual relay module
- Upper limit safety switch
- 12V battery powered
- Arduino Mega control system
- Mobile application interface
- Electrical protection through voltage regulation

## Hardware Components

- Arduino Mega 2560
- HC-05 Bluetooth Module
- DC Motors
- Servo Motor
- Dual Relay Module
- Limit Switch
- 12V Motorcycle Battery
- Voltage Regulator Module
- Mechanical Forklift Chassis

## Software

- Arduino IDE
- C/C++
- Arduino Bluetooth Control

## How It Works

1. The user connects a smartphone to the HC-05 Bluetooth module.
2. Control commands are sent from the mobile application.
3. The Arduino Mega receives and interprets each command.
4. The relay module controls the drive and lifting motors.
5. The servo motor controls the steering system.
6. The limit switch prevents the forks from exceeding the maximum lifting height.

## Project Objectives

- Design a functional electric forklift prototype.
- Apply concepts of embedded systems and automation.
- Improve material handling efficiency through automation.
- Demonstrate wireless control using Bluetooth communication.
- Increase operational safety using electronic protection systems.

## Applications

This prototype demonstrates concepts commonly found in:

- Industrial Automation
- Material Handling Systems
- Smart Logistics
- Industry 4.0
- Educational Robotics
- Embedded Systems

## Author

Alan Brito Guerreiro

Developed as the Final Course Project (TCC) for the Mechatronics Technical Program at **ETEC Lauro Gomes**.

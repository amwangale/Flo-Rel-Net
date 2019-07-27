# Flo-Rel-Net
Flood Relay Network

# What is this?

A radio relay network to collect and transmit weather data.


# Why are we doing this?

Each year people are displaced by flood waters. This project aims to analyze a real-time data feed to help enable flood prevention and preparedness efforts.

# How to run

Currently there are three programs:

 - A Python simulator that demonstrates the software pipeline from collecting data to transmitting it

 - Two C program which actually run on the device, but will not work without the necessary hardware

## Requirements

 - A Linux operating system, but MacOS should work just as well
 - git
 - (OPTIONAL) Hardware listed below

### Python

  - Python3.*

### C

 - Make
 - gcc
 - sx1278
   - [pigpio](https://github.com/scollet1/sx1278-LoRa-RaspberryPi)
   - [sx1278-LoRa-RaspberryPi](https://github.com/joan2937/pigpio)
 - [sx1272](https://www.cooking-hacks.com/documentation/tutorials/extreme-range-lora-sx1272-module-shield-arduino-raspberry-pi-intel-galileo/)
   - sx1272 library
   - ArduPi library

## How to run

Navigate to your home directory or whichever location you would like to install the program

`git clone https://github.com/scollet1/Flo-Rel-Net.git`

`cd Flo-Rel-Net`

### Python

`cd FloRelPy`

This will run a test program by default.

`./run`

You can edit the file to change the arguments or simply run it from the command line like so:

`python3 main.py` <ID>

### C

`./config`

This will make a test program by default.

`./install`

This will run a test program by default.

`./run`

You can edit the file to change the arguments or simply run it from the command line like so:

`./FloRel` <ID>

## Architecture

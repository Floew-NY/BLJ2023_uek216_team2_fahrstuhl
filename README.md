# BLJ2023 IC216 Team2 Elevator

## Development

This project uses PlatformIO for development. To install PlatformIO, follow the instructions [here](https://platformio.org/install/ide?install=vscode).
After installing PlatformIO, open the project folder in VSCode and you are good to go.

## Code Structure

The code has been divided into different parts which are responsible for different tasks.
'integration.cpp', 'interface.cpp', 'main.cpp', 'mqtt.cpp', 'prefs.cpp', 'wiconn.cpp',

### integration.cpp

This file contains the main setup and loop function for the elevator integration module.

### interface.cpp

This file contains the functions for the user interface module.

### main.cpp

This file contains boilerplate code for both modules.

### mqtt.cpp

All the functions related to MQTT are in this file.

### prefs.cpp

It contains the functions for saving, loading and deleting preferences.

### wiconn.cpp

In this file, the library WiFiManager is used to connect to the WiFi network and set the custom parameters.

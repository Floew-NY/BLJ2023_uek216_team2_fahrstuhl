// switch between the integration module and the user interface module
// by commenting out the line below. only one of the two modules can be active at a time.
#define INTEGRATION
// #define INTERFACE

// only aplies if confugring the integration module, automatically always calls the elevator when its not there.
#define INTEGRATION_AUTOMATIC_MODE false

// Leave the following lines unchanged
#define SERIAL_BAUD_RATE 115200
#define CONFIG_BUTTON_PIN 0

// pin definitions for the user interface module (GPIO required)
#define CALL_BUTTON_PIN 15
#define LIGHT_RED_PIN 16
#define LIGHT_GREEN_PIN 17
#define LIGHT_BLUE_PIN 18

// pin definitions for the elevator integration module
#define LIGHT_SENSOR_PIN 35 // ADC1 pin required
#define SERVO_PIN 32        // PWM pin required

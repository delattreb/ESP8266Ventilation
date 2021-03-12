//DEBUG INFORMATION
//#define SERIALLOG
//#define INFO
//#define DEBUG
//#define WIFIDEBUG

// Serial configuration
#define SERIALBAUDS 115200
//Device name
#define DEVICE_NAME "Ventilation1"

//ESP8266 configuration
#define NETWORKNAME "ESPVentilation"
#define ATTENPTING 1000
// GPIO
#define GPIO_0 0
#define GPIO_1 2

//Save Data
#pragma region SAVE_DATA
#define EEPROM_SIZE 1
#define EEPROM_PLACE_BRIGHT 0
#pragma endregion 

#pragma region IPDEFINITION
// IP Start
#define IPLOWA 10
#define IPLOWB 0
#define IPLOWC 0
#define IPLOWD 1

// IP End
#define IPHIGHA 10
#define IPHIGHB 0
#define IPHIGHC 0
#define IPHIGHD 1
#pragma endregion
//URL
//http://IP/espalexa
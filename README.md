# esp8266-homekit-contactsensor
This is a native HomeKit contact sensor with D1 mini ESP8266.

## Hardware
The following hardware is required:
```
- D1 mini (ESP8266)
- Resistor 10kOhm
- Wired Contact Sensor (like ABUS 2040038)
```

## Connection:

D1 mini -> NC Contact Sensor (Pin A, Pin B)
```
3V3 -> 10kOhm -> Contact sensor Pin A
D1 -> Contact sensor Pin A
GND -> Contact sensor Pin B
```

D1 mini -> NO Contact Sensor (Pin A, Pin B)
```
GND -> 10kOhm -> Contact sensor Pin A
D1 -> Contact sensor Pin A
3V3 -> Contact sensor Pin B
```

## Development
This sketch is for following development environment
```
Arduino
```

Following libraries are required
```
https://github.com/datjan/Arduino-HomeKit-ESP8266 (fork from Mixiaoxiao/Arduino-HomeKit-ESP8266:master)
```

## Setup
Setup my_accessory.c:
```
.password = "555-11-123"  // Homekit Code
```

Setup wifi_info.h
```
const char *ssid = "xxx"; // SETUP Wlan ssid
const char *password = "xxx"; // SETUP Wlan password
```

## Upload to device
Following files needs to be uploaded to the ESP8266 (D1 mini)
```
esp8266-homekit-contactsensor.ino
my_accessory.c
wifi_info.h
```

## Add device to Homekit
The device can be added to homekit like every other homekit device.

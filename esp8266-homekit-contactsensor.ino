
/*  WEMOS D1 Mini
                     ______________________________
                    |   L T L T L T L T L T L T    |
                    |                              |
                 RST|                             1|TX HSer
                  A0|                             3|RX HSer
                  D0|16                           5|D1
                  D5|14                           4|D2
                  D6|12                    10kPUP_0|D3
RX SSer/HSer swap D7|13                LED_10kPUP_2|D4
TX SSer/HSer swap D8|15                            |GND
                 3V3|__                            |5V
                       |                           |
                       |___________________________|

// connection schema for NORMALY CLOSED contact sensors
D1 mini -> Button (Pin A, Pin B)
3V3 -> 10kOhm -> Button Pin A
D1 -> Button Pin A
GND -> Button Pin B

// connection schema for NORMALY OPEN contact sensors
D1 mini -> Button (Pin A, Pin B)
GND -> 10kOhm -> Button Pin A
D1 -> Button Pin A
3V3 -> Button Pin B


*/


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

int pinContactSensor = D1;

void setup() {
  Serial.begin(115200);
  wifi_connect(); // in wifi_info.h
  //homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example

  pinMode(pinContactSensor, INPUT);
  
  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_contact;

#define HOMEKIT_CONTACT_SENSOR_DETECTED       0
#define HOMEKIT_CONTACT_SENSOR_NOT_DETECTED   1


// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch_event_getter() {
  // Should always return "null" for reading, see HAP section 9.75
  return HOMEKIT_NULL_CPP();
}

void my_homekit_setup() {
  arduino_homekit_setup(&config);
}

static uint32_t next_heap_millis = 0;
static uint32_t next_report_millis = 0;

void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_report_millis) {
    // report sensor values every 10 seconds
    next_report_millis = t + 10 * 1000;
    my_homekit_report();
  }
  if (t > next_heap_millis) {
    // Show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
        ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

  }
}

void my_homekit_report() {
  // FIXME, read your real sensors here.

  // Default - Open - Contact Not Detected
  cha_contact.value.uint8_value = 1;
  
  if (digitalRead(pinContactSensor) == LOW)
    {
      // Closed - Contact Detected
      cha_contact.value.uint8_value = 0;
    }

  homekit_characteristic_notify(&cha_contact, cha_contact.value);


  //LOG_D("t %.1f, h %.1f, l %.1f, c %u, m %u, o %u", t, h, l, c, (uint8_t)m, o);
}

int random_value(int min, int max) {
  return min + random(max - min);
}

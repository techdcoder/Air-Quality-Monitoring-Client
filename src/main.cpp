#include <Arduino.h>

#include "wifi.hpp"
#include <LiquidCrystal_I2C.h>
#include "sensors.hpp"
#include "storage.hpp"
#include "ui.hpp"

LiquidCrystal_I2C lcd(0x27,20,4);

char wifi_name[64];
char wifi_password[64];
int server_port;
IP_Address server_ip;

void retrieve_data(){
  retrieve_wifi_name(wifi_name);
  retrieve_wifi_password(wifi_password);
  server_ip = retrieve_server_ip();
  server_port = retrieve_server_port();
}

void setup(){
  Serial.begin(115200);

  initialize_sensors();

  retrieve_data();
  Wifi::initialize();

  print_ui(3000);
}

void loop() {
  if(!Wifi::connected()){
    print_ui(3000);
    Serial.println("Connecting to Wifi");
    Wifi::connect(wifi_name,wifi_password);
    return; 
  }

  if(!Wifi::connected_server()){
    print_ui(3000);
    Serial.println("Connecting to Server");
    Wifi::connect_server(server_ip.get_str(),server_port);
    return;
  }

  SensorData data = get_sensor_data();

  if(data.pms_read){
    const char* csv = data.csv();
    Wifi::send_data(csv);
    Serial.println(csv);
  }   

  delay(200);
}

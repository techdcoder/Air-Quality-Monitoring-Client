#include "wifi.hpp"

#include <Arduino.h>
#include <WiFiEsp.h>
#include <SoftwareSerial.h>

namespace Wifi{
  SoftwareSerial esp_serial(5,6);
  WiFiEspClient wifi_client;
  
  bool connecting_to_wifi = false; 

  void initialize(){
      esp_serial.begin(9600);
      WiFi.init(&esp_serial);
  }

  void connect(const char* ssid, const char* password){
    if(!connecting_to_wifi){
      WiFi.begin(ssid, password);
      connecting_to_wifi = true;
    }
    
    if(WiFi.status() == WL_CONNECTED){
      Serial.println("Connected to WiFi");
      connecting_to_wifi = false;
    }
  }

  void connect_server(const char* ip_addr, int port){
    if(wifi_client.connect(ip_addr,port)){
      Serial.println("Conected to Server");
    }
  }

  bool connected_server(){
      return wifi_client.connected();
  }

  bool connected(){
    return (WiFi.status() == WL_CONNECTED);
  }

  void send_data(const char* data){
    wifi_client.write(data);
    wifi_client.flush();
  }
}


IP_Address::IP_Address() {}

IP_Address::IP_Address(const byte b1_, const byte b2_, const byte b3_, const byte b4_) : 
b1(b1_),
b2(b2_),
b3(b3_),
b4(b4_) 
{
  sprintf(ip_str,"%d.%d.%d.%d",b1,b2,b3,b4);
} 

IP_Address::IP_Address(const char* ip_str_) {
  memset(ip_str, 0, sizeof(ip_str));
  memcpy(ip_str,ip_str_,sizeof(char)*strlen(ip_str_));

  const char* ptr = strtok(ip_str, ".");
  b1 = atoi(ptr);
    
  strtok(NULL, ".");
  b2 = atoi(ptr);
    
  ptr = strtok(NULL, ".");
  b3 = atoi(ptr);
    
  ptr = strtok(NULL, ".");
  b4 = atoi(ptr);
}

const char* IP_Address::get_str(){
  return ip_str; 
} 


void IP_Address::get_bytes(byte* b1_, byte* b2_, byte* b3_, byte* b4_){
  *b1_ = b1; 
  *b2_ = b2;
  *b3_ = b3;
  *b4_ = b4;
}
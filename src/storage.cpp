#include "storage.hpp"
#include <Arduino.h>
#include <EEPROM.h>

// LAYOUT 
// 0 - 3 => Server IP Address 
// 4 - 5 => Server Port 
// 6 => WiFi Name Length 
// 7 - 56 => WiFi Name 
// 57 => Password Length
// 58 - 107 => Password 
void store_server_ip(IP_Address ip){
    byte b1,b2,b3,b4;
    ip.get_bytes(&b1,&b2,&b3,&b4);

    EEPROM.write(0,b1);
    EEPROM.write(1,b2);
    EEPROM.write(2,b3);
    EEPROM.write(3,b4);
}

void store_server_port(const int port){
    EEPROM.write(4, port & 255);
    EEPROM.write(5, port >> 8);
}

void store_wifi_name(const char* wifi_name){
    int len = strlen(wifi_name);
    EEPROM.write(6, len);

    for(int i = 0; i < len; ++i){
        EEPROM.write(7+i, wifi_name[i]);
    }
}

void store_wifi_password(const char* wifi_password){
    int len = strlen(wifi_password);
    EEPROM.write(57,len);
    
    for(int i = 0; i < len; ++i){
        EEPROM.write(58+i,wifi_password[i]);
    }
}


IP_Address retrieve_server_ip(){
    byte b1,b2,b3,b4;

    b1 = EEPROM.read(0);
    b2 = EEPROM.read(1);
    b3 = EEPROM.read(2);
    b4 = EEPROM.read(3);

    return IP_Address(b1,b2,b3,b4);
}

int retrieve_server_port(){
    int lower = EEPROM.read(4);
    int upper = EEPROM.read(5) << 8;
    return lower+upper;
}

void retrieve_wifi_name(char* wifi_name){
    int len = EEPROM.read(6);
    for(int i = 0; i < len; ++i){
        char c = EEPROM.read(7+i);
        wifi_name[i] = c;
    }
    wifi_name[len] = '\0';
}

void retrieve_wifi_password(char* wifi_password){
int len = EEPROM.read(57);
    for(int i = 0; i < len; ++i){
        char c = EEPROM.read(58+i);
        wifi_password[i] = c;
    }
    wifi_password[len] = '\0';
}
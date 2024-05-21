#ifndef STORAGE
#define STORAGE

#include "wifi.hpp"

void store_server_ip(const IP_Address ip);
void store_server_port(const int port);
void store_wifi_name(const char* wifi_name);
void store_wifi_password(const char* wifi_password);

IP_Address retrieve_server_ip();
int retrieve_server_port();
void retrieve_wifi_name(char* wifi_name);
void retrieve_wifi_password(char* wifi_password); 

#endif 
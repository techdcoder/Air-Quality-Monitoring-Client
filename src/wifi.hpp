#ifndef WIFI_H
#define WIFI_H 

#include <Arduino.h>

class IP_Address{
private: 
    char ip_str[16]; 
    byte b1, b2, b3, b4;
public:
    IP_Address();
    IP_Address(const char* ip_str_);
    IP_Address(const byte b1_, const byte b2_, const byte b3_, const byte b4_);

    const char* get_str();
    void get_bytes(byte* b1, byte* b2, byte* b3, byte* b4);
};

namespace Wifi{
    void initialize();
    void connect(const char* ssid, const char* password);
    void connect_server(const char* ip_addr, int port);
    bool connected_server();
    bool connected();

    void send_data(const char* data);
}

#endif 
#include <Arduino.h>

#include "ui.hpp"
#include "storage.hpp"

int read_serial(char* str, int max_size){
  int len = Serial.available();
  if(len){
    memset(str,0,max_size);
    Serial.readBytes(str,len);
  }
  return len; 
}

int read_serial_blocking(char* str, int max_size){
    memset(str,0,sizeof(char)*max_size);
    while(!Serial.available()) {
        yield();
    }

    delay(100); 

    int len = Serial.available();
    if(len){
        memset(str,0,max_size);
        Serial.readBytes(str,len);
    }
    return len; 
}

#define BUFFER_SIZE 128

void print_root_ui(){
    Serial.println("<1> Change Wifi Name and Password");
    Serial.println("<2> Change Server ip and port");
  
    Serial.println("<3> Run");
}

void print_ui(int wait_duration){
    char input[BUFFER_SIZE];
    bool first = true;

    while(true){
        print_root_ui();
        if(first){
            int last_time = millis();
            bool user = false; 
            
            while(millis() - last_time < wait_duration){
                if(Serial.available() > 0){
                    user = true; 
                    break;
                }
            }
            if(!user){
                Serial.println("No response, continuing");
                return;
            }
            first = false;
        }
        
        read_serial_blocking(input,BUFFER_SIZE);

        if(input[0] == '1'){
            Serial.println("Enter Wifi Name: ");
            read_serial_blocking(input,BUFFER_SIZE);
            store_wifi_name(input);

            Serial.println(input);

            Serial.println("Enter Wifi Password:");
            read_serial_blocking(input,BUFFER_SIZE);
            store_wifi_password(input);

            Serial.println(input);

        }else if(input[0] == '2'){
            Serial.println("Enter Server IP: ");
            read_serial_blocking(input,BUFFER_SIZE);
            store_server_ip(input);
            IP_Address ip_addr(input);
            store_server_ip(ip_addr); 
            Serial.println(ip_addr.get_str());

            
            Serial.println("Enter Server Port:");
            read_serial_blocking(input,BUFFER_SIZE);

            Serial.println(input);

            for(int i = 0; i < strlen(input); ++i){
                if(isAlpha(input[i])){
                    Serial.println("Invalid server port!");
                    continue;
                }
            }

            store_server_port(atoi(input));
        }else if(input[0] == '3'){
            break; 
        }else{
            Serial.println("Invalid Input");
        }
    }
}
#include "sensors.hpp"
#include <DHT.h> 
#include <SoftwareSerial.h>
#include <PMS.h> 

const int mq2 = A0;
const int mq5 = A1;
const int mq7 = A2; 

DHT dht(9,DHT22);

SoftwareSerial pms_serial(2,3);
PMS pms(pms_serial);

void initialize_sensors(){
    pms_serial.begin(9600); 
    dht.begin();

    pinMode(mq2,INPUT);
    pinMode(mq5,INPUT);
    pinMode(mq7,INPUT);
}

SensorData get_sensor_data(){
    pms_serial.listen();
    SensorData output;

    output.mq2_reading = analogRead(mq2);
    output.mq5_reading = analogRead(mq5);
    output.mq7_reading = analogRead(mq7);

    output.dht_temperature = dht.readTemperature();
    output.dht_humidity = dht.readHumidity();

    PMS::DATA data;
    bool pms_read = pms.read(data);
    output.pms_read = pms_read;

    if(pms_read){
        output.pms_1 = data.PM_AE_UG_1_0;
        output.pms_2_5 = data.PM_AE_UG_2_5;
        output.pms_10 = data.PM_AE_UG_10_0;
    }else{
        output.pms_1 = 0;
        output.pms_2_5 = 0;
        output.pms_10 = 0;
    }

    return output;
}

template<typename T> void print_value(const char* str, const T value){
    Serial.print(str);
    Serial.println(value);
}

void SensorData::print(){
    print_value("MQ2: ", mq2);
    print_value("MQ5: ", mq5);
    print_value("MQ7: ", mq7);

    print_value("Temperature: ", dht_temperature);
    print_value("Humidity: ", dht_humidity);

    print_value("PMS 1.0", pms_1);
    print_value("PMS 2.5", pms_2_5);
    print_value("PMS 10.0", pms_10);
}

void float_to_str(float input, char* output, int buf_size){
    memset(output,0,buf_size);
    int num = (int)input; 
    sprintf(output,"%d",num);
    char decimal_part[2];
    decimal_part[0] = '0' + (int(input * 10) % 10);
    decimal_part[1] = '\0';
    output[strlen(output)] = '.';
    strcat(output,decimal_part);
}

const char* SensorData::csv(){
    static char csv[256];
    char temperature[10];
    char humidity[10];

    float_to_str(dht_humidity,humidity,10);
    float_to_str(dht_temperature,temperature,10);

    sprintf(csv, "%d,%d,%d,%s,%s,%d,%d,%d", mq2_reading, mq5_reading, mq7_reading, temperature, humidity, pms_1, pms_2_5, pms_10);
    return csv;
}
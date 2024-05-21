#ifndef SENSORS
#define SENSORS 

struct SensorData{
    int mq2_reading, mq5_reading, mq7_reading;
    float dht_humidity, dht_temperature;
    int pms_1, pms_2_5, pms_10;
    bool pms_read;

    

    void print();
    const char* csv();
};

void initialize_sensors();
SensorData get_sensor_data();


#endif 
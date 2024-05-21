import serial

arduino_serial = serial.Serial("/dev/ttyUSB0",115200)
while True:
    reading = arduino_serial.readline()
    reading_decoded = reading.decode()[:-2]
    print(reading_decoded)
    if reading_decoded == "AIR QUALITY CONTROL":
        arduino_serial.write('GOOD'.encode())
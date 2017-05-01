# Sensor Bridge

The sensor bridge board is a small piece of embedded hardware that allows the 
user to easily connect up to six analog sensors. The board will then read the 
data from the sensors and send this data via the serial port to a [client 
application](https://github.com/sensorlab030/sensorbridge-client) which then
either records the data to files or serves it over a websocket to interested
applications.

The firmware (/firmware) of the sensor board is Arduino based and the board 
layout files (/hardware) are created with CadSoft/Autodesk Eagle

## Protocol

The data from the sensors is sent over the serial port at a baud rate of 9600 
bps. 

The serial protocol in which the data is communicated is very straighforward: 
it will always send six two-byte (16 bit) values (ordered from sensor one to 
sensor six), separated by a carriage return (0x0D) and a line feed (0x0A). 
So one single message will always be 14 bytes long and  be ordered like this:

Sensor 1 value, Sensor 2 value, Sensor 3 value, Sensor 4 value, 
Sensor 5 value, Sensor 5 value, Carriage return, Line feed

The sensor readings will have a value from 0 to 1023 (10 bit), and will be 
sent with the high byte first. If it is detected that there is no sensor 
connected to the analog input, a value of ```FF:FF``` will be sent to notify the 
disconnected state of the sensor.


### Example 1: One sensor connected, analog value of 0

This is the message that is sent when only the first sensor is connected that
has a sensor reading of 0 (```00:00```).

```
00:00:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:0D:0A
```

### Example 2: One sensor connected, analog value of 1023

This is the message that is sent when only the first sensor is connected that
has a sensor reading of 1023 (```03:FF```).

```
03:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:0D:0A
```


## License

The firmware (everything under /firmware) is licensed under the GPLv3, the 
Arduino core libraries and IDE are under their own respective licenses (GNU 
LGPL and GNU GPL). License text can be found under /firmware/license.txt

The board layout files (everything under /hardware) is under the Creative 
Commons Attribution-ShareAlike 3.0 Unported License. License text can be 
found under /hardware/license.txt
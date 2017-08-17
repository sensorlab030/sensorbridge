
#define SENSOR_COUNT 3

// Mapping of sensors to pins. The first value of the sensor pin arrays
// is the pin that Sensor1 is connected to, second value for Sensor2 and
// so on.
//                Sensor id: 1, 2, 3
uint8_t sensorDataPins[] = { 5, 4, 3 }; // Analog input pin the sensor is connected to to collect data
uint8_t sensorConnPins[] = { 2, 3, 4 }; // Digital input pin the sensor is connected to check connection (uses internal pullup)
uint8_t sensorLedPins[]  = { 5, 6, 7 }; // Digital input pin the sensor is connected to display connection status

void setup() {

  // Setup pin modes for the digital pins
  for (int i = 0; i < SENSOR_COUNT; i++) {    
    pinMode(sensorConnPins[i], INPUT_PULLUP);
    pinMode(sensorLedPins[i], OUTPUT);
  }

  // Booting LED animation 
  for (int i = 0; i < 40; i++) {
    int enabledLedIndex = i % SENSOR_COUNT;
    for (int j = 0; j < SENSOR_COUNT; j++) {    
      digitalWrite(sensorLedPins[j], j == enabledLedIndex);
    }
    delay(50);
  }

  // Start serial communication
  Serial.begin(9600);
  
}

void loop() {

  // Read and communicate values
  for (int i = 0; i < SENSOR_COUNT; i++) {

    // Determine value of pin
    bool sensorConnected = (digitalRead(sensorConnPins[i]) == LOW); // Pin is pulled low if sensor is connected
    digitalWrite(sensorLedPins[i], sensorConnected);
    uint16_t value = sensorConnected ? analogRead(sensorDataPins[i]) : 65535;

    // Write value to serial port
    Serial.write(highByte(value));
    Serial.write(lowByte(value));
    
  }
  
  // Terminate series of values
  Serial.write(0x0D);
  Serial.write(0x0A);

  // Wait for a bit
  delay(20);
  
}

